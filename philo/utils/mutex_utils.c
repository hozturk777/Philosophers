#include "../lib/philo.h"
#include <stdio.h>

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);

	return (0);
}

int	check_start_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_flag_mutex);
	if (philo->data->start_flag)
	{
		pthread_mutex_unlock(&philo->data->start_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->start_flag_mutex);
	
	return (0);
}
