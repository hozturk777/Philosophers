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
- Her mutex'i ` int pthread_mutex_init ` ile initialize eder.
- Left, right forklara da atamalarını yapar.

---

###		**void	monitor_philo(t_data *data) && static void	*monitor_process(void *argv)**
```c
void	*monitor_test(void *argv)
{
	t_data	*datas;
	int		i;

	datas = (t_data *)argv;
	while (1)
	{
		pthread_mutex_lock(&datas->start_flag_mutex);
		if (datas->start_flag == 1)
		{
			pthread_mutex_unlock(&datas->start_flag_mutex);	
			break ;
		}
		pthread_mutex_unlock(&datas->start_flag_mutex);
	}
	while (1)
	{
		i = -1;
		while (++i < datas->philo_count)
		{
			check_and_handle_death(datas, i);
			pthread_mutex_lock(&datas->philos[i].eat_count_mutex);
			if (datas->must_eat == datas->philos[i].eat_count) // MUTEX
				pthread_exit(NULL);
			pthread_mutex_unlock(&datas->philos[i].eat_count_mutex);
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
```

### 🔧 **Açıklama:**
- Filozofları arka planda sürekli izleyen bir gözetleme thread’idir.
- Her filozof ölüyor mu, hedef kadar yemek yedi mi diye kontrol eder.
- Simülasyon başlamadan önce, start_flag = 1 olana kadar sürekli bekler.(init_philo fonksiyonu start_flag=1 yapar.)
- `pthread_create` fonksiyonu parametre olarak posix thread'in adresini, Attribute yani thread özelliklerini, thread'in çalıştıracağı fonksiyonu ve fonksiyonun parametresini alır.
---

###		**void	create_philo(t_data *data) && static void	*philo_process(void *arg) **
```c
static void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_start_flag(philo))
			break ;
		// usleep(100);
	}
	sync_philo_start(philo);
	while (!check_dead(philo))
	{
		philo_take_fork(philo);
		philo_eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_bool = 0;
		philo->right_fork_bool = 0;
		philo_sleep(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

void	create_philo(t_data *data)
{
	int	i;

	i = -1;
	
	while (++i < data->philo_count)
	{
		pthread_create(
				&data->philos[i].thread,
				NULL,
				philo_process,
				&data->philos[i]);
	}
	set_time(data);
	pthread_mutex_lock(&data->start_flag_mutex);
	data->start_flag = 1; // MUTEX
	pthread_mutex_unlock(&data->start_flag_mutex);
}
```

### 🔧 **Açıklama:**
- `create_philo` fonksiyonu verilen philo_count kadar philoyu çalıştırıyor.
- Tüm philolar çalıştırıldıktan sonra start_flag değeri 1 olarak değiştiriliyor ve monitor_thread ve tüm threadler aynı anda çalışmaya başlıyor.
- `set_time` fonksiyonu Process'in başlangıç zamanının atamasını yapıyor.
- `sync_philo_start` fonksiyonu her thread'in başlangıç last_meal değer atamasını yapıp aynı zamanda id değeri tek olan philoları 200
---