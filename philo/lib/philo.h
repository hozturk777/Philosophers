#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_philo
{
	int	id;
	pthread_t thread;
	long long last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutext;
	t_philo			*philos;
}	t_data;

int ft_atoi(char *str, int *res);

#endif