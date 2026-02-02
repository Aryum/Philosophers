/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_mut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:48:26 by ricsanto          #+#    #+#             */
/*   Updated: 2026/02/02 14:28:20 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
