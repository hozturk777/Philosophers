#include "../lib/philo.h"
#include <stdlib.h>

static void	*say_hello(void *argv)
{
	t_philo *philo;

	philo = (t_philo *)argv;

	while (!philo->data->is_dead)
	{
		
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		printf("thread_id: %d - philo_count: %d - just EAT! ms: %lld philo_is_dead: %d", philo->id, philo->data->philo_count, get_time_in_ms() - philo->data->start_time, philo->data->is_dead);

		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time_in_ms(); // Mutex kullanılacak

		pthread_mutex_unlock(&philo->meal_mutex);
		
		usleep(philo->data->time_to_eat * 1000);
		if (philo->data->is_dead)
		{
			pthread_exit(NULL);  // Burada çıkış yap
			break;  // ya da return (NULL);
		}
		printf(" - last_meal: %d \n", get_time_in_ms() - philo->last_meal);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		usleep(200 * 1000); // Uyuma kismi olacak
	}
}

void	init_philo(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	if (ft_atoi(argv[1], &data->philo_count)
		|| ft_atoi(argv[2], &data->time_to_die)
		|| ft_atoi(argv[3], &data->time_to_eat))
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
}

void	create_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_create(
			&data->philos[i].thread,
			NULL,
			say_hello,
			&data->philos[i]);
	}
}

void	monitor_test(void *argv) // Düzenlenecek ve mutex oluşturulacak öldükten sonra race condition oluyor ve bazı threadler bittikten sonra da çalışıyor ve her philoya bakmak gerek örnek kod chatgpt'de 
{
	t_data	*datas;
	int	i;

	datas = (t_data *)argv;
	while (1)
	{
		usleep(200 * 1000);
		i = -1;
		while (++i < datas->philo_count)
		{
			pthread_mutex_lock(&datas->philos[i].meal_mutex);
			long long last = datas->philos[i].last_meal;
			pthread_mutex_unlock(&datas->philos[i].meal_mutex);
			if (get_time_in_ms() - last > datas->time_to_die)
			{
				datas->is_dead = 1; // Buraya da mutex lazım(sanırım)
				printf("last_meal: %lld\n",get_time_in_ms() -  last);
				printf("DEAAAAAAAAAAAAAAAAAAAD\n");
				pthread_exit(NULL);
			}
		}
	}
}

void	monitor_philo(t_data *data)
{
	// pthread_t philo; // struct yapisina koyulacak

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

	while (++i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
	}

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
	}
}
