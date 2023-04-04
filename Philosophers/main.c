/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:49:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/04 19:08:34 by serif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	d_philo	*philo;

	if (cntrl_input(ac, av) == 0)
	{
		printf("Wrong input");
		return (0);
	}
	init_philo(ac, av, philo);
}