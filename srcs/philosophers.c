/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/16 16:13:47 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_threads(pthread_t *philo, int nb_philo)
{
	philo = malloc(sizeof(pthread_t) * nb_philo);
}
int	allocate_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	allocate_threads(data->philo);
}
int	free_data(t_data *data)
{
	free(data);
	free_philosophers(data->philo, data->pars->nb_philo);
}
int	main(int ac, char **av)
{
	t_data	*data;

	allocate_data(data);
	check_args(av, ac);
	create_philo()
}