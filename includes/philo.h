/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:54:55 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/17 21:49:19 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_parse
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
}	t_parse;

typedef struct s_data
{
	pthread_t	*philo;
	t_parse	pars;
}	t_data;
void	free_philosophers(pthread_t *philo, int nb_philo);
int	ft_isdigit(int c);
int	ft_atoi(char *str);
int	check_args(char **av, int ac, t_data *data);
void	fill_parsing(char **av, t_data *data, int ac);

#endif