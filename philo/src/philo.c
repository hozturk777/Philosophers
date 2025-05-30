#include "../lib/philo.h"
#include <stdio.h>
#include <stdlib.h>

void	*say_hello(void *argv)
{
	t_philo *philo;

	philo = (t_philo *)argv;
	printf("thread_id: %d \\ \n", philo->id);
	printf("thread_left_fork: %s \\ \n", philo->left_fork);

}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i = 0;

	if (argc == 2)
	{
		if (ft_atoi(argv[1], &data.philo_count))
		{
			printf("hata\n");
			return (1);
		}
		printf("count: %d\n", data.philo_count);
		data.philos = malloc(sizeof(t_philo) * data.philo_count);
		while (i < data.philo_count)
		{
			data.philos[i].id = i + 1;
			i++;
		}

		i = 0;
		while (i < data.philo_count)
		{
			pthread_create(&data.philos[i].thread, NULL, say_hello, &data.philos[i]);
			i++;
		}

		i = 0;
		while (i < data.philo_count)
		{
			pthread_join(data.philos[i].thread, NULL);
			i++;
		}
		free(data.philos);
		return (0);
	}
	else
	{
		printf("Invalid Argument");
		return (1);
	}
}