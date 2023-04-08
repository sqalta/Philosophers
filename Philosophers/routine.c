/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/09 02:32:59 by serif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finish(t_philo *philo)
{
	if ((*philo->flag_die == 1 || philo->must_eat == 0) && print_die)
	{
		pthread_mutex_lock(philo->die);
		if (print_die == 1)
		{
			printf("%ld %d is dead\n", get_time() - philo->start_dinner, philo->id);
			print_die = 0;	
		}
		pthread_mutex_unlock(philo->die);
		return (1);
	}
	return (0);
}

int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->die);
	if (i == 1 && ((get_time() - philo->start_dinner) > philo->time_to_die))
		*philo->flag_die = 1;
	else if (i == 2 && (get_time() - philo->last_meal) > philo->time_to_die)
		*philo->flag_die = 1;
	pthread_mutex_unlock(philo->die);
	if (is_finish(philo))
		return (1);
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

int	check_dead(t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		if (philo[i].first_meal)
			is_dead(&philo[i], 1);
		else
			is_dead(&philo[i], 2);
		i++;
	}
	return (1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->target->fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_dinner, philo->id);
	pthread_mutex_lock(philo->target->next->fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_dinner, philo->id);
	printf("%ld %d is eating\n", get_time() - philo->start_dinner, philo->id);
	philo->must_eat--;
	time_to_wait(philo, 1);
	pthread_mutex_unlock(philo->target->fork);
	pthread_mutex_unlock(philo->target->next->fork);
	philo->last_meal = get_time();
	return(0);
}

int	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - philo->start_dinner, philo->id);
	time_to_wait(philo, 2);
	return(1);
}

int	philo_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time() - philo->start_dinner, philo->id);
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