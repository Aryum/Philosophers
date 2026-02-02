/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:27:39 by ricsanto          #+#    #+#             */
/*   Updated: 2026/02/02 14:27:32 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

typedef struct s_param
{
	long	phi_count;
	long	total_eat_count;
	long	die_delta;
	long	eat_delta;
	long	sleep_delta;
}	t_param;

typedef struct s_mutex
{
	pthread_mutex_t	lock;
	bool			set;
}	t_mutex;

typedef struct s_waiter
{
	t_mutex		*forks;
	t_mutex		*philo;
	t_mutex		end_mut;
	t_mutex		msg_mut;
	t_mutex		ini_mut;
	long		start_time;
	int			finsihed_count;
	bool		end;
}	t_waiter;

typedef struct s_philo
{
	t_waiter	*waiter;
	pthread_t	thread;
	t_param		param;
	long		last_meal;
	int			fork[2];
	int			nbr;
	int			eat_count;
	bool		finished;
}	t_philo;

typedef struct s_data
{
	t_philo		*phi_arr;
	t_waiter	waiter;
	t_param		param;
}	t_data;

//end
void	set_end(t_waiter *w);
bool	read_end(t_waiter *w);

//helpers
int		print_error(char *str, t_waiter *waiter);
void	free_data(t_data *data, char *error);
long	get_current_time(t_waiter *waiter);
void	accurate_sleep(long delta, t_waiter *waiter);

//safe alloc
int		sf_malloc(void **ptr, unsigned long size);

//safe threads
int		sf_create_mutex(t_mutex *mutex);
void	sf_destroy_mutex(t_mutex *mutex);
void	mutex_lock(t_mutex *mutex);
void	mutex_unlock(t_mutex *mutex);

//parse
int		parse_args(int argc, char **argv, t_param *param);

//philo thread
int		philo_start(int argc, char **agrv, t_data *d);
void	philo_join(t_data *data);
void	*philo_loop(void *arg);
void	msg(t_waiter *w, int nbr, char *action);
void	msg_died(t_waiter *w, int nbr);

//philo waiter
void	philo_manager(t_data *data);

#endif