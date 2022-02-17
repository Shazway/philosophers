/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/17 17:22:33 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_threads(pthread_t *philo, int nb_philo)
{
	philo = malloc(sizeof(pthread_t) * nb_philo);
	if (!philo)
		return (1);
	return (0);
}
int	allocate_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	allocate_threads(data->philo, data->pars.nb_philo);
	if (!data)
		return (1);
	return (0);
}
void	free_data(t_data *data)
{
	free(data);
	free_philosophers(data->philo, data->pars.nb_philo);
}

void*	routine()
{
	write(1, "a thread is passing here\n", 29);
		return (NULL);
}

void	create_threads(pthread_t *philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_create(&philo[i], NULL, &routine, NULL);
		pthread_join(philo[i], NULL);
		i++;
	}
}
int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	allocate_data(data);
	check_args(av, ac, data);
	create_threads(data->philo, data->pars.nb_philo);
	
}