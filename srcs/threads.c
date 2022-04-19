/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:32:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/19 17:00:07 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo *philo;
	int		is_dead;

	philo = (t_philo *)p;
	is_dead = ALIVE;
	if (check_lock(philo->data->death_lock, philo->data->death) == ALIVE)
	{
		get_forks(philo);
		if (philo->state == DEAD || philo->data->death == DEAD)
		{
			release_forks(philo);
			change_lock(philo->data->death_lock, &(philo->data->death), DEAD);
			return (NULL);
		}
		current_actions(philo, "is eating");
		gettimeofday(&(philo->last_meal), NULL);
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
		pthread_create(&(philo[i].t), NULL, &routine, philo + i);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		printf("I'm waiting %d\n", i + 1);
		pthread_join(philo->t, NULL);
		printf("%d is finished\n", i + 1);
		i++;
	}
	free(philo);
}