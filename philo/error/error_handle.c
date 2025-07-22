/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:46:19 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/22 19:46:53 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include "../lib/error.h"
#include <stdlib.h>
#include <stdio.h>

void	cleanup(t_data *data)
{
	destroy_mutex(data);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	error_check(t_data *data, int err_code, void *ptr)
{
	if (ptr)
		return ;
	if (err_code == ERR_MALLOC_FAIL)
		fprintf(stderr, "ERR_MALLOC_FAIL\n");
	else if (err_code == ERR_INVALID_ARG)
		fprintf(stderr, "ERR_INVALID_ARG\n");
	else if (err_code == ERR_THREAD_FAIL)
		fprintf(stderr, "ERR_THREAD_FAIL\n");
	else if (err_code == ERR_ATOI_FAIL)
		fprintf(stderr, "ERR_ATOI_FAIL\n");
	if (data)
		cleanup(data);
	exit(1);
}

void	error_check_mutex(t_data *data, int value)
{
	if (value == 0)
		return ;
	if (value != 0)
		fprintf(stderr, "ERR_MUTEX_FAIL\n");
	if (data)
		cleanup(data);
	exit(1);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->check_meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->start_flag_mutex);
	if (data->forks)
	{
		while (++i < data->philo_count)
			pthread_mutex_destroy(&data->forks[i]);
	}
}
