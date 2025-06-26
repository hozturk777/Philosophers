#include "../lib/philo.h"
#include <stdio.h>

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->dead_mutex);

	pthread_mutex_lock(&philo->print_mutex); // print için fonk oluşturup parametre olarak istediğin string verilecek fprintf kullan stderr stdout
	printf("CHECK_DEAD_ID: %d\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);

}

