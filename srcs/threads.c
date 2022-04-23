/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:32:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/23 18:48:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_lock(pthread_mutex_t *lock, long *n1, long n2)
{
	pthread_mutex_lock(lock);
	*n1 = n2;
	pthread_mutex_unlock(lock);
}

int	binary_lock(pthread_mutex_t *lock, int n1)
{
	int	temp;

	pthread_mutex_lock(lock);
	temp = n1;
	pthread_mutex_unlock(lock);
	return (temp);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (binary_lock(&(philo->data->death_lock), philo->data->death) == ALIVE)
	{
		get_forks(philo);
		if (philo->state == DEAD)
		{
			release_forks(philo);
			change_lock(&(philo->data->death_lock),
				&(philo->data->death), DEAD);
			return (NULL);
		}
		philo->nb_meals++;
		gettimeofday(&(philo->meal), NULL);
		philo->last_meal = convert_time(philo->meal);
		current_actions(philo, "is eating");
		ft_sleep(philo->data->time_to_eat);
		release_forks(philo);
		current_actions(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		current_actions(philo, "is thinking");
	}
	return (NULL);
}

void	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	gettimeofday(&(data->start_time), NULL);
	while (i < data->nb_philo)
	{
		philo[i].last_meal = convert_time(data->start_time);
		pthread_create(&(philo[i].t), NULL, &routine, philo + i);
		i++;
	}
	i = 0;
	death_set(philo);
	while (i < data->nb_philo)
	{
		pthread_join(philo->t, NULL);
		i++;
	}
	free(philo);
}
