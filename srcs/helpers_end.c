/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:14:56 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/15 14:22:57 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end(t_waiter *w)
{
	mutex_lock(&w->end_mut);
	w->end = true;
	mutex_unlock(&w->end_mut);
}

bool	read_end(t_waiter *w)
{
	bool	ret;

	mutex_lock(&w->end_mut);
	ret = w->end;
	mutex_unlock(&w->end_mut);
	return (ret);
}
