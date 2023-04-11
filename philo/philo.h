/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spalta <spalta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:50:10 by serif             #+#    #+#             */
/*   Updated: 2023/04/11 16:54:37 by spalta           ###   ########.fr       */
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
	int				must_eat;
	int				all_die;
	int				*flag_die;
	long long		start_dinner;
	long long		last_meal;
	t_mutex			*target;
	pthread_t		th;
	pthread_mutex_t	*die;
	pthread_mutex_t	*meal_mutex;
}	t_philo;

int		cntrl_input(int ac, char **av);
long	ph_atoi(const char *str);
int		init_philo(int ac, char **av, t_philo	*philo, t_mutex *mutex);
int		init_thread(char **av, t_philo	*philo);
void	init_die(char **av, t_philo	*philo, pthread_mutex_t *die);
int		join_thread(char **av, t_philo	*philo);
int		check_dead(t_philo	*philo);
void	add_mutex(t_mutex *head, t_mutex *new);
t_mutex	*new_mutex(int i);
t_mutex	*init_mutex(char **av, pthread_mutex_t *die);
long long get_time();
void 	*routine(void *av);
int	print_status(t_philo *philo, char *status, int i);
int	check_must_eat(t_philo *philo);
void	time_to_wait(t_philo *philo, int i);
#endif