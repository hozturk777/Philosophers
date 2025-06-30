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

void handle_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex); // Func icerisinde yazdirma ve olme islemi
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);			
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void	last_meal_added(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
}