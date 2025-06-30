/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsyn <hsyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:46:25 by huozturk          #+#    #+#             */
/*   Updated: 2025/06/30 21:50:13 by hsyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include "../lib/error.h"
#include <stdlib.h>

void	*say_hello(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	
	sync_philo_start(philo);
	while (!check_dead(philo))
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		philo_eat(philo); // eat
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(philo);
		philo_thinking(philo);
	}
	return (NULL);
}


void	init_philo(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	if (ft_atoi(argv[1], &data->philo_count)
		|| ft_atoi(argv[2], &data->time_to_die)
		|| ft_atoi(argv[3], &data->time_to_eat)
		|| ft_atoi(argv[4], &data->time_to_sleep))
		error_check(data, ERR_INVALID_ARG, NULL);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	error_check(data, ERR_MALLOC_FAIL, data->philos);
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal = get_time_in_ms();
		i++;
	}
	if (data->philo_count != data->philos[i - 1].id) // Philo eksik olustuysa hata
	{
		printf("LAST_ID: %d\n", data->philos[i - 1].id);
		exit(1);
	}
}

void	create_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count) // Philo oluşup oluşmadı mı kontrol id ile yapılabilir
	{
		pthread_create(
			&data->philos[i].thread,
			NULL,
			say_hello,
			&data->philos[i]);
	}
}

void	*monitor_test(void *argv)
{
	t_data	*datas;
	int	i;
	
	datas = (t_data *)argv;
	while (1)
	{
		i = -1;
		while (++i < datas->philo_count)
		{
			pthread_mutex_lock(&datas->philos[i].meal_mutex);
			long long last = datas->philos[i].last_meal;
			pthread_mutex_unlock(&datas->philos[i].meal_mutex);

			if (get_time_in_ms() - last > datas->time_to_die)
			{
				pthread_mutex_lock(&datas->death_mutex);
				datas->is_dead = 1; // Now protected by mutex
				pthread_mutex_unlock(&datas->death_mutex);
				philo_dead(datas->philos);
				pthread_exit(NULL);
			}
		}
	}
}

void	monitor_philo(t_data *data)
{
	pthread_create(
		&data->monitor_philo,
		NULL,
		monitor_test,
		&*data);
}

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	error_check(data, ERR_MALLOC_FAIL, data->forks);
	
	// Initialize global mutexes
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->start_flag_mutex, NULL);

	while (++i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL); // AÇILDI MI AÇILMADI MI CHECK
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		pthread_mutex_init(&data->philos[i].print_mutex, NULL);
	}

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
	}
}
