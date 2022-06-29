/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:26:20 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 14:09:19 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return ;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(data->forks + i, NULL);
		i++;
	}
}

void	set_table(t_data *data, t_philo *philo, int i)
{
	philo[i].r_fork = data->forks + i;
	if (i == 0)
		philo[i].l_fork = data->forks + (data->nb_philo - 1);
	else
		philo[i].l_fork = data->forks + (i - 1);
	(void)philo;
	
}

void	init_philo_data(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	init_forks(data);
	data->death = ALIVE;
	data->philo_meals = 0;
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].id = i;
		set_table(data, philo, i);
		philo[i].enough_meals = NOT_ENOUGH;
		philo[i].state = ALIVE;
		philo[i].right_fork = 0;
		philo[i].left_fork = 0;
		philo[i].nb_meals = 0;
		i++;
	}
}

int	free_data_philo(t_data *data, t_philo *philo)
{
	free(philo);
	free(data);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
