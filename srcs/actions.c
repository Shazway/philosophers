/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:35:59 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/28 19:34:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	current_actions(t_philo *philo, char *action)
{
	struct timeval	current_time;

	gettimeofday(&(current_time), NULL);
	pthread_mutex_lock(&(philo->data->current_action));
	if (binary_lock(&(philo->data->death_lock), philo->data->death))
		printf("%ld %d %s\n",
			convert_time(current_time) - convert_time(philo->data->start_time),
			philo->id + 1, action);
	pthread_mutex_unlock(&(philo->data->current_action));
}

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		pthread_mutex_lock(philo->r_fork);
		current_actions(philo, "has taken a fork");
		philo->right_fork = 1;
		pthread_mutex_lock(philo->l_fork);
		current_actions(philo, "has taken a fork");
		philo->left_fork = 1;
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		current_actions(philo, "has taken a fork");
		philo->left_fork = 1;
		pthread_mutex_lock(philo->r_fork);
		current_actions(philo, "has taken a fork");
		philo->right_fork = 1;
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	philo->right_fork = 0;
	pthread_mutex_unlock(philo->l_fork);
	philo->left_fork = 0;
}

void	ate_enough(t_philo *philo, int i)
{
	philo[i].enough_meals = ENOUGH;
	philo->data->philo_meals++;
}
