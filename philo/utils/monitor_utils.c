/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:01:48 by huozturk          #+#    #+#             */
/*   Updated: 2025/08/04 19:26:09 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static void	set_death_status(t_data *data, int philo_index) // MUTEX
{
	pthread_mutex_lock(&data->death_mutex);
	data->is_dead = 1;
	data->dead_index = philo_index;
	pthread_mutex_unlock(&data->death_mutex);
}

int	check_and_handle_death(t_data *data, int philo_index)
{
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal_philo = data->philos[philo_index].last_meal;
	pthread_mutex_unlock(&data->meal_mutex);
	if (get_time_in_ms() - data->last_meal_philo >= data->time_to_die)
	{
		set_death_status(data, philo_index);
		return (1);
	}
	else if (check_dead(data->philos))
		return (1);
	return (0);
}

void	wait_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_flag_mutex);
			if (data->start_flag == 1)
			{
				pthread_mutex_unlock(&data->start_flag_mutex);	
				break ;
			}
		pthread_mutex_unlock(&data->start_flag_mutex);
	}
}
