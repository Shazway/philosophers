/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:18:46 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/16 15:10:00 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_parsing(char **av, t_data *data, int ac)
{
	data->pars.nb_philo = ft_atoi(av[1]);
	data->pars.nb_philo = ft_atoi(av[2]);
	data->pars.nb_philo = ft_atoi(av[3]);
	data->pars.nb_philo = ft_atoi(av[4]);
	if (argc == 5)
		data->pars.nb_philo = ft_atoi(av[5]);
}


int	check_args(char **av, int ac, t_data *data)
{
	int	i;
	int	j;

	if (!(ac == 4 || ac == 5))
		return (printf("Wrong number of arguments\n"));
	if (ft_atoi(av[2]) < 1)
		return (printf("How would the simulation work with no philosophers?\n"));
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (is_digit(av[i][j]))
				return (printf("Arguments must be positive numbers\n"));
			j++;
		}
		i++;
	}
	fill_parsing(av, data, ac);
	return (0);
}