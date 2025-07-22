#include "../lib/philo.h"

void	set_last_meal(t_data *data, int philo_index)
{
	data->last_meal_philo = data->philos[philo_index].last_meal;
}

void	check_and_handle_death(t_data *data, int philo_index)
{
	if (get_time_in_ms() - data->last_meal_philo > data->time_to_die)
	{
		set_death_status(data, philo_index);
		pthread_exit(NULL);
	}
}

void	set_death_status(t_data *data, int philo_index)
{
	data->is_dead = 1;
	data->dead_index = philo_index;
}
