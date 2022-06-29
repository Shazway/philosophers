/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:34:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 15:10:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	convert_time(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(long pause_time, t_philo *philo)
{
	long			total_time;
	long			current_time;
	long			start_time;
	struct timeval	time;

	gettimeofday(&(time), NULL);
	start_time = convert_time(time);
	while (1)
	{
		gettimeofday(&(time), NULL);
		current_time = convert_time(time);
		total_time = current_time - start_time;
		pthread_mutex_lock(&(philo->data->death_lock));
		if (total_time >= pause_time)
		{
			pthread_mutex_unlock(&(philo->data->death_lock));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->death_lock));
		if (pause_time - total_time > 1000)
			usleep(100);
		if (pause_time - total_time > 10 && pause_time - total_time < 1000)
			usleep((pause_time - total_time) / 10);
		if (pause_time - total_time < 10)
			usleep(pause_time - total_time);
	}
}
