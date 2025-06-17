#include "../lib/philo.h"
#include <stdio.h>

long long	get_time_in_ms(void) // ARAŞTIRILACAK
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}


void	set_time(t_data *data)
{
	data->start_time = get_time_in_ms();
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int i = -1;

	data.philos = NULL;
	data.is_dead = 0;
	set_time(&data);
	if (argc == 5)
	{
		init_philo(&data, argv);
		init_forks(&data);
		create_philo(&data);
		monitor_philo(&data);
		while (++i < data.philo_count)  // Bekleme fonksiyonu olusturulacak
		{
			pthread_join(
				data.philos[i].thread,
				NULL);
			// if(data)
			// {
			// 	// printf("\nis_dead_MAİN: %d\n", data.is_dead);
			// 	// pthread_exit(NULL);
			// 	break;
			// }
		}
		pthread_join(
			data.monitor_philo,
			NULL);
		cleanup(data);
		return (0);
	}
	else
	{
		printf("Invalid Argument\n");
		return (1);
	}
}
