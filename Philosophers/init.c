/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:09:47 by serif             #+#    #+#             */
/*   Updated: 2023/04/09 21:17:03 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>


int	join_thread(char **av, t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < ph_atoi(av[1]))
	{
		if (pthread_join(philo->th, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_thread(char **av, t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < ph_atoi(av[1]))
	{
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) != 0)
			return (-1);
		i++;
		usleep(100);
	}
	while (1)
	{
		if (check_dead(philo) == 1)
		{
			//pthread_mutex_unlock(philo->die);
			pthread_mutex_unlock(philo->oc);
			usleep(50);
			return (-1);
		}
	}
	return (0);
}

int	init_philo(int ac, char **av, t_philo	*philo, t_mutex *mutex, pthread_mutex_t *die, pthread_mutex_t *first_meal)
{
	int	i;
	int	flag_die;

	i = 0;
	flag_die = 0;
	while (mutex->number == ph_atoi(av[1]))
		mutex = mutex->next;
	while (i < ph_atoi(av[1]))
	{
		if (ac == 6)
			philo[i].must_eat = ph_atoi(av[5]);
		else
			philo[i].must_eat = -1;
		philo[i].id = i + 1;
		philo[i].time_to_die = ph_atoi(av[2]);
		philo[i].time_to_eat = ph_atoi(av[3]);
		philo[i].time_to_sleep = ph_atoi(av[4]);
		philo[i].first_meal = 1;
		philo[i].target = mutex;
		philo[i].flag_die = &flag_die;
		philo[i].start_dinner = get_time();
		philo[i].total_philo = ph_atoi(av[1]);
		philo[i].die = die;
		philo[i].meal_mutex = first_meal;
		mutex = mutex->next;
		i++;
	}
	return (0);
}