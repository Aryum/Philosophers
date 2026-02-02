/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:31:18 by ricsanto          #+#    #+#             */
/*   Updated: 2026/02/02 14:29:25 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param.phi_count)
	{
		if (pthread_join(data->phi_arr[i].thread, NULL) != 0)
		{
			print_error("Failed to join threads\n", &data->waiter);
			set_end(&data->waiter);
			break ;
		}
		i++;
	}
}
