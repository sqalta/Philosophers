/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:50:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/06 20:36:12 by spalta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_mutex
{
	pthread_mutex_t *fork;
	struct s_mutex 	*next;
	int				number;
}					t_mutex;

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				flag_eat;
	int				flag_sleep;
	int				flag_die;
	int				must_eat;
	time_t			last_eat;
	time_t			current_time;
	time_t			passing_time;
	pthread_t		th;
	t_mutex			*target;
} 					d_philo;

int		cntrl_input(int ac, char **av);
long	ph_atoi(const char *str);
int		init_philo(int ac, char **av, d_philo	*philo, t_mutex *mutex);
int		init_thread(int ac, char **av, d_philo	*philo);
void	add_mutex(t_mutex *head, t_mutex *new);
t_mutex	*new_mutex(int i);
t_mutex	*init_mutex(int ac, char **av);
void *routine();

#endif