/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/06 20:32:06 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *philo)
{
	d_philo *philo1;

	philo1 = philo;
	pthread_mutex_lock(philo1->target->fork);
	printf("%lld %d has taken a fork\n", get_time() - philo1->start_time, philo1->id);
	pthread_mutex_lock(philo1->target->next->fork);
	printf("%d has taken a fork\n", philo1->id);
	usleep(2000000);
	pthread_mutex_unlock(philo1->target->next->fork);
	pthread_mutex_unlock(philo1->target->fork);
	return (NULL);
}