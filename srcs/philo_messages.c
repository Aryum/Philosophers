/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:57:49 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/15 14:23:16 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg(t_waiter *w, int nbr, char *action)
{
	long	time;

	mutex_lock(&w->msg_mut);
	time = get_current_time(w) - w->start_time;
	if (!read_end(w))
		printf("%ld %d %s\n", time, nbr, action);
	mutex_unlock(&w->msg_mut);
}

void	msg_died(t_waiter *w, int nbr)
{
	long	time;

	mutex_lock(&w->msg_mut);
	time = get_current_time(w) - w->start_time;
	if (!read_end(w))
	{
		printf("%ld %d %s\n", time, nbr, "died");
		set_end(w);
	}
	mutex_unlock(&w->msg_mut);
}
