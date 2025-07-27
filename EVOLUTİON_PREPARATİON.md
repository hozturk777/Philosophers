# Philosophers Project - Evolution Preparation

---

###		**void	ft_usleep(int wait_time)**
```c
void	ft_usleep(int wait_time)
{
	unsigned long long	time;

	time = get_time_in_ms();
	while (get_time_in_ms() - time < (unsigned long long)wait_time)
		usleep(100);
}
```

### 🔧 **Açıklama:**
- Neden usleep(wait_time * 1000) yapmıyoruz?
- Çünkü usleep() fonksiyonu sistem tarafından biraz gecikmeli uyanabilir. Yani:
- Beklemesi gereken süreyi tam olarak beklemeyebilir.
- Bu da filozof projesi gibi zaman hassas uygulamalarda hata yaratır.

---

###		**void	init_philo(t_data *data, char *argv[], int argc)**
```c
void	init_philo(t_data *data, char *argv[], int argc)
{
	int	i;

	i = 0;
	parse_args(argv, data, argc);
	data->forks = NULL;
	data->philos = NULL;
	data->is_dead = 0;
	data->dead_index = -1;
	data->start_flag = 0;
	data->philos = ft_calloc(sizeof(t_philo), data->philo_count);
	error_check(data, ERR_MALLOC_FAIL, data->philos);
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal = get_time_in_ms();
		data->philos[i].eat_count = 0;
		data->philos[i].left_fork_bool = 0;
		data->philos[i].right_fork_bool = 0;
		i++;
	}
	if ((data->philo_count != data->philos[i - 1].id))
		error_check(data, ERR_THREAD_FAIL, NULL);
}
```

### 🔧 **Açıklama:**
- Bu fonksiyon, her filozofun doğum yeridir
- Her filozof için dinamik olarak bellek yer tahsis eder.
- Her filozofun ve datanın başlangıç değer atamasını yapar.

---

###		**void	init_forks(t_data *data)**
```c
void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	error_check_mutex(data, pthread_mutex_init(&data->death_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->start_flag_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->check_meal_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->print_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->last_meal_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->must_meal_mutex, NULL));
	error_check_mutex(data, pthread_mutex_init(&data->meal_mutex, NULL));


	data->forks = ft_calloc(data->philo_count, sizeof(pthread_mutex_t));
	error_check(data, ERR_MALLOC_FAIL, data->forks);
	while (++i < data->philo_count)
	{
		error_check_mutex(data, pthread_mutex_init(&data->forks[i],
				NULL));
		error_check_mutex(data, pthread_mutex_init(&data->philos[i].eat_count_mutex,
				NULL));
	}
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
	}
}
```

### 🔧 **Açıklama:**
- Bu fonksiyon, her fork(çatal) mutex'in ve diğer mutexlerin doğum yeridir
- Her fork için dinamik olarak bellek yer tahsis eder.
- Her mutex'i ```c int pthread_mutex_init ``` ile initialize eder.
- Left, right forklara da atamalarını yapar.

---