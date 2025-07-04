#include "../lib/philo.h"

void	philo_eat(t_philo *philo)
{
	last_meal_added(philo); // last meal update
	handle_dead(philo); // Tek philo için yazıldı

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

void	philo_dead(t_philo philo)
{
	// usleep(100); // bu kaldıralacak
	pthread_mutex_lock(&philo.data->print_mutex);
	printf("%lld 	%d died\n", get_time_in_ms() - philo.data->start_time, philo.id);
	pthread_mutex_unlock(&philo.data->print_mutex);
	
	// print(philo, "died");
}

void	philo_take_fork(t_philo *philo)
{
	handle_dead(philo);

	if (philo->data->philo_count == 1) // Tek philo için yazıldı
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		philo->data->is_dead = 1;
		return ;
	}
	
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
}
