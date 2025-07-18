/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:47 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/17 12:06:38 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void	*monitor_test(void *argv)
{
	t_data	*datas;
	int	i;
	
	datas = (t_data *)argv;
	datas->start_flag = 1;
	while (1)
	{
		i = -1;
		while (++i < datas->philo_count)
		{
			set_last_meal(datas, i);
			check_and_handle_death(datas, i);
			if (datas->must_eat == datas->philos[i].eat_count)
				pthread_exit(NULL);
		}
		usleep(100);
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