/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:14:30 by spalta            #+#    #+#             */
/*   Updated: 2023/04/07 17:04:34 by serif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->target->fork);
	printf ("%d->%s\n", philo->id, "Philo has taken a fork!");
	pthread_mutex_lock(philo->target->next->fork);
	printf ("%d->%s\n", philo->id, "Philo has taken a fork!");
	usleep(800);
	pthread_mutex_unlock(philo->target->fork);
	pthread_mutex_unlock(philo->target->next->fork);
	return(NULL);
}

int	philo_sleep(t_philo *philo)
{
	printf ("%s\n", "Philo is sleeping!");
	return(1);	
}

int	philo_thinking(t_philo *philo)
{
	printf ("%s\n", "Philo is thinking!");
	return(1);
}
void *routine(void *av)
{
	t_philo *philo;

	philo = av;
	while(1)
		philo_eat(philo);
	return (NULL);
}