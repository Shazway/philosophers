/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:32:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/21 01:42:05 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo *philo;

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
		gettimeofday(&(philo->last_meal), NULL);
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
	int		i;

	i = 0;
	gettimeofday(&(data->start_time), NULL);
	while (i < data->nb_philo)
	{
		philo[i].last_meal = data->start_time;
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
	printf("Over\n");
	free(philo);
}