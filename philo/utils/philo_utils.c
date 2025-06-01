#include "../lib/philo.h"
#include <stdlib.h>

static void	*say_hello(void *argv)
{
	t_philo *philo;

	philo = (t_philo *)argv;

	if (philo->left_fork != philo->right_fork) // tek thread geldiğinde left_fork 0.indeks'de right_fork'da 0.indeks'de olduğu için thread kendini deadlock'a sokuyordu
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
		pthread_mutex_lock(philo->left_fork);
	printf("thread_id: %d  -  philo_count: %d \\ \n", philo->id, philo->data->philo_count);
}

void	init_philo(t_data *data, char *philo_count_av)
{
	int	i;

	i = 0;
	if (ft_atoi(philo_count_av, &data->philo_count))
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
	while (++i < data->philo_count)
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
