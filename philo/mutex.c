/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:32:47 by spalta            #+#    #+#             */
/*   Updated: 2023/04/11 15:10:02 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_mutex(t_mutex *head, t_mutex *new)
{
	t_mutex	*iter;

	iter = head;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
}

t_mutex	*new_mutex(int i)
{
	t_mutex *new;
	
	new = malloc(sizeof(t_mutex));
	new->fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->fork, NULL);
	new->number = i + 1;
	new->next = NULL;
	return (new);
}

t_mutex	*init_mutex(char **av, pthread_mutex_t *die)
{
	t_mutex *all_mutex;
	t_mutex	*iter;
	int	i;

	i = 0;
	pthread_mutex_init(die, NULL);
	all_mutex = new_mutex(i);
	while (i < (ph_atoi(av[1]) - 1))
	{
		i++;
		add_mutex(all_mutex, new_mutex(i));
	}
	iter = all_mutex;
	if (i == 0)
	{
		all_mutex->next = iter;
		return (all_mutex);
	}
	while (iter->next)
		iter = iter->next;
	iter->next = all_mutex;
	return (all_mutex);
}
