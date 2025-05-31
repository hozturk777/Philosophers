#include "../lib/philo.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i = 0;

	if (argc == 2)
	{
		if (init_philo(&data, argv[1])) // error control oluşturulacak(exit kullan).
		{
			printf("hata\n");
			return (1);
		}
		create_philo(&data);

		free(data.philos); // error control'e direkt NULL gönderip freelenecek
		return (0);
	}
	else
	{
		printf("Invalid Argument\n");
		return (1);
	}
}