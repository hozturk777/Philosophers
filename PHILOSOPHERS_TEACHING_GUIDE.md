# Philosophers Project - Öğretim Rehberi 📚

## 📋 **Proje Genel Bakış**

Bu proje, klasik **Dining Philosophers** probleminin C dilinde POSIX threads kullanarak implementasyonudur. Thread synchronization, mutex kullanımı ve race condition prevention konularını öğretir.

---

## 🧵 **Temel Kavramlar (Öğrenmesi Gerekenler)**

### **1. Thread Nedir?**
```c
pthread_t thread;  // Thread tanımlayıcısı
```
- **Process**: Bağımsız çalışan program (ayrı memory space)
- **Thread**: Process içinde çalışan hafif işlem (shared memory)
- **Avantaj**: Paralel işlem, hızlı context switch
- **Dezavantaj**: Race condition riski

### **2. POSIX Threads (pthread)**
```c
#include <pthread.h>

// Thread oluşturma
pthread_create(&thread, NULL, function, argument);

// Thread'in bitmesini bekleme  
pthread_join(thread, NULL);

// Thread'den çıkış
pthread_exit(NULL);
```

### **3. Mutex (Mutual Exclusion)**
```c
pthread_mutex_t mutex;

// Initialize
pthread_mutex_init(&mutex, NULL);

// Lock (kritik bölge girişi)
pthread_mutex_lock(&mutex);
// Kritik kod buraya...
pthread_mutex_unlock(&mutex);

// Destroy
pthread_mutex_destroy(&mutex);
```

**Neden Gerekli?** 
- Shared data'ya aynı anda erişimi önler
- Race condition'u engeller
- Data consistency sağlar

### **4. Race Condition**
```c
// ❌ Tehlikeli kod (race condition)
global_counter++;  // Thread-unsafe

// ✅ Güvenli kod  
pthread_mutex_lock(&mutex);
global_counter++;  // Thread-safe
pthread_mutex_unlock(&mutex);
```

---

## 🏗️ **Proje Mimarisi**

```
philosophers/philo/
├── src/philo.c              # Ana program
├── utils/
│   ├── philo_utils.c        # Filozof yönetimi
│   ├── philo_routine.c      # Filozof davranışları  
│   ├── mutex_utils.c        # Thread güvenlik
│   ├── monitor.c            # Ölüm kontrolü
│   ├── helpers.c            # Yardımcı fonksiyonlar
│   └── utils.c              # Genel utilities
├── error/error_handle.c     # Hata yönetimi
└── lib/
    ├── philo.h              # Ana header
    └── error.h              # Hata kodları
```

---

## 📊 **Veri Yapıları**

### **Filozof Struct'ı:**
```c
typedef struct s_philo {
    int    id;                    // Filozof numarası (1-N)
    int    eat_count;             // Kaç kez yediği
    pthread_t thread;             // Thread handle'ı
    long long last_meal;          // Son yemek zamanı (ms)
    pthread_mutex_t *left_fork;   // Sol çatal (pointer)
    pthread_mutex_t *right_fork;  // Sağ çatal (pointer)
    pthread_mutex_t meal_mutex;   // Last_meal koruması
    t_data *data;                 // Global data'ya referans
} t_philo;
```

### **Global Data Struct'ı:**
```c
typedef struct s_data {
    int philo_count;              // Filozof sayısı
    int time_to_die;              // Ölme süresi (ms)
    int time_to_eat;              // Yeme süresi (ms) 
    int time_to_sleep;            // Uyku süresi (ms)
    int must_eat;                 // Minimum yeme sayısı (-1 = sınırsız)
    int is_dead;                  // Global ölüm flag'ı
    long long start_time;         // Başlangıç zamanı
    
    pthread_mutex_t *forks;       // Çatal array'i
    pthread_mutex_t death_mutex;  // Ölüm kontrolü
    pthread_mutex_t print_mutex;  // Konsol çıktısı
    t_philo *philos;              // Filozof array'i
    pthread_t monitor_philo;      // Monitor thread
} t_data;
```

---

## 🔄 **Program Akışı (Hiyerarşik)**

