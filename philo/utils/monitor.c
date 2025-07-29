/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:47 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/29 17:10:53 by huozturk         ###   ########.fr       */
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
			if (datas->must_eat == datas->philos[i].eat_count || datas->is_dead == 2)
				pthread_exit(NULL);
			pthread_mutex_unlock(&datas->philos[i].eat_count_mutex);
		}
	}
}

void	monitor_philo(t_data *data)
{
	pthread_create(
		&data->monitor_philo,
		NULL,
		monitor_process,
		&*data);
}
