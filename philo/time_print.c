/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:28:00 by serif             #+#    #+#             */
/*   Updated: 2023/04/11 16:51:48 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *philo, char *status, int i)
{
	pthread_mutex_lock(philo->die);
	if (i == 0)
		if (*philo->flag_die == 0)
			printf("%lld %d %s\n",
				get_time() - philo->start_dinner, philo->id, status);
	if (i == 1)
		printf("%lld %d %s\n",
			get_time() - philo->start_dinner, philo->id, status);
	pthread_mutex_unlock(philo->die);
	return (1);
}

void	time_to_wait(t_philo *philo, int i)
{
	long long	start_time;

	start_time = get_time();
	if (i == 1)
		while ((get_time() - start_time) < philo->time_to_eat)
			usleep(100);
	if (i == 2)
		while ((get_time() - start_time) < philo->time_to_sleep)
			usleep(100);
	if (i == 3)
		while ((get_time() - start_time) < philo->time_to_die)
			usleep(100);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}