/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:18:46 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/28 17:07:52 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_parsing(char **av, t_data *data, int ac)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = __INT_MAX__;
}

int	check_zero(t_data *data)
{	
	if (data->time_to_die == 0)
		return (printf("All arguments must be positive numbers\n"));
	if (data->time_to_eat == 0)
		return (printf("All arguments must be positive numbers\n"));
	if (data->time_to_sleep == 0)
		return (printf("All arguments must be positive numbers\n"));
	if (data->nb_meals == 0)
		return (printf("All arguments must be positive numbers\n"));
	return (0);
}

int	check_args(char **av, int ac, t_data *data)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	if (ft_atoi(av[1]) <= 0)
		return (printf("How would the simulation work with no philosophers?\n"));
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (printf("All arguments must be positive numbers\n"));
			j++;
		}
		i++;
	}
	fill_parsing(av, data, ac);
	if (check_zero(data))
		return (1);
	return (0);
}
