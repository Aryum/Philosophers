/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_mut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:48:26 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/15 14:23:02 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ini_thread(t_data *data, int i)
{
	pthread_t	*thread;
	t_philo		*philo;

	philo = &data->phi_arr[i];
	thread = &data->phi_arr[i].thread;
	if (pthread_create(thread, NULL, philo_loop, philo) != 0)
		return (0);
	return (1);
}

int	sf_create_mutex(t_mutex *mutex)
{
	mutex->set = false;
	if (pthread_mutex_init(&mutex->lock, NULL) != 0)
		return (0);
	mutex->set = true;
	return (1);
}

void	sf_destroy_mutex(t_mutex *mutex)
{
	if (mutex->set)
		pthread_mutex_destroy(&mutex->lock);
}

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->lock);
}

void	mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->lock);
}
