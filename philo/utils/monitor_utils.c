/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsyn <hsyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:01:48 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/27 16:50:48 by hsyn             ###   ########.fr       */
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

void	check_and_handle_death(t_data *data, int philo_index)
{
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal_philo = data->philos[philo_index].last_meal;
	pthread_mutex_unlock(&data->meal_mutex);	
	if (get_time_in_ms() - data->last_meal_philo >= data->time_to_die)
	{
		set_death_status(data, philo_index);
		pthread_exit(NULL);
	}
}
