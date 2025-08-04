/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:33:28 by huozturk          #+#    #+#             */
/*   Updated: 2025/08/04 19:34:19 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include "../lib/error.h"


void	init_philo(t_data *data, char *argv[], int argc)
{
	int	i;

	i = 0;
	parse_args(argv, data, argc);
	data->forks = NULL;
	data->philos = NULL;
	data->is_dead = 0;
	data->dead_index = -1;
	data->start_flag = 0;
	data->must_meal_num = 0;
	data->philos = ft_calloc(sizeof(t_philo), data->philo_count);
	error_check(data, ERR_MALLOC_FAIL, data->philos);
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal = get_time_in_ms();
		data->philos[i].eat_count = 0;
		data->philos[i].left_fork_bool = 0;
		data->philos[i].right_fork_bool = 0;
		i++;
	}
	if ((data->philo_count != data->philos[i - 1].id))
		error_check(data, ERR_THREAD_FAIL, NULL);
}


void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	error_check_mutex(data, pthread_mutex_init(&data->death_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->start_flag_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->check_meal_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->print_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->must_meal_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->meal_mutex, NULL));
	data->forks = ft_calloc(data->philo_count, sizeof(pthread_mutex_t));
	error_check(data, ERR_MALLOC_FAIL, data->forks);
	while (++i < data->philo_count)
	{
		error_check_mutex(data, pthread_mutex_init(&data->forks[i],
				NULL));
		error_check_mutex(data, pthread_mutex_init(&data->philos[i].eat_count_mutex,
				NULL));
	}
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
	}
}