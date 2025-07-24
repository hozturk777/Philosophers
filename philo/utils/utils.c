/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:08:03 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/24 18:43:20 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include "../lib/error.h"
#include <stdio.h>
#include <unistd.h>

static int	check_long(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	if (i >= 11)
		return (1);
	return (0);
}

int	ft_atoi(char *str, int *res)
{
	int	i;
	int	sign;

	*res = 0;
	i = 0;
	sign = 1;
	if (check_long(str))
		return (1);
	while (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i++) == '-')
			sign *= -1;
	}
	while ((*(str + i) >= '0' && *(str + i) <= '9') || *(str + i) != '\0')
	{
		if (!(*(str + i) >= '0' && *(str + i) <= '9'))
			error_check(NULL, ERR_ATOI_FAIL, NULL);
		else
			*res = (*res * 10) + (*(str + i) - '0');
		i++;
	}
	*res *= sign;
	if (*res <= 0)
		error_check(NULL, ERR_ATOI_FAIL, NULL);
	return (0);
}

void	sync_philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	
	if (philo->id % 2 != 0)
		ft_usleep(200);
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
			error_check(data, ERR_INVALID_ARG, NULL);
	}
}

void	print(t_philo *philo, char *str)
{
	handle_dead(philo);
	check_meal_goal(philo);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms() - philo->data->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
