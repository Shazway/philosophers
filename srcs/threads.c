/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:32:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 20:27:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_lock(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->death_lock));
	if (philo->state == DEAD)
	{
		release_forks(philo);
		philo->data->death = DEAD;
		pthread_mutex_unlock(&(philo->data->death_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->death_lock));
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 > 0)
		usleep(30000);
	while (1)
	{
		get_forks(philo);
		if (routine_lock(philo))
			return (NULL);
		change_lock(&(philo->data->death_lock), &(philo->nb_meals),
			(philo->nb_meals + 1));
		gettimeofday(&(philo->meal), NULL);
		change_lock(&(philo->data->death_lock), &(philo->last_meal),
			convert_time(philo->meal));
		current_actions(philo, "is eating");
		ft_sleep(philo->data->time_to_eat, philo);
		release_forks(philo);
		current_actions(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep, philo);
		current_actions(philo, "is thinking");
		ft_sleep(3, philo);
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
