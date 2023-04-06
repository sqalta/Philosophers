/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:09:47 by serif             #+#    #+#             */
/*   Updated: 2023/04/06 20:25:28 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(int ac, char **av, d_philo	*philo)
{
	int	i;

	i = 0;
	while (i < ph_atoi(av[1]))
	{
		pthread_create(&philo[i].th, NULL, &routine, &philo[i]);
		ac++;
		i++;
		usleep(100);
	}


	
	return (1);
}

int	init_philo(int ac, char **av, d_philo	*philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < ph_atoi(av[1]))
	{
		if (ac == 6)
			philo[i].must_eat = ph_atoi(av[5]);
		philo[i].id = i + 1;
		philo[i].time_to_die = ph_atoi(av[2]);
		philo[i].time_to_eat = ph_atoi(av[3]);
		philo[i].time_to_sleep = ph_atoi(av[4]);
		philo[i].flag_eat = 0;
		philo[i].flag_die = 0;
		philo[i].flag_sleep = 0;
		philo[i].target = mutex;
		mutex = mutex->next;
		i++;
	}
	return (1);
}