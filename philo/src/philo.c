#include "../lib/philo.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_data	data;

	data.philos = NULL;
	if (argc == 2)
	{
		init_philo(&data, argv[1]);
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