/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/24 16:12:45 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//GNL IN LIBFT

void	print_philo_data(t_data *data)
{
	int i;

	i = 0;
	while (i < data->pars->nb_philo)
	{
		printf("table fork of %d %d\n", i, data->philo[i][0].table_fork);
		printf("state of %d %d\n", i, data->philo[i][0].state);
		printf("holding of %d %d\n", i, data->philo[i][0].hand_forks);
		printf("id of %d %d\n", i, data->philo[i][0].id);
		i++;
	}
}

int	allocate_philo(t_data *data, int nb_philo)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo *));
	while (i < nb_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		i++;
	}
	init_philo_data(data);
	print_philo_data(data);
	if (!data->philo)
		return (1);
	return (0);
}

int		left_fork(t_philo *philo, int id)
{
	if (id == 0)
	{
		if (philo[philo->pars->nb_philo].table_fork == 1)
			return (1);
		printf("fork isn't available for 0, %d\n", philo[philo->pars->nb_philo].table_fork);
	}
	else if (philo[id - 1].table_fork == 1)
		return (1);
	return (0);
}

int		right_fork(t_philo *philo, int id)
{
	if (id == philo->pars->nb_philo)
	{	
		if (philo[0].table_fork == 1)
			return (1);
		printf("fork isn't available for last\n");
	}
	else if (philo[id + 1].table_fork == 1)
		return (1);
	return (0);
}

void	get_fork(t_philo *philo)
{
	pthread_mutex_t fork_lock;

	pthread_mutex_init(&fork_lock, NULL);
	usleep(500);
	pthread_mutex_lock(&fork_lock);
	if (left_fork(philo, philo->id))
		printf("philosopher number %d is taking a fork\n", philo->id);
	if (right_fork(philo, philo->id))
		printf("philosopher number %d is taking a fork\n", philo->id);
	pthread_mutex_unlock(&fork_lock);
	pthread_mutex_destroy(&fork_lock);
}
void*	routine(void *philo)
{
	get_fork(philo);
	return (NULL);
}

void	free_philosophers(t_data *from_burden)
{
	int i;

	i = 0;
	while (i < from_burden->pars->nb_philo)
	{
		free(from_burden->philo[i]);
		i++;
	}
	free(from_burden->philo);
}

void	create_threads(t_data *data, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_create(&((*(data->philo[i])).t), NULL, &routine, (void *)data->philo[i]);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		printf("I'm waiting %d\n", i);
		pthread_join((*(data->philo[i])).t, NULL);
		printf("%d is finished\n", i);
		i++;
	}
	free_philosophers(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->pars = malloc(sizeof(t_parse));
	pthread_mutex_init(&(data->death_lock), NULL);
	if (!data)
		return (1);
	if (check_args(av, ac, data))
		return (free_data(data));
	allocate_philo(data, data->pars->nb_philo);
	create_threads(data, data->pars->nb_philo);
	pthread_mutex_destroy(&(data->death_lock));
	free(data);
	free(data->pars);
}
