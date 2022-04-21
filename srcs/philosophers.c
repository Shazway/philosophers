/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/21 01:42:37 by tmoragli         ###   ########.fr       */
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
	int temp;

	pthread_mutex_lock(lock);
	temp = n1;
	pthread_mutex_unlock(lock);
	return (temp);
}

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
	i = 0;
	printf("Here is death\n");
	while (binary_lock(&(philo->data->death_lock), philo->data->death))
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			gettimeofday(&time, NULL);
			if (convert_time(time) - convert_time(philo[i].last_meal) > philo->data->time_to_die)
			{
				change_lock(&(philo->data->death_lock),
							&(philo->data->death), DEAD);
				printf("\033[1;31m");
				printf("%ld\n", convert_time(time) - convert_time(philo[i].last_meal));
				printf("%ld %ld %ld\n", philo->data->time_to_die, philo->data->time_to_eat, philo->data->time_to_sleep);
				current_actions(philo + i, "died");
				printf("\033[0m");
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
	pthread_mutex_destroy(&(data->death_lock));
	obliterate_forks(data->forks, data->nb_philo);
	free(data->forks);
	free(data);
}
