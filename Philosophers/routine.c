/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/09 21:15:20 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->die);
	if (i == 1)
	{
		if ((get_time() - philo->start_dinner) > philo->time_to_die)
			*philo->flag_die = 1;
	}
	else if (i == 2)
	{
		if ((get_time() - philo->last_meal) > philo->time_to_die)
			{
				*philo->flag_die = 1;
			}
		if (philo->must_eat == 0)
		{
			pthread_mutex_unlock(philo->die);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->die);
	if (*philo->flag_die == 1 && print_status(philo, "is dead"))
	{
		pthread_mutex_lock(philo->die);
		return (1);
	}
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
			if (is_dead(&philo[i], 1))
				return (1);
		}
		else
			if (is_dead(&philo[i], 2))
			{
				//pthread_mutex_lock(philo->die);
				pthread_mutex_lock(philo->oc);
				return (1);
			}
		i++;
	}
	return (0);
}
int	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->die);
	printf("%lld %d %s\n", get_time() - philo->start_dinner, philo->id, status);
	pthread_mutex_unlock(philo->die);
	return (1);
}
int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->target->fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->target->next->fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->die);
//	pthread_mutex_lock(philo->meal_mutex);
	philo->first_meal = 0;
	philo->must_eat--;
//	pthread_mutex_unlock(philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->die);
	time_to_wait(philo, 1);
	pthread_mutex_unlock(philo->target->next->fork);
	pthread_mutex_unlock(philo->target->fork);
	return(0);
}

int	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	time_to_wait(philo, 2);
	return(1);
}

int	philo_thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
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