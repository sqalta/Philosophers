/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:50:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/05 01:00:23 by serif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				flag_eat;
	int				flag_sleep;
	int				flag_die;
	time_t			last_eat;
	time_t			current_time;
	time_t			passing_time;
	pthread_t		th;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} 					d_philo;

int	cntrl_input(int ac, char **av);
long	ph_atoi(const char *str);

#endif