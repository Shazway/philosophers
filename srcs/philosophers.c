/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:38:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/17 22:20:51 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//GNL IN LIBFT

//----------Time data---------//
//printf ("Time is %ld\n", data->current_time.tv_usec - data->start_time.tv_usec);

void	current_actions(t_philo *philo, char *action)
{
	struct timeval current_time;

	pthread_mutex_lock(&(philo->data->current_action));
	gettimeofday(&(current_time), NULL);
	printf("%d %d %s\n", (current_time.tv_usec - philo->data->start_time.tv_usec) / 1000, philo->id + 1, action);
	pthread_mutex_unlock(&(philo->data->current_action));
}

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->right_fork = 1;
		current_actions(philo, "is taking a fork (right)");
		pthread_mutex_lock(philo->l_fork);
		current_actions(philo, "is taking a fork(left)");
		philo->left_fork = 1;
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		philo->left_fork = 1;
		current_actions(philo, "is taking a fork(left)");
		pthread_mutex_lock(philo->r_fork);
		current_actions(philo, "is taking a fork(right)");
		philo->right_fork = 1;
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	printf("%d is releasing a fork (right)\n", philo->id + 1);
	philo->right_fork = 0;
	pthread_mutex_unlock(philo->l_fork);
	printf("%d is releasing a fork (left)\n", philo->id + 1);
	philo->left_fork = 0;
}

void	ft_sleep(long time)
{
	struct timeval start_time;
	struct timeval current_time;

//----Secondes * 1000 + microsecondes / 1000 + duree du usleep---//
	printf("time = %ld\n", time);
	gettimeofday(&(start_time), NULL);
	current_time.tv_usec = start_time.tv_usec;
	while (current_time.tv_usec / 1000 + 100 < start_time.tv_usec / 1000 + time)
	{
		usleep(100 * 1000);
		printf("paused : %d\n", current_time.tv_usec / 1000);
		gettimeofday(&(current_time), NULL);
	}
}

void	*routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	
	while (1)
	{
		get_forks(philo);
		//----Verifier si mort----//
		printf("%d will take %ld time to eat\n", philo->id, philo->data->time_to_eat);
		current_actions(philo, "is eating");
		gettimeofday(&(philo->last_meal), NULL);
		ft_sleep(philo->data->time_to_eat);
		release_forks(philo);
		printf("%d will take %ld ms to eat\n", philo->id, philo->data->time_to_sleep);
		current_actions(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		current_actions(philo, "is thinking");
	}
	return (NULL);
}

void	create_threads(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	gettimeofday(&(data->start_time), NULL);
	while (i < data->nb_philo)
	{
		pthread_create(&(philo[i].t), NULL, &routine, philo + i);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		printf("I'm waiting %d\n", i + 1);
		pthread_join(philo->t, NULL);
		printf("%d is finished\n", i + 1);
		i++;
	}
	free(philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	pthread_mutex_init(&(data->death_lock), NULL);
	pthread_mutex_init(&(data->current_action), NULL);
	if (check_args(av, ac, data))
		return (free_data(data));
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (1);
	init_philo_data(data, philo);
	create_threads(data, philo);
	pthread_mutex_destroy(&(data->death_lock));
	free(data->forks);
	free(data);
}
