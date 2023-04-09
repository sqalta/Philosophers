/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:49:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/09 03:00:56 by serif            ###   ########.fr       */
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


int main (int ac, char **av)
{
	t_philo			*philo;
	t_mutex 		*all_mutex;
	pthread_mutex_t	*die = NULL;

	if (cntrl_input(ac, av) == 0)
	{
		printf("Wrong input");
		return (0);
	}
	philo = malloc(sizeof(t_philo) * ph_atoi(av[1]));
	die = malloc(sizeof(pthread_mutex_t));
	all_mutex = init_mutex(av, die);
	if (init_philo(ac, av, philo, all_mutex, die))
		return (0);
	if (init_thread(av, philo))
		return (0);
	ft_free(philo, all_mutex, die);
}