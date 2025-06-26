#include "../lib/philo.h"
#include <stdio.h>

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_mutex2);
	if (philo->data->is_dead)
		return (1);
	printf("CHECK_DEAD_ID: %d\n", philo->id);
	pthread_mutex_unlock(&philo->dead_mutex2);
}