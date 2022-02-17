/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/17 22:35:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_threads(t_data *data, int nb_philo)
{
	data->philo = malloc(sizeof(pthread_t) * nb_philo);
	if (!data->philo)
		return (1);
	return (0);
}

void*	routine()
{
	write(1, "a thread is passing here\n", 26);
	usleep(4000*1000);
	write(1, "a thread is leaving here\n", 26);
	return (NULL);
}

void	create_threads(t_data *data, int nb_philo)
{
	int i;

	(void)data;
	i = 0;
	while (i < nb_philo)
	{
		pthread_create(data->philo + i, NULL, &routine, NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		printf("I'm waiting %d\n", i);
		pthread_join(data->philo[i], NULL);
		printf("%d is finished\n", i);
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
	if (ac < 4 || ac > 5)
		return (write(1, "Wrong number of argumens\n", 26));
	fill_parsing(av, data, ac);
	allocate_threads(data, data->pars.nb_philo);
	check_args(av, ac, data);
	create_threads(data, data->pars.nb_philo);
	free(data);
}
