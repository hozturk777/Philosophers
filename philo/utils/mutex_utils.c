/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:55 by huozturk          #+#    #+#             */
/*   Updated: 2025/08/04 19:26:04 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead == 1 || philo->data->is_dead == 2 || philo->data->is_dead == 3)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	check_start_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_flag_mutex);
	if (philo->data->start_flag)
	{
		pthread_mutex_unlock(&philo->data->start_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->start_flag_mutex);
	return (0);
}

int	handle_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo->right_fork_bool)
		{
			pthread_mutex_unlock(philo->right_fork);
			philo->right_fork_bool = 0;		
		}
		if (philo->left_fork_bool)
		{
			pthread_mutex_unlock(philo->left_fork);
			philo->left_fork_bool = 0;
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	check_meal_goal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_meal_mutex);
	if (philo->eat_count == philo->data->must_eat)
	{
		pthread_mutex_lock(&philo->data->must_meal_mutex);
		philo->data->must_meal_num++;
		pthread_mutex_unlock(&philo->data->must_meal_mutex);
		pthread_mutex_unlock(&philo->data->check_meal_mutex);
		if (philo->left_fork_bool)
			pthread_mutex_unlock(philo->left_fork);
		if (philo->right_fork_bool)
			pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check_meal_mutex);
	return (0);
}

void	last_meal_added(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
}
