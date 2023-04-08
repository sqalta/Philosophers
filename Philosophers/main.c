/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:49:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/08 18:53:50 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_philo		*philo;
	t_mutex 	*all_mutex;

	if (cntrl_input(ac, av) == 0)
	{
		printf("Wrong input");
		return (0);
	}
	philo = malloc(sizeof(t_philo) * ph_atoi(av[1]));
	all_mutex = init_mutex(av);
	if (init_philo(ac, av, philo, all_mutex))
		return (0);
	if (init_thread(av, philo))
		return (0);
	if (join_thread(av, philo))
		return (0);
}