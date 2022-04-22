/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/22 02:17:32 by tmoragli         ###   ########.fr       */
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
	long	now;

	i = 0;
	while (binary_lock(&(philo->data->death_lock), philo->data->death))
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			gettimeofday(&time, NULL);
			now = convert_time(time);
			if (philo[i].nb_meals == philo->data->nb_meals)
				philo->data->philo_meals++;
			if (philo->data->philo_meals == philo->data->nb_meals)
			{
				change_lock(&(philo->data->death_lock),
							&(philo->data->death), DEAD);
				printf("Enough eating for today, all philosophers ate %ld times\n", philo->data->nb_meals - 1);
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

int	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(1000 * data->time_to_die);
	printf("%ld 1 died\n", data->time_to_die);
	free(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (check_args(av, ac, data))
		return (free_data(data));
	if (data->nb_philo == 1)
		return(one_philo(data));
	pthread_mutex_init(&(data->current_action), NULL);
	pthread_mutex_init(&(data->death_lock), NULL);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (1);
	init_philo_data(data, philo);
	create_threads(data, philo);
	pthread_mutex_destroy(&(data->current_action));
	pthread_mutex_destroy(&(data->death_lock));
	obliterate_forks(data->forks, data->nb_philo);
	free(data->forks);
	free(data);
}
