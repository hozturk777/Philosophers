/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:46:28 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/08 14:56:04 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h" 
#include <stdio.h>

long long	get_time_in_ms(void) // ARAŞTIRILACAK
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	set_time(t_data *data)
{
	data->start_time = get_time_in_ms();
	data->start_flag = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.is_dead = 0;
	data.dead_index = -1;
	data.forks = NULL;
	data.philos = NULL;
	// ft_memset(&data, 0, sizeof(t_data)); // This line is not needed as we initialize all members explicitly
	if (argc == 5 || argc == 6)
	{
		init_philo(&data, argv, argc);
		init_forks(&data);
		monitor_philo(&data);
		set_time(&data);
		create_philo(&data);
		pthread_mutex_lock(&data.start_flag_mutex);
		data.start_flag = 1;
		pthread_mutex_unlock(&data.start_flag_mutex);
		philo_join(&data);
		cleanup(&data);
		return (0);
	}
	else
	{
		fprintf(stderr, "ERR_INVALID_ARG\n");
		return (1);
	}
}
