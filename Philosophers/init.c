/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:09:47 by serif             #+#    #+#             */
/*   Updated: 2023/04/08 19:32:24 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (*philo->flag_die != 1)
		check_dead(philo);
	return (0);
}

int	init_philo(int ac, char **av, t_philo	*philo, t_mutex *mutex)
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
		philo[i].id = i + 1;
		philo[i].time_to_die = ph_atoi(av[2]);
		philo[i].time_to_eat = ph_atoi(av[3]);
		philo[i].time_to_sleep = ph_atoi(av[4]);
		philo[i].first_meal = 1;
		philo[i].target = mutex;
		philo[i].flag_die = &flag_die;
		philo[i].start_dinner = get_time();
		philo[i].total_philo = ph_atoi(av[1]);
		mutex = mutex->next;
		i++;
	}
	return (0);
}