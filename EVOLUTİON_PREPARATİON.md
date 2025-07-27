# Philosophers Project - Evolution Preparation

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