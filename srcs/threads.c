/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:32:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 13:40:47 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_lock(pthread_mutex_t *lock, long *n1, long n2)
{
	pthread_mutex_lock(lock);
	*n1 = n2;
	pthread_mutex_unlock(lock);
}

int	compare_lock(pthread_mutex_t *lock, long n1, long n2)
{
	int i;

	pthread_mutex_lock(lock);
	if (n1 == n2)
		i = 1;
	if (n1 > n2)
		i = 2;
	if (n1 < n2)
		i = 3;
	pthread_mutex_unlock(lock);
	return (i);
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
	while (1)
	{
		get_forks(philo);
		if (philo->state == DEAD)
		{
			release_forks(philo);
			change_lock(&(philo->data->death_lock),
				&(philo->data->death), DEAD);
			return (NULL);
		}
		change_lock(&(philo->meal_lock), &(philo->nb_meals),
				(philo->nb_meals + 1));
		gettimeofday(&(philo->meal), NULL);
		change_lock(&(philo->meal_lock), &(philo->last_meal), 
				convert_time(philo->meal));
		current_actions(philo, "is eating");
		ft_sleep(philo->data->time_to_eat, philo);
		release_forks(philo);
		current_actions(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep, philo);
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
		pthread_join(philo[i].t, NULL);
		i++;
	}
}
