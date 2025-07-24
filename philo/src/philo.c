/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:46:28 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/24 12:49:34 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdio.h>
#include <unistd.h>


// void	ft_usleep(int wait_time)
// {
// 	unsigned long long	time;

// 	time = get_time_in_ms();
// 	while (get_time_in_ms() - time < ((unsigned long long)wait_time / 100))
// 		usleep(100);
// }

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		init_philo(&data, argv, argc);
		init_forks(&data);
		monitor_philo(&data);
		// set_time(&data);
		create_philo(&data);
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
