# Philosophers Project - Evolution Preparation

---

### 	void	ft_usleep(int wait_time)
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

### 	init_philo(t_data *data, char *argv[], int argc)
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