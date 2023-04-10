/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:00:02 by spalta            #+#    #+#             */
/*   Updated: 2023/04/10 17:20:09 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->die);
	if ((get_time() - philo->last_meal) > philo->time_to_die)
		*philo->flag_die = 1;
	if (*philo->flag_die == 1)
	{
		pthread_mutex_unlock(philo->die);
		print_status(philo, "is dead");
		return (1);
	}
	pthread_mutex_unlock(philo->die);
	return (0);
}

int	check_dead(t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		if (is_dead(&philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_must_eat(t_philo *philo)
{
	int i;
	int j;

	i = 0;
	j = 0;
	pthread_mutex_lock(philo->die);
	while (i < philo->total_philo)
	{
		if (philo[i].must_eat == 0)
			j++;
		i++;
	}
	if (i == j)
	{
		pthread_mutex_unlock(philo->die);
		return (1);
	}
	pthread_mutex_unlock(philo->die);
	return (0);
}