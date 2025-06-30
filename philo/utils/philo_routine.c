#include "../lib/philo.h"

void	philo_eat(t_philo *philo) // yazdirma islemi eklenecek
{
	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "eating id:   %d\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo) // yazdirma islemi eklenecek
{
	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "sleeping id: %d\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

// thinking state will be added
void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "thinking id: %d\n", philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}
