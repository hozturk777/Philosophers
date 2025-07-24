/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:58 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/24 17:12:03 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdio.h>
#include <unistd.h>

void	philo_eat(t_philo *philo)
{
	last_meal_added(philo);
	print(philo, "is eating");
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	usleep(philo->data->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	check_meal_goal(philo);
	print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	check_meal_goal(philo);
	print(philo, "is thinking");
	usleep(100);
}

void	philo_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.data->print_mutex);
	printf("%lld %d died\n", get_time_in_ms() - philo.data->start_time,
		philo.id);
	pthread_mutex_unlock(&philo.data->print_mutex);
}

void	philo_take_fork(t_philo *philo)
{
	check_meal_goal(philo);
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		philo->data->is_dead = 1;
		return ;
	}
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_bool = 1;
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo->right_fork_bool = 1;
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->right_fork_bool = 1;
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_bool = 1;
		print(philo, "has taken a fork");
	}
}
