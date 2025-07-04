#include "../lib/philo.h"

void	*monitor_test(void *argv)
{
	t_data	*datas;
	int	i;
	
	datas = (t_data *)argv;
	while (1)
	{
		i = -1;
		while (++i < datas->philo_count)
		{
			pthread_mutex_lock(&datas->philos[i].meal_mutex);
			long long last = datas->philos[i].last_meal;
			pthread_mutex_unlock(&datas->philos[i].meal_mutex);

			if (get_time_in_ms() - last > datas->time_to_die)
			{
				pthread_mutex_lock(&datas->death_mutex);
				datas->is_dead = 1; // Now protected by mutex
				pthread_mutex_unlock(&datas->death_mutex);
				philo_dead(datas->philos[i]);
				pthread_exit(NULL);
			}
			else
			{
				if (datas->must_eat == datas->philos[i].eat_count)
					pthread_exit(NULL);
			}
		}
	}
}

void	monitor_philo(t_data *data)
{
	pthread_create(
		&data->monitor_philo,
		NULL,
		monitor_test,
		&*data);
}