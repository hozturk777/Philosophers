/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:47 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/31 14:46:07 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <unistd.h>
#include <stdio.h>

static void	*monitor_process(void *argv)
{
	t_data	*datas;
	int		i;

	datas = (t_data *)argv;
	wait_start(datas);
	while (1)
	{
		i = -1;
		while (++i < datas->philo_count)
		{
			check_and_handle_death(datas, i);
			pthread_mutex_lock(&datas->philos[i].eat_count_mutex);
			// printf("EAT_LOOP: %d\n", datas->philos[i].eat_loop);
			if (datas->must_eat != -1 && (datas->philos[i].eat_loop + 1 == 0))
			{
				printf("DATA_IS_DEAD : %d\n", datas->is_dead);
				datas->is_dead = 3;
				// printf("is_dead: %d\n", datas->is_dead);
				pthread_exit(NULL);
			}
			pthread_mutex_unlock(&datas->philos[i].eat_count_mutex);
		}
	}
}

void	monitor_philo(t_data *data)
{
	if (pthread_create(
		&data->monitor_philo,
		NULL,
		monitor_process,
		&*data))
	{
		data->start_flag = 1;
		data->is_dead = 2;
	}
}
