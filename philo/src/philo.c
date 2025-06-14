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

	data.philos = NULL;
	set_time(&data);
	if (argc == 4)
	{
		init_philo(&data, argv);
		init_forks(&data);
		create_philo(&data);
		//if (get_time_in_ms() - data.start_time > data.time_to_die)
		//{
		//	printf("YAT ASSA\n");
		//	printf("last_meal: %lld\n", data.philos->last_meal);
		//	printf("time_to_die: %lld\n", data.time_to_die);
		//	printf("current_time: %lld\n", get_time_in_ms() - data.start_time);
		//}
		//cleanup(data);
		return (0);
	}
	else
	{
		printf("Invalid Argument\n");
		return (1);
	}
}
