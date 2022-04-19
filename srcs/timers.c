/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:34:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/04/19 15:35:26 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(long start)
{
	struct timeval	current_time;
	long			ret;

	gettimeofday(&current_time, NULL);
	ret = (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
	return (ret - start);
}

long	convert_time(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(long pause_time)
{
	long	total_time;

	total_time = ft_time(0) + pause_time;
	while (ft_time(0) < total_time)
		usleep(100);
}
