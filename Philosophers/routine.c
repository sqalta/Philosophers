/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/08 18:17:25 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int i)
{
	if (i == 1 && ((get_time() - philo->start_dinner) > philo->time_to_die))
		philo->flag_die = 1;
	else if ((get_time() - philo->last_meal) > philo->time_to_die)
		philo->flag_die = 1;
	return (0);
}

void	time_to_wait(t_philo *philo, int i)
{
	time_t	start_time;

	start_time = get_time();
	if (i == 1)
		while ((get_time() - start_time) < philo->time_to_eat)
			usleep(100);
	if (i == 2)
		while ((get_time() - start_time) < philo->time_to_sleep)
			usleep(100);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->target->fork);
	printf("%llu %d has taken a fork\n", get_time() - philo->start_dinner, philo->id);
	pthread_mutex_lock(philo->target->next->fork);
	printf("%llu %d has taken a fork\n", get_time() - philo->start_dinner, philo->id);
	printf("%llu %d is eating\n", get_time() - philo->start_dinner, philo->id);
	time_to_wait(philo, 1);
	pthread_mutex_unlock(philo->target->fork);
	pthread_mutex_unlock(philo->target->next->fork);
	return(0);
}

int	philo_sleep(t_philo *philo)
{
	time_to_wait(philo, 2);
	return(1);
}

int	philo_thinking(t_philo *philo)
{
	printf ("%ld Philo->%d is thinking\n", get_time() - philo->start_dinner, philo->id);
	return(1);
}
void *routine(void *av)
{
	t_philo 	*philo;

	philo = av;
	while(1)
	{
		if (philo_eat(philo))
			break;
		philo_sleep(philo);
		philo_thinking(philo);
	}
	return (NULL);
}