/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/09 04:43:40 by serif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->die);
	if (i == 1 && ((get_time() - philo->start_dinner) > philo->time_to_die))
		*philo->flag_die = 1;
	else if (i == 2 && (get_time() - philo->last_meal) > philo->time_to_die)
		*philo->flag_die = 1;
	pthread_mutex_unlock(philo->die);
	if (*philo->flag_die == 1 && printf("%lld %d is dead\n", get_time() - philo->start_dinner, philo->id))
		return (1);
	return (0);
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
}

int	check_dead(t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		if (philo[i].first_meal)
		{
			philo[i].first_meal = 0;
			if (is_dead(&philo[i], 1))
				break;
		}
		else
			if (is_dead(&philo[i], 2))
				break;
		i++;
	}
	return (1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->target->fork);
	printf("%lld %d has taken a fork\n", get_time() - philo->start_dinner, philo->id);
	pthread_mutex_lock(philo->target->next->fork);
	printf("%lld %d has taken a fork\n", get_time() - philo->start_dinner, philo->id);
	printf("%lld %d is eating\n", get_time() - philo->start_dinner, philo->id);
	philo->must_eat--;
	pthread_mutex_lock(philo->die);
	time_to_wait(philo, 1);
	pthread_mutex_unlock(philo->die);
	pthread_mutex_unlock(philo->target->fork);
	pthread_mutex_unlock(philo->target->next->fork);
	philo->last_meal = get_time();
	return(0);
}

int	philo_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", get_time() - philo->start_dinner, philo->id);
	time_to_wait(philo, 2);
	return(1);
}

int	philo_thinking(t_philo *philo)
{
	printf("%lld %d is thinking\n", get_time() - philo->start_dinner, philo->id);
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