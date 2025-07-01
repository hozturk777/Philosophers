/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:46:28 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/01 13:19:42 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h" 
#include <stdio.h>

long long	get_time_in_ms(void) // ARAŞTIRILACAK
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));

	//struct timespec ts;
    //clock_gettime(CLOCK_MONOTONIC, &ts);
    //return (long long)(ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL);
}

void	set_time(t_data *data)
{
	data->start_time = get_time_in_ms();
	data->start_flag = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int i = -1;

	data.is_dead = 0;
	data.forks = NULL;
	data.philos = NULL;
	set_time(&data);
	if (argc == 5 || argc == 6)
	{
		init_philo(&data, argv, argc);
		init_forks(&data);
		monitor_philo(&data);
		create_philo(&data);
		pthread_mutex_lock(&data.start_flag_mutex);
		data.start_flag = 1;
		pthread_mutex_unlock(&data.start_flag_mutex);

		pthread_join(
			data.monitor_philo,
			NULL);
		while (++i < data.philo_count)  // Bekleme fonksiyonu olusturulacak
		{
			pthread_join(
				data.philos[i].thread,
				NULL);
		}
		cleanup(&data);
		return (0);
	}
	else
	{
		fprintf(stderr, "Invalid Argument\n");
		return (1);
	}
}
