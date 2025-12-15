/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:45:51 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/15 14:23:34 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/philo.h"

int	main(int argc, char **agrv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (philo_start(argc, agrv, &data))
	{
		philo_manager(&data);
		philo_join(&data);
		free_data(&data, NULL);
	}
}
