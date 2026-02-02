/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:08:53 by ricsanto          #+#    #+#             */
/*   Updated: 2026/02/02 14:33:36 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = &data->phi_arr[i];
	memset(philo, 0, sizeof(t_philo));
	if (i == 0)
		philo->fork[0] = data->param.phi_count - 1;
	else
		philo->fork[0] = i - 1;
	philo->fork[1] = i;
	philo->nbr = i + 1;
	philo->param = data->param;
	philo->waiter = &data->waiter;
	if (!sf_create_mutex(&data->waiter.philo[i]))
		return (0);
	if (pthread_create(&philo->thread, NULL, philo_loop, philo) != 0)
		return (0);
	return (1);
}

static int	create_philos(t_data *dt)
{
	int		i;

	i = 0;
	mutex_lock(&dt->waiter.ini_mut);
	while (i < dt->param.phi_count)
	{
		if (!create_philo(dt, i))
			return (free_data(dt, "Failed to create philo"), 0);
		if (!sf_create_mutex(&dt->waiter.forks[i]))
			return (free_data(dt, "Failed to create fork"), 0);
		i++;
	}
	dt->waiter.start_time = get_current_time(&dt->waiter);
	i = 0;
	while (i < dt->param.phi_count)
	{
		dt->phi_arr[i].last_meal = dt->waiter.start_time;
		i++;
	}
	mutex_unlock(&dt->waiter.ini_mut);
	return (1);
}

bool	create_mut(t_data *d)
{
	if (!sf_create_mutex(&d->waiter.end_mut))
		return (false);
	if (!sf_create_mutex(&d->waiter.msg_mut))
		return (false);
	if (!sf_create_mutex(&d->waiter.ini_mut))
		return (false);
	return (true);
}

int	philo_start(int argc, char **agrv, t_data *d)
{
	unsigned int	i;

	memset(&d->waiter, 0, sizeof(t_waiter));
	memset(&d->param, 0, sizeof(t_param));
	d->param.total_eat_count = -1;
	if (!parse_args(argc, agrv, &d->param))
		return (0);
	i = d->param.phi_count;
	d->waiter.finsihed_count = i;
	if (!sf_malloc((void **)&d->phi_arr, sizeof(t_philo) * i))
		return (free_data(d, "Failed to malloc philo"), 0);
	if (!sf_malloc((void **)&d->waiter.forks, sizeof(t_mutex) * i))
		return (free_data(d, "Failed to malloc forks"), 0);
	if (!sf_malloc((void **)&d->waiter.philo, sizeof(t_mutex) * i))
		return (free_data(d, "Failed to malloc forks"), 0);
	if (!create_mut(d))
		return (free_data(d, "Failed to create a mutex"), 0);
	if (!create_philos(d))
		return (free_data(d, "Failed to create philos"), 0);
	return (1);
}
