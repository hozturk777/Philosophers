#include "../lib/philo.h"
#include "../lib/error.h"

int ft_atoi(char *str, int *res)
{
	int	i;
	int	sign;

	*res = 0;
	i = 0;
	sign = 1;
	while (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			sign *= -1;
		i++;
	}
	while ((*(str + i) >= '0' && *(str + i) <= '9') || *(str + i) != '\0')
	{
		if (!(*(str + i) >= '0' && *(str + i) <= '9'))
			return (1);	// Buralara check error'a gönderip error message dönülmeli
		else
			*res = (*res * 10) + (*(str + i) - '0');
		i++;
	}
	*res *= sign;
	if (*res <= 0)
		return (1);	// Buralara check error'a gönderip error message dönülmeli
	return (0);
}

void	sync_philo_start(t_philo *philo)
{
	while (1)
	{
		if (check_start_flag(philo))
			break;
	}
	
	if (philo->id % 2 != 0)
		usleep(100);
}

void	parse_args(char *argv[], t_data *data, int argc)
{
	if (argc == 5)
	{
		if (ft_atoi(argv[1], &data->philo_count)
			|| ft_atoi(argv[2], &data->time_to_die)
			|| ft_atoi(argv[3], &data->time_to_eat)
			|| ft_atoi(argv[4], &data->time_to_sleep))
				error_check(data, ERR_INVALID_ARG, NULL);
		data->must_eat = -1;
	}
	else
	{
		if (ft_atoi(argv[1], &data->philo_count)
			|| ft_atoi(argv[2], &data->time_to_die)
			|| ft_atoi(argv[3], &data->time_to_eat)
			|| ft_atoi(argv[4], &data->time_to_sleep)
			|| ft_atoi(argv[5], &data->must_eat))
				error_check(data, ERR_INVALID_ARG, NULL);  // ./philo 400 200 200 3'de fork yazdırıyo // atoi'de max int limit eklenecek // yeme işlemi bittikten sonra fork almaya devam ediyo
	}	
}

void	print(t_philo *philo, char *str)
{
	handle_dead(philo);
	
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->print_mutex);

}