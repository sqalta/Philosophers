/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:00:02 by spalta            #+#    #+#             */
/*   Updated: 2023/04/11 16:14:34 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if ((get_time() - philo->last_meal) > philo->time_to_die)
		*philo->flag_die = 1;
	if (*philo->flag_die == 1)
	{
		pthread_mutex_unlock(philo->die);
		print_status(philo, "is dead", 1);
		return (1);
	}
	return (0);
}

int	check_dead(t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		pthread_mutex_lock(philo->die);
		if (is_dead(&philo[i]))
			return (1);
		pthread_mutex_unlock(philo->die);
		usleep(1000);
		i++;
	}
	return (0);
}

int	check_must_eat(t_philo *philo)
{
	int	i;

	if (philo->must_eat == -1)
		return (0);
	i = 0;
	pthread_mutex_lock(philo->die);
	while (i < philo->total_philo)
	{
		if (philo[i].flag_eat < philo[i].must_eat)
		{
			pthread_mutex_unlock(philo->die);
			return (0);
		}
		i++;
	}
	*philo->flag_die = 1;
	pthread_mutex_unlock(philo->die);
	return (1);
}
