/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 13:49:16 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(1000 * data->time_to_die);
	printf("%ld 1 died\n", data->time_to_die);
	free(data);
	return (0);
}

void	obliterate_meal_locks(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_destroy(&(philo[i].meal_lock));
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
	if (check_args(av, ac, data))
		return (free_data_philo(data, NULL));
	if (data->nb_philo == 1)
		return (one_philo(data));
	pthread_mutex_init(&(data->current_action), NULL);
	pthread_mutex_init(&(data->death_lock), NULL);
	pthread_mutex_init(&(data->sleep), NULL);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (1);
	init_philo_data(data, philo);
	create_threads(data, philo);
	pthread_mutex_destroy(&(data->current_action));
	pthread_mutex_destroy(&(data->death_lock));
	pthread_mutex_destroy(&(data->sleep));
	obliterate_meal_locks(philo);
	obliterate_forks(data->forks, data->nb_philo);
	free(data->forks);
	free_data_philo(data, philo);
	return (0);
}
