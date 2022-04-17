/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:54:55 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/17 17:14:24 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define DEAD 0
# define FORK 1
# define MEAL 2
# define THINK 3
# define SLEEP 4

typedef struct s_info
{
}	t_info;

typedef struct s_philo
{
	int				hand_forks;
	int				state;
	int				id;
	pthread_t		t;
	long			nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_info			*info;
	pthread_mutex_t	*forks;
	struct timeval	current_time;
	struct timeval	start_time;
	pthread_mutex_t	current_action;
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