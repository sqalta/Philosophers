/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:49:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/06 20:24:57 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	d_philo	*philo;
	t_mutex *all_mutex;

	if (cntrl_input(ac, av) == 0)
	{
		printf("Wrong input");
		return (0);
	}
	philo = malloc(sizeof(d_philo) * ph_atoi(av[1]));
	all_mutex = init_mutex(ac, av);
	while (all_mutex->number == ph_atoi(av[1]))
		all_mutex = all_mutex->next;
	init_philo(ac, av, philo, all_mutex);
	init_thread(ac, av, philo);
	
	
}