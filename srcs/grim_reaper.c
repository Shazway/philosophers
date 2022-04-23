/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:04:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/23 18:05:07 by tmoragli         ###   ########.fr       */
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

void	death_set(t_philo *philo)
{
	int i;
	struct timeval time;
	long	now;

	i = 0;
	while (binary_lock(&(philo->data->death_lock), philo->data->death))
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			gettimeofday(&time, NULL);
			now = convert_time(time);
			if (philo[i].nb_meals == philo->data->nb_meals
				&& philo[i].enough_meals == NOT_ENOUGH)
			{
				philo[i].enough_meals = ENOUGH;
				philo->data->philo_meals++;
			}
			if (philo->data->philo_meals == philo->data->nb_philo)
			{
				change_lock(&(philo->data->death_lock),
							&(philo->data->death), DEAD);
				printf("Enough eating for today, all philosophers ate %ld times\n", philo->data->nb_meals);
				printf("%ld\n",philo->data->philo_meals);
				death_row(philo);
				return ;
			}
			if (now - philo[i].last_meal > philo->data->time_to_die)
			{
				change_lock(&(philo->data->death_lock),
							&(philo->data->death), DEAD);
				printf("%ld %d %s\n", now - convert_time(philo->data->start_time) , i  + 1, "died");
				death_row(philo);
				return ;
			}
			i++;
		}
	}
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
