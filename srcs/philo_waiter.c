/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_waiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:01:04 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/15 14:23:20 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	reached_target(t_data *dt)
{
	t_param		param;
	t_waiter	*w;
	bool		ret;
	int			i;

	w = &dt->waiter;
	param = dt->param;
	i = 0;
	while (i < param.phi_count)
	{
		mutex_lock(&w->philo[i]);
		ret = dt->phi_arr[i].eat_count == param.total_eat_count;
		mutex_unlock(&w->philo[i]);
		if (ret == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	philo_died(t_data *dt, int i)
{
	t_param		param;
	t_waiter	*w;
	bool		ret;
	long		time;

	w = &dt->waiter;
	param = dt->param;
	ret = false;
	mutex_lock(&w->philo[i]);
	time = get_current_time(w);
	if (!dt->phi_arr[i].finished)
	{
		if (time > dt->phi_arr[i].last_meal + param.die_delta)
		{
			ret = true;
			msg_died(w, dt->phi_arr[i].nbr);
		}
	}
	mutex_unlock(&w->philo[i]);
	return (ret);
}

void	philo_manager(t_data *data)
{
	int	i;

	while (!read_end(&data->waiter))
	{
		i = 0;
		while (i < data->param.phi_count)
		{
			if (philo_died(data, i))
				return ;
			i++;
		}
		if (reached_target(data))
			return ;
	}
}
