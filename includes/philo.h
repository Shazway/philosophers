/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:54:55 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/19 17:10:04 by tmoragli         ###   ########.fr       */
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
# define ALIVE 1

struct s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				right_fork;
	int				left_fork;
	int				state;
	int				id;
	pthread_t		t;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	struct timeval	last_meal;
	long			nb_meals;
}	t_philo;

typedef struct s_data
{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_meals;
	int		death;
	pthread_mutex_t	*forks;
	struct timeval	current_time;
	struct timeval	start_time;
	pthread_mutex_t	current_action;
	pthread_mutex_t death_lock;
}	t_data;
//--------------Init of data--------------//
void	init_philo_data(t_data *data, t_philo *philo);
void	init_forks(t_data *data);
//--------------Utilitary functions--------------//
int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		free_data(t_data *data);
//--------------Parsing functions--------------//
int		check_args(char **av, int ac, t_data *data);
void	fill_parsing(char **av, t_data *data, int ac);
//--------------Time functions--------------//
long	ft_time(long start);
long	convert_time(struct timeval time);
void	ft_sleep(long pause_time);
//--------------Vital functions--------------//
void	current_actions(t_philo *philo, char *action);
void	get_forks(t_philo *philo);
void	release_forks(t_philo *philo);
//--------------Threads functions--------------//
void	*routine(void *p);
void	create_threads(t_data *data, t_philo *philo);
void	change_lock(pthread_mutex_t *lock, long *val1, long val2);


#endif