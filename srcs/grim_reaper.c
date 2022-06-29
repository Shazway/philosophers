/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:04:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 21:42:21 by tmoragli         ###   ########.fr       */
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
	philo->data->death = DEAD;
	printf("Enough eating for today, all philosophers ate at least %ld times\n",
		philo->data->nb_meals);
	death_row(philo);
	pthread_mutex_unlock(&(philo->data->death_lock));
	return (1);
}

int	end_simulation(t_philo *philo, long now, int i)
{
	death_row(philo);
	pthread_mutex_unlock(&(philo->data->death_lock));
	pthread_mutex_lock(&(philo->data->current_action));
	printf("%ld %d %s\n",
		now - convert_time(philo->data->start_time), i + 1, "died");
	pthread_mutex_unlock(&(philo->data->current_action));
	change_lock(&(philo->data->death_lock),
		&(philo->data->death), DEAD);
	return (1);
}

int	death_loop(t_philo *philo, long now, int i)
{
	struct timeval	time;

	i = 0;
	pthread_mutex_lock(&(philo->data->death_lock));
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
			return (end_simulation(philo, now, i));
		i++;
	}
	pthread_mutex_unlock(&(philo->data->death_lock));
	usleep(1000);
	return (0);
}

int	death_set(t_philo *philo)
{
	while (1)
		if (death_loop(philo, 0, 0))
			break ;
	return (0);
}
