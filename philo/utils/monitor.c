/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:47 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/24 14:56:53 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <unistd.h>
#include <stdio.h>

void	*monitor_test(void *argv)
{
	t_data	*datas;
	int		i;

	datas = (t_data *)argv;
	while (1)
	{
		pthread_mutex_lock(&datas->start_flag_mutex);
		if (datas->start_flag == 1)
		{
			pthread_mutex_unlock(&datas->start_flag_mutex);	
			break ;
		}
		pthread_mutex_unlock(&datas->start_flag_mutex);
	}
	while (1)
	{
		i = -1;
		while (++i < datas->philo_count)
		{

			check_and_handle_death(datas, i);

			pthread_mutex_lock(&datas->philos[i].eat_count_mutex);
			if (datas->must_eat == datas->philos[i].eat_count) // MUTEX
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
		monitor_test,
		&*data);
}
