#include "../lib/philo.h"

void	philo_eat(t_philo *philo) // must eat oldugunda program sonlaniyor ama handle_dead sayesinde
{
	handle_dead(philo); // dead check
	check_meal_goal(philo);
	last_meal_added(philo); // last meal update

	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "%lld %d is eating\n", get_time_in_ms() - philo->data->start_time, philo->id);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo) // yazdirma islemi eklenecek
{
	handle_dead(philo); // dead check

	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "%lld %d is sleeping\n",get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

// thinking state will be added
void	philo_thinking(t_philo *philo)
{
	handle_dead(philo); // dead check

	pthread_mutex_lock(&philo->print_mutex);
	fprintf(stdout, "%lld %d is thinking\n", get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d died\n", get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}
