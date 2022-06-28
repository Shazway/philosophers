/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:04:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/28 16:10:33 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_row(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		philo[i].state = DEAD;
		i++;
	}
}

int	enough_meals(t_philo *philo)
{
	change_lock(&(philo->data->death_lock),
		&(philo->data->death), DEAD);
	printf("Enough eating for today, all philosophers ate at least %ld times\n",
		philo->data->nb_meals);
	death_row(philo);
	return (1);
}

void	obliterate_forks(pthread_mutex_t *fork, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(fork + i);
		i++;
	}
}

int	end_simultaion(t_philo *philo, long now, int i)
{
	change_lock(&(philo->data->death_lock),
		&(philo->data->death), DEAD);
	printf("%ld %d %s\n",
		now - convert_time(philo->data->start_time), i + 1, "died");
	death_row(philo);
	return (1);
}

int	death_set(t_philo *philo)
{
	int				i;
	struct timeval	time;
	long			now;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			gettimeofday(&time, NULL);
			now = convert_time(time);
			if (philo[i].nb_meals == philo->data->nb_meals
				&& philo[i].enough_meals == NOT_ENOUGH)
				ate_enough(philo, i);
			if (philo->data->philo_meals == philo->data->nb_philo)
				return (enough_meals(philo));
			if (now - philo[i].last_meal > philo->data->time_to_die)
				return (end_simultaion(philo, now, i));
			i++;
		}
	}
	return (0);
}
