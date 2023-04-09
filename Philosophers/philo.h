/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serif <serif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:50:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/09 03:58:04 by serif            ###   ########.fr       */
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
	int				total_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				flag_eat;
	int				flag_sleep;
	int				*flag_die;
	int				print_die;
	int				must_eat;
	int				first_meal;
	long long		start_dinner;
	long long		last_meal;
	t_mutex			*target;
	pthread_t		th;
	pthread_mutex_t	*die;
} 					t_philo;

int		cntrl_input(int ac, char **av);
long	ph_atoi(const char *str);
int		init_philo(int ac, char **av, t_philo	*philo, t_mutex *mutex, pthread_mutex_t *die);
int		init_thread(char **av, t_philo	*philo);
int		join_thread(char **av, t_philo	*philo);
int		check_dead(t_philo	*philo);
void	add_mutex(t_mutex *head, t_mutex *new);
t_mutex	*new_mutex(int i);
t_mutex	*init_mutex(char **av, pthread_mutex_t *die);
long long get_time();
void 	*routine(void *av);

#endif