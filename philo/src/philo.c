#include "../lib/philo.h"
#include <stdio.h>

long long	get_time_in_ms(void)
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
	if (argc == 4)
	{
		init_philo(&data, argv);
		init_forks(&data);
		create_philo(&data);
		//while (1)
		//{
		//	if (get_time_in_ms() - data.philos->last_meal > data.time_to_die)
		//	{
		//		printf("YAT ASSA\n");
		//		printf("last_meal: %lld\n", data.philos->last_meal);
		//		printf("time_to_die: %lld\n", data.time_to_die);
		//		printf("current_time: %lld\n", get_time_in_ms() - data.start_time);
		//		usleep(90000);
		//	}
		//}
		monitor_philo(&data);
		while (++i < data.philo_count)  // Bekleme fonksiyonu olusturulacak
		{
			
			pthread_join(
				data.philos[i].thread,
				NULL);
		}			
		//cleanup(data);
		return (0);
	}
	else
	{
		printf("Invalid Argument\n");
		return (1);
	}
}
