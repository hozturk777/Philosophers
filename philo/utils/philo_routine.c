#include "../lib/philo.h"

void	philo_eat(t_philo *philo)
{
	last_meal_added(philo); // last meal update
	print(philo, "is eating");
	philo->eat_count++;
	usleep(philo->data->time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	print(philo, "is thinking");
}

void	philo_dead(t_philo *philo)
{
	print(philo, "died");
}

void	philo_take_fork(t_philo *philo)
{
	// handle_dead(philo);
	// check_meal_goal(philo); // Check if meal goal reached


	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
}
