/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:00:24 by ricsanto          #+#    #+#             */
/*   Updated: 2026/02/09 12:04:21 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_time(t_philo *philo, t_waiter *w)
{
	mutex_lock(&w->philo[philo->nbr - 1]);
	philo->last_meal = get_current_time(w);
	mutex_unlock(&w->philo[philo->nbr - 1]);
}

static bool	update_eat_count(t_philo *philo, t_waiter *w)
{
	bool	finished;

	mutex_lock(&w->philo[philo->nbr - 1]);
	philo->eat_count++;
	philo->finished = philo->eat_count == philo->param.total_eat_count;
	finished = philo->finished;
	mutex_unlock(&w->philo[philo->nbr - 1]);
	return (finished);
}

static bool	eat_cycle(t_philo *philo)
{
	t_waiter	*w;
	bool		finished;

	w = philo->waiter;
	mutex_lock(&w->forks[philo->fork[philo->nbr % 2 == 0]]);
	msg(w, philo->nbr, "has taken a fork");
	mutex_lock(&w->forks[philo->fork[philo->nbr % 2 != 0]]);
	msg(w, philo->nbr, "has taken a fork");
	update_time(philo, w);
	msg(w, philo->nbr, "is eating");
	accurate_sleep(philo->param.eat_delta, w);
	mutex_unlock(&w->forks[philo->fork[philo->nbr % 2 == 0]]);
	mutex_unlock(&w->forks[philo->fork[philo->nbr % 2 != 0]]);
	finished = update_eat_count(philo, w);
	return (finished);
}

void	*philo_loop(void *arg)
{
	t_waiter	*w;
	t_philo		*p;

	p = ((t_philo *) arg);
	w = p->waiter;
	mutex_lock(&w->ini_mut);
	mutex_unlock(&w->ini_mut);
	if (p->param.phi_count == 1)
	{
		msg(w, p->nbr, "has taken a fork");
		accurate_sleep(p->param.die_delta, w);
		return (NULL);
	}
	if (p->nbr % 2 == 0)
		accurate_sleep(10, p->waiter);
	while (!read_end(p->waiter))
	{
		if (eat_cycle(p))
			break ;
		msg(w, p->nbr, "is sleeping");
		accurate_sleep(p->param.sleep_delta, w);
		msg(w, p->nbr, "is thinking");
	}
	return (NULL);
}
