/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:09:47 by serif             #+#    #+#             */
/*   Updated: 2023/04/04 19:27:27 by serif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(int ac, char **av, d_philo	*philo)
{
	int	i;

	i = 0;
	while (i < ph_atoi(av[1]))
	{
		philo[i].time_to_die = ph_atoi(av[2]);
		philo[i].time_to_eat = ph_atoi(av[3]);
		philo[i].time_to_sleep = ph_atoi(av[4]);
		philo[i].flag_eat = 0;
		philo[i].flag_die = 0;
		philo[i].flag_sleep = 0;
		i++;
	}
}