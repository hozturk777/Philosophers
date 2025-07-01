#include "../lib/philo.h"

void	philo_eat(t_philo *philo)
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

void	philo_sleep(t_philo *philo)
{
	handle_dead(philo); // dead check

	print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	handle_dead(philo);

	print(philo, "is thinking");
}

void	philo_dead(t_philo *philo)
{
	print(philo, "died");
}

void	philo_take_fork(t_philo *philo)
{
	handle_dead(philo);

	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
}
