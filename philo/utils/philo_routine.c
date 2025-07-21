/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsyn <hsyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:07:58 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/20 19:27:26 by hsyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void	philo_eat(t_philo *philo)
{
	//last_meal_added(philo); // Burada mi ?
	handle_dead(philo);
	print(philo, "is eating");
	philo->eat_count++;
	usleep(philo->data->time_to_eat * 1000);
	last_meal_added(philo); // Burada mi ?
}

void	philo_sleep(t_philo *philo)
{
	check_meal_goal(philo);
	print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	int think_time;
	check_meal_goal(philo);
	print(philo, "is thinking");
	
	if (philo->data->philo_count % 2 == 1 && philo->data->philo_count > 1)
	{
		think_time = philo->data->time_to_eat - philo->data->time_to_sleep;
		if (think_time > 0)
			usleep(think_time * 100);
		else
			usleep(100);
	}
}

void	philo_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.data->print_mutex);
	printf("%lld %d died\n", get_time_in_ms() - philo.data->start_time, philo.id);
	pthread_mutex_unlock(&philo.data->print_mutex);
}

void	philo_take_fork(t_philo *philo)
{
	handle_dead(philo);
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
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
	}
}
