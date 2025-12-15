/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:02:18 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/15 14:22:53 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sf_malloc(void **ptr, unsigned long size)
{
	*ptr = malloc(size);
	if (ptr == NULL)
		return (0);
	memset(*ptr, 0, size);
	return (1);
}

void	free_data(t_data *data, char *error)
{
	int	i;

	i = 0;
	while (i < data->param.phi_count)
	{
		sf_destroy_mutex(&data->waiter.forks[i]);
		sf_destroy_mutex(&data->waiter.philo[i]);
		i++;
	}
	sf_destroy_mutex(&data->waiter.end_mut);
	free(data->waiter.forks);
	free(data->waiter.philo);
	free(data->phi_arr);
	if (error != NULL)
		print_error(error, &data->waiter);
}