### **1. main() - Program Başlangıcı**
```c
int main(int argc, char *argv[]) {
    t_data data;
    
    // 1. Argüman kontrolü (5 veya 6 parametre)
    init_philo(&data, argv, argc);    // Filozof struct'larını oluştur
    init_forks(&data);                // Mutex'leri initialize et
    monitor_philo(&data);             // Monitor thread'i başlat
    set_time(&data);                  // Başlangıç zamanını kaydet
    create_philo(&data);              // Filozof thread'lerini oluştur
    philo_join(&data);                // Tüm thread'lerin bitmesini bekle
    cleanup(&data);                   // Memory'yi temizle
    return (0);
}
```

### **2. init_philo() - Filozof Yapılarını Oluştur**
```c
void init_philo(t_data *data, char *argv[], int argc) {
    parse_args(argv, data, argc);     // Argümanları parse et
    
    // Memory allocation
    data->philos = ft_calloc(sizeof(t_philo), data->philo_count);
    
    // Her filozof için
    for (int i = 0; i < data->philo_count; i++) {
        data->philos[i].id = i + 1;
        data->philos[i].data = data;
        data->philos[i].last_meal = get_time_in_ms();
        data->philos[i].eat_count = 0;
    }
}
```

### **3. init_forks() - Mutex Sistemini Kur**
```c
void init_forks(t_data *data) {
    // Global mutex'leri initialize et
    pthread_mutex_init(&data->death_mutex, NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    
    // Çatal array'ini oluştur
    data->forks = ft_calloc(data->philo_count, sizeof(pthread_mutex_t));
    
    // Her çatal için mutex initialize et
    for (int i = 0; i < data->philo_count; i++) {
        pthread_mutex_init(&data->forks[i], NULL);
        pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
    }
    
    // Çatal pointerlarını ata (circular arrangement)
    for (int i = 0; i < data->philo_count; i++) {
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
    }
}
```

### **4. create_philo() - Thread'leri Başlat**
```c
void create_philo(t_data *data) {
    for (int i = 0; i < data->philo_count; i++) {
        pthread_create(&data->philos[i].thread, NULL, say_hello, &data->philos[i]);
    }
}
```

---

## 🧠 **Filozof Thread'i Davranışı**

### **say_hello() - Ana Filozof Loop'u**
```c
static void *say_hello(void *arg) {
    t_philo *philo = (t_philo *)arg;
    
    // Başlangıç senkronizasyonu bekle
    while (!check_start_flag(philo))
        usleep(100);
    
    sync_philo_start(philo);  // Çift ID'liler 500µs bekle (deadlock önleme)
    
    // Ana yaşam döngüsü
    while (!check_dead(philo)) {
        philo_take_fork(philo);    // Çatal al
        philo_eat(philo);          // Ye
        // Çatalları bırak
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        philo_sleep(philo);        // Uyu
        philo_thinking(philo);     // Düşün
    }
    return (NULL);
}
```

### **Kritik Fonksiyonlar:**

#### **philo_take_fork() - Deadlock Prevention**
```c
void philo_take_fork(t_philo *philo) {
    // Tek filozof edge case
    if (philo->data->philo_count == 1) {
        pthread_mutex_lock(philo->left_fork);
        print(philo, "has taken a fork");
        pthread_mutex_unlock(philo->left_fork);
        philo->data->is_dead = 1;  // Tek çatalla yemek yiyemez
        return;
    }
    
    // Deadlock önleme: Pointer address'e göre sıralama
    if (philo->left_fork < philo->right_fork) {
        pthread_mutex_lock(philo->left_fork);
        print(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print(philo, "has taken a fork");
    } else {
        pthread_mutex_lock(philo->right_fork);
        print(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print(philo, "has taken a fork");
    }
}
```

#### **philo_eat() - Yemek Yeme**
```c
void philo_eat(t_philo *philo) {
    last_meal_added(philo);        // Son yemek zamanını güncelle
    print(philo, "is eating");
    philo->eat_count++;            // Yemek sayacını artır
    usleep(philo->data->time_to_eat * 1000);  // Yeme süresini bekle
}
```

---

## 👁️ **Monitor Thread - Ölüm Kontrolü**

### **monitor_test() - Sürekli Kontrol**
```c
void *monitor_test(void *argv) {
    t_data *datas = (t_data *)argv;
    datas->start_flag = 1;  // Tüm thread'leri başlat
    
    while (1) {
        for (int i = 0; i < datas->philo_count; i++) {
            set_last_meal(datas, i);           // Thread-safe last_meal okuma
            check_and_handle_death(datas, i);  // Ölüm kontrolü
            
            // Yemek hedefi kontrolü
            if (datas->must_eat == datas->philos[i].eat_count)
                pthread_exit(NULL);
        }
        usleep(100);  // 100µs polling rate
    }
}
```

