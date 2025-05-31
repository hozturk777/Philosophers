#include "../lib/philo.h"
#include <stdlib.h>

static void	*say_hello(void *argv)
{
	t_philo *philo;

	philo = (t_philo *)argv;

	printf("thread_id: %d  -  philo_count: %d \\ \n", philo->id, philo->data->philo_count);

}

int	init_philo(t_data *data, char *philo_count_av)
{
	int	i;

	i = 0;
	if (ft_atoi(philo_count_av, &data->philo_count))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);

	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		i++;
	}
	return (0);
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
