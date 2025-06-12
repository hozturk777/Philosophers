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
	if (argc == 2)
	{
		init_philo(&data, argv[1]);
		init_forks(&data);
		create_philo(&data);
		cleanup(data);
		return (0);
	}
	else
	{
		printf("Invalid Argument\n");
		return (1);
	}
}
