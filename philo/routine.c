/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/11 17:07:43 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lonely_philo(t_philo *philo)
{
	time_to_wait(philo, 3);
	pthread_mutex_lock(philo->die);
	*philo->flag_die = 1;
	pthread_mutex_unlock(philo->die);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->target->fork);
	print_status(philo, "has taken a fork", 0);
	if (philo->total_philo == 1)
	{
		lonely_philo(philo);
		return (0);
	}
	pthread_mutex_lock(philo->target->next->fork);
	print_status(philo, "has taken a fork", 0);
	print_status(philo, "is eating", 0);
	pthread_mutex_lock(philo->die);
	philo->flag_eat++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->die);
	time_to_wait(philo, 1);
	pthread_mutex_unlock(philo->target->next->fork);
	pthread_mutex_unlock(philo->target->fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	time_to_wait(philo, 2);
	print_status(philo, "is sleeping", 0);
	return (0);
}

int	philo_thinking(t_philo *philo)
{
	print_status(philo, "is thinking", 0);
	return (0);
}

void	*routine(void *av)
{
	t_philo	*philo;

	philo = av;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->die);
		if (*philo->flag_die == 1)
			break ;
		pthread_mutex_unlock(philo->die);
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (philo_thinking(philo))
			break ;
	}
	pthread_mutex_unlock(philo->die);
	return (NULL);
}
