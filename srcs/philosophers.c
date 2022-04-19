/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/19 17:09:28 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_lock(pthread_mutex_t *lock, int value)
{
	int temp;

	temp = value;
	pthread_mutex_lock(lock);
	if (temp == 1)
	{
		pthread_mutex_unlock(lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(lock);
		return (0);
	}
}

void	death_set(t_philo *philo)
{
	int i;

	i = 0;
	change_lock(&(philo->data->death_lock), &(philo->data->death), ALIVE);
	while (check_lock(&(philo->data->death_lock), philo->data->death) == ALIVE)
	{
		while (i < philo->data->nb_philo)
		{
			if (convert_time(philo[i].last_meal) - convert_time(philo->data->start_time) >= philo->data->time_to_die * 1000)
			{
				change_lock(philo->data->death_lock, &(philo->data->death), DEAD);
				current_actions(philo + i, "died");
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

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	pthread_mutex_init(&(data->death_lock), NULL);
	pthread_mutex_init(&(data->current_action), NULL);
	if (check_args(av, ac, data))
		return (free_data(data));
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (1);
	init_philo_data(data, philo);
	create_threads(data, philo);
	death_set(philo);
	pthread_mutex_destroy(&(data->death_lock));
	obliterate_forks(data->forks, data->nb_philo);
	free(data->forks);
	free(data);
}
