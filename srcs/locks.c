/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:34:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/06/29 20:50:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	obliterate_forks(pthread_mutex_t *fork, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(fork + i);
		i++;
	}
}

void	change_lock(pthread_mutex_t *lock, long *n1, long n2)
{
	pthread_mutex_lock(lock);
	*n1 = n2;
	pthread_mutex_unlock(lock);
}

int	compare_lock(pthread_mutex_t *lock, long n1, long n2)
{
	int	i;

	pthread_mutex_lock(lock);
	if (n1 == n2)
		i = 1;
	if (n1 > n2)
		i = 2;
	if (n1 < n2)
		i = 3;
	pthread_mutex_unlock(lock);
	return (i);
}

int	binary_lock(pthread_mutex_t *lock, int n1)
{
	int	temp;

	pthread_mutex_lock(lock);
	temp = n1;
	pthread_mutex_unlock(lock);
	return (temp);
}
