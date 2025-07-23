/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:01:48 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:35 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static void	set_death_status(t_data *data, int philo_index)
{
	data->is_dead = 1;
	data->dead_index = philo_index;
}

void	set_last_meal(t_data *data, int philo_index)
{
	data->last_meal_philo = data->philos[philo_index].last_meal;
}

void	check_and_handle_death(t_data *data, int philo_index)
{
	if (get_time_in_ms() - data->last_meal_philo > data->time_to_die)
	{
		set_death_status(data, philo_index);
		pthread_exit(NULL);
	}
}
