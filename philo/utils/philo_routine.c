#include "../lib/philo.h"

void	philo_eat(t_philo *philo) // yazdirma islemi eklenecek
{
	handle_dead(philo); // dead check
	last_meal_added(philo); // last meal update

	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "timestamp_in_ms %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo) // yazdirma islemi eklenecek
{
	handle_dead(philo); // dead check

	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "timestamp_in_ms %d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

// thinking state will be added
void	philo_thinking(t_philo *philo)
{
	handle_dead(philo); // dead check

	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "timestamp_in_ms %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout ,"timestamp_in_ms %d died\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}
