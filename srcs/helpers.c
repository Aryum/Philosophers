/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:06:06 by ricsanto          #+#    #+#             */
/*   Updated: 2026/02/09 12:23:43 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_buffer(char *buffer, char *str)
{
	int	i;
	int	h;

	i = 0;
	h = 0;
	while (buffer[i] != '\0' && i < 100)
		i++;
	if (i == 89)
		write(2, "Message too big\n", 17);
	while (str[h] != '\0')
	{
		buffer[i + h] = str[h];
		h++;
	}
	buffer[i + h] = '\0';
}

int	print_error(char *str, t_waiter *waiter)
{
	char	c[100];
	int		i;

	memset(c, 0, 100);
	fill_buffer(c, "Error: ");
	fill_buffer(c, str);
	fill_buffer(c, "\n");
	i = 0;
	while (c[i] != '\0')
		i++;
	if (waiter != NULL)
	{
		mutex_lock(&waiter->msg_mut);
		write(2, c, i);
		mutex_unlock(&waiter->msg_mut);
	}
	else
		write(2, c, i);
	return (0);
}

long	get_current_time(t_waiter *waiter)
{
	struct timeval	tv;
	long			current;

	if (gettimeofday(&tv, NULL) == -1)
	{
		//set_end(waiter);
		print_error("Get time error", waiter);
		return (0);
	}
	current = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current);
}

void	accurate_sleep(long delta, t_waiter *waiter)
{
	long	start;

	start = get_current_time(waiter);
	while (get_current_time(waiter) - start < delta)
	{
		if (read_end(waiter))
			break ;
		usleep(500);
	}
}
