/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:54:55 by tmoragli          #+#    #+#             */
/*   Updated: 2022/02/24 15:20:41 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# define DEAD 0
# define MEAL 1
# define THINK 2
# define SLEEP 3

typedef struct s_parse
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
}	t_parse;

typedef struct s_philo
{
	t_parse		*pars;
	int			table_fork;
	int			hand_forks;
	int			state;
	int			id;
	pthread_t	t;
}	t_philo;

typedef struct s_data
{
	t_philo	**philo;
	t_parse	*pars;
	pthread_mutex_t death_lock;
}	t_data;
//---------Allocation and free functions-----//
void	free_philosophers(t_data *from_burden);
int		free_data(t_data *data);
//---------Utilitary functions--------------//
int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		check_args(char **av, int ac, t_data *data);
void	fill_parsing(char **av, t_data *data, int ac);
void	init_philo_data(t_data *data);

#endif