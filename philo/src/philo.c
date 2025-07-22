/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsyn <hsyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:46:28 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/23 01:57:33 by hsyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		init_philo(&data, argv, argc);
		init_forks(&data);
		monitor_philo(&data);
		set_time(&data);
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
