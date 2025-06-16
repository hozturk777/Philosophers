#include "../lib/philo.h"
#include <stdio.h>

long long	get_time_in_ms(void) // ARAŞTIRILACAK
{
	struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)(ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL);
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
	if (argc == 4)
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
		}
		cleanup(data);
		return (0);
	}
	else
	{
		printf("Invalid Argument\n");
		return (1);
	}
}
