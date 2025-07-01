# Philosophers Project - TODO List 📋

## 📅 **Kontrol Tarihi:** 1 Temmuz 2025

PDF gereksinimlerine göre kodumuzda eksik olan ve düzeltilmesi gereken konular:

---

## 🔧 **1. LOG FORMAT DÜZELTMESİ (KRİTİK)**

### ❌ **Mevcut Durum:**
```c
// philo_routine.c - Yanlış format
fprintf(stdout, "eating id:   %d\n", philo->id);
fprintf(stdout, "sleeping id: %d\n", philo->id);
fprintf(stdout, "thinking id: %d\n", philo->id);
fprintf(stdout ,"dead id: %d\n", philo->id);
```

### ✅ **PDF Gereksinimleri:**
```c
// Doğru format (PDF sayfa 7):
"timestamp_in_ms X has taken a fork"
"timestamp_in_ms X is eating"
"timestamp_in_ms X is sleeping" 
"timestamp_in_ms X is thinking"
"timestamp_in_ms X died"
```

### 🎯 **Yapılacaklar:**
- [ ] `philo_routine.c` dosyasındaki tüm print formatlarını PDF'ye uygun şekilde düzelt
- [ ] Timestamp eklenmesi (get_time_in_ms() - start_time kullan)
- [ ] "has taken a fork" mesajı eklenmesi
- [ ] "is eating/sleeping/thinking/died" formatına geçiş

---

## 🔧 **2. ÇATAL ALMA LOGu EKSİK (KRİTİK)**

### ❌ **Mevcut Durum:**
```c
// philo_utils.c - Çatal alındığında log yok
pthread_mutex_lock(philo->right_fork);
pthread_mutex_lock(philo->left_fork);
// ❌ Log mesajı eksik!
```

### ✅ **PDF Gereksinimleri:**
```c
// Her çatal alındığında log olmalı
pthread_mutex_lock(philo->right_fork);
printf("timestamp_in_ms %d has taken a fork\n", philo->id);
pthread_mutex_lock(philo->left_fork); 
printf("timestamp_in_ms %d has taken a fork\n", philo->id);
```

### 🎯 **Yapılacaklar:**
- [ ] `say_hello()` fonksiyonunda fork lock'tan sonra log ekle
- [ ] 2 ayrı çatal için 2 ayrı "has taken a fork" mesajı

---

## 🔧 **3. ÖLÜM MESAJI GECİKME (KRİTİK)**

### ❌ **Mevcut Durum:**
```c
// monitor_test() - Ölüm kontrolü yavaş olabilir
if (get_time_in_ms() - last > datas->time_to_die)
```

### ✅ **PDF Gereksinimleri:**
- **"A message announcing a philosopher's death must be displayed within 10 ms"**

### 🎯 **Yapılacaklar:**
- [ ] Monitor thread polling süresini optimize et
- [ ] Ölüm algılandığında immediate print
- [ ] 10ms kısıtını test et

---

## 🔧 **4. 5. ARGÜMAN DESTEĞİ EKSİK**

### ❌ **Mevcut Durum:**
```c
// main.c - Sadece 4 argüman kontrolü
if (argc == 5)
```

### ✅ **PDF Gereksinimleri:**
```bash
# 5. argüman: number_of_times_each_philosopher_must_eat (opsiyonel)
./philo 5 800 200 200 7  # 7 kez yedikten sonra dursun
```

### 🎯 **Yapılacaklar:**
- [ ] `main()` fonksiyonunda `argc == 6` kontrolü ekle
- [ ] `t_data` struct'ına `must_eat_count` field'ı ekle
- [ ] Her filozof yemek sayısını takip etsin (`eat_count`)
- [ ] Tüm filozoflar gerekli sayıda yediğinde simülasyon dursun

---

## 🔧 **5. TEK FİLOZOF DURUMU (ÖNEMLİ)**

### ❌ **Mevcut Durum:**
```c
// Tek filozof için özel durum kontrolü yok
```

### ✅ **PDF Gereksinimleri:**
- **"If there is only one philosopher, they will have access to just one fork."**
- Tek filozof yemek yiyemez, ölmeli

### 🎯 **Yapılacaklar:**
- [ ] `philo_count == 1` kontrolü ekle
- [ ] Tek filozof durumunda özel handling
- [ ] Tek çatal ile yemek yiyememe logica'sı

---

## 🔧 **6. DATA RACES KONTROL (KRİTİK)**

### ❌ **Potansiyel Problem:**
- Print mutex'ler individual, global olmalı mı?

### ✅ **PDF Gereksinimleri:**
- **"Your program must not have any data races."**
- **"A displayed state message should not overlap with another message."**

### 🎯 **Yapılacaklar:**
- [ ] Tüm print'ler için tek global print_mutex kullan
- [ ] Helgrind ile final test
- [ ] Message overlap kontrolü

---

## 🔧 **7. ARGÜMAN VALİDASYONU GELİŞTİR**

### ❌ **Mevcut Durum:**
```c
// utils.c - Basit pozitif sayı kontrolü
if (*res <= 0)
    return (1);
```

### ✅ **Geliştirmeler:**
- Maksimum filozof sayısı kontrolü (çok fazla olmasın)
- Time değerleri için min/max kontroller
- Edge case'ler için test

### 🎯 **Yapılacaklar:**
- [ ] Max philosopher count limit (örn: 200)
- [ ] Min time values (örn: time_to_die >= 60ms)
- [ ] Edge case testleri

---

## 🔧 **8. MEMORY CLEANUP GELİŞTİR**

### ❌ **Kontrol Edilmeli:**
- Mutex destroy eksik olabilir

### 🎯 **Yapılacaklar:**
- [ ] `cleanup()` fonksiyonunu kontrol et
- [ ] Tüm mutex'ler destroy ediliyor mu?
- [ ] Memory leak testi (valgrind)

---

## 🔧 **9. MAKEFILE GELİŞTİR**

### ✅ **PDF Gereksinimleri:**
- **"must contain at least the rules $(NAME), all, clean, fclean and re"**
- **"-Wall, -Wextra, and -Werror"**

### 🎯 **Kontrol:**
- [x] NAME rule ✅
- [x] all rule ✅  
- [x] clean rule ✅
- [x] fclean rule ✅
- [x] re rule ✅
- [x] -Wall -Wextra -Werror ✅

---

## 📊 **ÖNCELİK SIRASI**

### 🔴 **KRİTİK (Hemen Yapılmalı):**
1. **Log Format Düzeltmesi** - PDF compliance
2. **"has taken a fork" Log Ekleme** - PDF requirement
3. **5. Argüman Desteği** - PDF requirement
4. **Tek Filozof Durumu** - Edge case

### 🟡 **ÖNEMLİ (Yakında):**
5. **Ölüm Mesajı 10ms** - Performance requirement
6. **Global Print Mutex** - Race condition önleme

### 🟢 **İYİLEŞTİRME (Son):**
7. **Argüman Validasyonu** - Robustness
8. **Memory Cleanup** - Clean code

---

## 🎯 **HEDEF DURUM**

```bash
# Perfect working example:
./philo 4 310 200 100
0 1 has taken a fork
0 1 has taken a fork  
0 1 is eating
0 3 has taken a fork
200 1 is sleeping
200 3 has taken a fork
200 3 is eating
```

**📅 Hedef Tamamlama:** 2 Temmuz 2025  
**🎯 Durum:** PDF compliance %100
