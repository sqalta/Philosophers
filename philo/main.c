/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:49:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/11 16:48:17 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo, t_mutex *mutex, pthread_mutex_t *die)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		pthread_mutex_destroy(mutex->fork);
		free(mutex->fork);
		mutex = mutex->next;
		i++;
	}
	pthread_mutex_destroy(philo->die);
	free(die);
	free(philo);
}


int	main(int ac, char **av)
{
	t_philo			*philo;
	t_mutex			*all_mutex;
	pthread_mutex_t	*die;
	int				i;
	int				flag;

	if (cntrl_input(ac, av) == 0)
	{
		printf("Wrong input");
		return (0);
	}
	philo = malloc(sizeof(t_philo) * ph_atoi(av[1]));
	die = malloc(sizeof(pthread_mutex_t));
	all_mutex = init_mutex(av, die);
	init_philo(ac, av, philo, all_mutex);
	init_die(av, philo, die);
	i = -1;
	flag = 0;
	while (++i < ph_atoi(av[1]))
		philo[i].flag_die = &flag;
	init_thread(av, philo);
	join_thread(av, philo);
	return (0);
}