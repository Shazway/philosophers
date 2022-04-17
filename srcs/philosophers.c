/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/17 17:18:24 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//GNL IN LIBFT

int	allocate_philo(t_data *data, int nb_philo)
{
	data->philo = malloc(sizeof(t_philo) * nb_philo);
	data->forks = malloc(sizeof(pthread_t) * nb_philo);
	init_philo_data(data);
	//print_philo_data(data);
	if (!data->philo)
		return (1);
	return (0);
}

//----------Time data---------//
//printf ("Time is %ld\n", data->current_time.tv_usec - data->start_time.tv_usec);

void	current_actions(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&(data->current_action));
	printf("%ld %d %s\n", (data->current_time.tv_usec - data->start_time.tv_usec), id, action);
	pthread_mutex_unlock(&(data->current_action));
}

void	get_fork(t_philo philo)
{
	right_fork(philo);
	left_fork(philo);
}

void	*routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	
	get_fork(*philo);
	printf("hi %d\n", philo->id);
	return (NULL);
}

void	create_threads(t_data *data, int nb_philo)
{
	int		i;

	i = 0;
	gettimeofday(&(data->start_time), NULL);
	while (i < nb_philo)
	{
		data->philo[i].id = i + 1;
		pthread_create(&data->philo[i].t, NULL, &routine, data->philo + i);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		printf("I'm waiting %d\n", i + 1);
		pthread_join(data->philo->t, NULL);
		printf("%d is finished\n", i + 1);
		i++;
	}
	free(data->philo);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->info = malloc(sizeof(t_info));
	pthread_mutex_init(&(data->death_lock), NULL);
	pthread_mutex_init(&(data->current_action), NULL);
	if (check_args(av, ac, data))
		return (free_data(data));
	allocate_philo(data, data->info->nb_philo);
	create_threads(data, data->info->nb_philo);
	pthread_mutex_destroy(&(data->death_lock));
	free(data);
	free(data->info);
	free(data->forks);
}
