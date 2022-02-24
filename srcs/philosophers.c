/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/22 15:20:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//GNL IN LIBFT
int	allocate_philo(t_data *data, int nb_philo)
{
	data->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!data->philo)
		return (1);
	return (0);
}

void	get_fork(t_data *data)
{
	usleep(400);
	pthread_mutex_lock(&(data->fork_lock));
	printf("philosopher number %d is taking a fork", data->id);
	pthread_mutex_unlock((&data->fork_lock));
}
void*	routine(void *data)
{
	get_fork(data);
	return (NULL);
}

void	create_threads(t_data *data, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		data->id = i;
		pthread_create(&(data->philo[i].t), NULL, &routine, (void *)data);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		printf("I'm waiting %d\n", i);
		pthread_join(data->philo[i].t, NULL);
		printf("%d is finished\n", i);
		i++;
	}
	free(data->philo);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	pthread_mutex_init(&(data->fork_lock), NULL);
	pthread_mutex_init(&(data->death_lock), NULL);
	if (!data)
		return (1);
	if (check_args(av, ac, data))
		return (free_data(data));
	allocate_philo(data, data->pars.nb_philo);
	create_threads(data, data->pars.nb_philo);
	pthread_mutex_destroy(&(data->fork_lock));
	pthread_mutex_destroy(&(data->death_lock));
	free(data->philo);
	free(data);
}
