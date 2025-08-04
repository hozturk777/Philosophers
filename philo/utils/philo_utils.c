/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:46:25 by huozturk          #+#    #+#             */
/*   Updated: 2025/08/04 19:37:52 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include "../lib/error.h"
#include <unistd.h>

static void	one_philo_handle(t_philo *philo)
{
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
}

static void process_loop(t_philo *philo)
{
	while (!check_dead(philo))
	{
		if(philo->data->must_eat != -1 && check_meal_goal(philo)) // handle dead
			break;
		if (handle_dead(philo))
			break;
		philo_take_fork(philo);
		philo_eat(philo);
		if (philo->right_fork_bool)
			pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_bool = 0;
		if (philo->left_fork_bool)
			pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_bool = 0;
		if(philo->data->must_eat != -1 && check_meal_goal(philo)) // handle dead
			break;;
		if (handle_dead(philo))
			break;
		philo_sleep(philo);
		if (handle_dead(philo))
			break;
		philo_thinking(philo);
	}
}

static void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_start_flag(philo))
			break ;
		usleep(100);
	}
	one_philo_handle(philo);
	sync_philo_start(philo);
	process_loop(philo);
	return (NULL);
}

void	create_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(
				&data->philos[i].thread,
				NULL,
				philo_process,
				&data->philos[i]))
		{
			pthread_mutex_lock(&data->start_flag_mutex);
			data->start_flag = 1;
			pthread_mutex_unlock(&data->start_flag_mutex);
			pthread_mutex_lock(&data->death_mutex);
			data->is_dead = 2;
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
	}
	set_time(data);
	pthread_mutex_lock(&data->start_flag_mutex);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->start_flag_mutex);
}
