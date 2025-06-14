#include "../lib/philo.h"
#include <stdlib.h>

static void	*say_hello(void *argv)
{
	t_philo *philo;

	philo = (t_philo *)argv;

	while (1) // Burada !philo.dead kosulu olacak
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
		printf("thread_id: %d  -  philo_count: %d \\ \n", philo->id, philo->data->philo_count);
		printf("just EAT! ms: %lld\n", get_time_in_ms() - philo->data->start_time);
		usleep(philo->data->time_to_eat * 1000);

		philo->last_meal = get_time_in_ms() -  philo->data->start_time;

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		usleep(100); // Uyuma kismi olacak
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
		i++;
	}
}

void	create_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_create(
			&data->philos[i].thread,
			NULL,
			say_hello,
			&data->philos[i]);
	i = -1;
	while (++i < data->philo_count)  // Bekleme fonksiyonu olusturulacak
		pthread_join(
			data->philos[i].thread,
			NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	error_check(data, ERR_MALLOC_FAIL, data->forks);

	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
	}
}