### **Ölüm Tespiti:**
```c
void check_and_handle_death(t_data *data, int philo_index) {
    if (get_time_in_ms() - data->last_meal_philo > data->time_to_die) {
        set_death_status(data, philo_index);  // Global death flag set
        handle_dead(data->philos);            // Ölüm mesajı
        pthread_exit(NULL);
    }
}
```

---

## 🔐 **Thread Safety Stratejileri**

### **1. Mutex Hierarchy**
```c
// Global mutex'ler
pthread_mutex_t death_mutex;      // is_dead flag koruması
pthread_mutex_t print_mutex;      // printf race condition önleme
pthread_mutex_t start_flag_mutex; // Başlangıç senkronizasyonu

// Per-philosopher mutex
pthread_mutex_t meal_mutex;       // last_meal thread-safe update

// Shared resource mutex
pthread_mutex_t *forks;           // Çatal paylaşımı
```

### **2. Deadlock Prevention**
- **Philosopher numbering**: Circular arrangement
- **Fork ordering**: Address-based locking order
- **Odd/even synchronization**: Çift ID'li filozoflar 500µs bekler

### **3. Race Condition Çözümleri**
```c
// ❌ Race condition
if (philo->data->is_dead)
    return;

// ✅ Thread-safe
pthread_mutex_lock(&philo->data->death_mutex);
if (philo->data->is_dead) {
    pthread_mutex_unlock(&philo->data->death_mutex);
    return;
}
pthread_mutex_unlock(&philo->data->death_mutex);
```

---

## ⚡ **Kritik Timing İssues**

### **1. 10ms Death Detection**
- Monitor thread 100µs polling yapmalı
- Ölüm mesajı immediate print edilmeli
- PDF requirement: "within 10ms"

### **2. Synchronization Timing**
```c
// Başlangıç senkronizasyonu
sync_philo_start(philo);
if (philo->id % 2 != 0)
    usleep(500);  // Çift ID'ler 500µs bekler
```

### **3. Think Time Optimization**
```c
// Tek sayıda filozof için think time
if (philo->data->philo_count % 2 == 1) {
    think_time = time_to_eat - time_to_sleep;
    if (think_time > 0)
        usleep(think_time * 100);
}
```

---

## 🧪 **Test Senaryoları**

### **Basic Tests:**
```bash
# Normal case
./philo 4 310 200 100

# Single philosopher (should die)
./philo 1 800 200 200

# No death scenario  
./philo 5 800 200 200

# Meal count limit
./philo 4 400 100 100 7
```

### **Edge Cases:**
- **Tek filozof**: Yemek yiyemez, ölmeli
- **İki filozof**: Deadlock riski yüksek
- **Çok hızlı timing**: Race condition testi

---

## 📚 **Öğretirken Vurgulanacak Noktalar**

### **1. Concurrency Concepts**
- Process vs Thread farkı
- Shared memory vs Message passing
- Context switching maliyeti

### **2. Synchronization Primitives**
- Mutex vs Semaphore vs Condition Variable
- Lock ordering ve deadlock prevention
- Atomic operations

### **3. Real-world Applications**
- Database connection pooling
- Web server request handling  
- Producer-consumer patterns

### **4. Debug Techniques**
```bash
# Valgrind thread checker
valgrind --tool=helgrind ./philo 4 310 200 100

# AddressSanitizer
gcc -fsanitize=address -pthread

# Debug builds
gcc -g -pthread -DDEBUG
```

---

## ⚠️ **Sık Yapılan Hatalar**

1. **Double mutex init** - Aynı mutex'i iki kez initialize etmek
2. **Deadlock** - Yanlış lock ordering
3. **Race condition** - Unprotected shared data access
4. **Memory leak** - Mutex destroy etmemek
5. **Invalid pointer** - Freed memory'ye erişim

---

## 🎯 **Öğrenci Değerlendirme Kriterleri**

- **Threading mastery**: pthread API kullanımı
- **Synchronization**: Mutex ile data protection
- **Deadlock prevention**: Circular wait breaking
- **Performance**: 10ms death detection
- **Memory management**: Leak-free cleanup
- **Edge case handling**: Single philosopher scenario

**Bu proje, concurrent programming temellerini öğrenmek için mükemmel bir örnektir! 🚀**
