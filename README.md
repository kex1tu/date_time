# DateTime library

Реализуйте классы для представления дат и времени.

## Требования к реализации
* Название классов: `date`, `time`, `datetime`, `timediff`
* Заголовочный файл: `datetime.h`
* Файл реализации: `datetime.cpp`
* Пространство имен `DateTime`
* Файл `main.cc` не менять.

## Класс time
Класс для представления времени дня. 

### Конструктор
```c++
time(int hour,
     int minute,
     int second);
```
#### Диапазоны:
* 0 <= hour < 24,
* 0 <= minute < 60,
* 0 <= second < 60.

#### Примечание
При неправильном задании аргументов конструктора бросать исключение `std::invalid_argument`.
Например, `throw std::invalid_argument("hours must be between 0 and 23");`

### Доступные методы
```c++
int hour() const;      // Получить количество часов
int minute() const;    // Получить количество минут
int second() const;    // Получить количество секунд

void add_hours(int nb_hours);      // Добавить заданное количество часов
void add_minutes(int nb_minutes);  // Добавить заданное количество минут
void add_seconds(int nb_seconds);  // Добавить заданное количество секунд
```

### Внешняя функция

```c++
std::string to_string(const time&);  // Преобразовать в строку в формате "HH:mm:ss"
```

#### Формат строки

| Спецификатор | Описание                              |
| ------------ | ------------------------------------- |
| HH           | Часы в 24-часовом формате от 00 до 23 |
| mm           | Минуты от 00 до 59                    |
| ss           | Секунды от 00 до 59                   |

### Поддерживаемые операторы
```c++
time tm1 = time(12, 50, 0);
time tm2 = time(13, 40, 0);
time tm3 = tm1;
```
| Оператор     | Описание               | Пример использования             |
| ------------ | ---------------------- | -------------------------------- |
| time == time | Equality operator      | `assert(tm1 == tm3);`            |
| time != time | Inequality operator    | `assert(tm1 != tm2);`            |
| time < time  | Less operator          | `assert(tm1 < tm2);`             |
| time <= time | Less equal operator    | `assert(tm1 <= tm2);`            |
| time > time  | Greater operator       | `assert(tm2 > tm3);`             |
| time >= time | Greater equal operator | `assert(tm2 >= tm3);`            |
| time - time  | Minus operator         | `timediff ts1 = tm2 - tm1;`<br>`assert(ts.minutes() == 50);`<br>`assert(ts.hours() == 0);` |

## Класс date
Класс для представления даты. 

### Конструктор
```c++
date(int year,
     int month,
     int day);
```

#### Примечание
При неправильном задании аргументов конструктора бросать исключение `std::invalid_argument`.

### Доступные методы
```c++
int year() const;            // Получить год    
int month() const;           // Получить месяц 
int day() const;             // Получить день
weekday weekday() const;     // Получить день недели для даты
bool is_leapyear() const;    // true, если год високосностный, иначе false

void add_days(int nb_days);		   // Добавить заданное количество дней

date next() const;           // Получить дату для следующего дня
date prev() const;           // Получить дату для предыдущего дня

static bool is_leapyear(int year); // Проверка года на високосность 
```

### Внешняя функция

```c++
std::string to_string(const date&);  // Преобразовать в строку в формате "yyyy.MM.dd"
```

#### Формат строки

| Спецификатор | Описание                               |
| ------------ | -------------------------------------- |
| yyyy         | Год                                    |
| MM           | Месяц от 01 до 12                      |
| dd           | День месяца от 01 до 31                |

### Поддерживаемые операторы
```c++
date dt1 = date(2025, 2, 11);
date dt2 = date(2025, 2, 12);
date dt3 = dt1;
```
| Оператор     | Описание                | Пример использования            |
| ------------ | ----------------------- | ------------------------------- |
| date == date | Equality operator       | `assert(dt1 == dt3);`           |
| date != date | Inequality operator     | `assert(dt1 != dt2);`           |
| date < date  | Less operator           | `assert(dt1 < dt2);`            |
| date <= date | Less equal operator     | `assert(dt1 <= dt2);`           |
| date > date  | Greater operator        | `assert(dt2 > dt3);`            |
| date >= date | Greater equal operator  | `assert(dt2 >= dt3);`           |
| date - date  | Minus operator          | `timediff ts = dt2 - dt1;` <br> `assert(ts.days() == 1)`|
| ++date       | Pre-increment operator  | `assert(++dt1 == dt2);`         |
| date++       | Post-increment operator | `dt1++; assert(dt1 == dt2);`    |
| --date       | Pre-decrement operator  | `assert(--dt2 == dt3);`         |
| date--       | Post-decrement operator | dt2--;`assert(dt2 == dt3);`     |


## Класс datetime
Класс для представления даты и времени. 

### Конструкторы
```c++
datetime(int year,
         int month,
         int day,
         int hour = 0,
         int minute = 0,
         int second = 0);
datetime(const date & dt,
         const time & tm);
```

#### Примечание
При неправильном задании аргументов бросать исключение `std::invalid_argument`.
Например, `throw std::invalid_argument("hours must be between 0 and 23");`

### Доступные методы
```c++
int year() const;
int month() const;
int day() const;
int hour() const;
int minute() const;
int second() const;
weekday weekday() const;
bool is_leapyear() const;          // true, если год високосностный, иначе false

void add_days(int nb_days);		   // Добавить заданное количество дней
void add_hours(int nb_hours);      // Добавить заданное количество часов
void add_minutes(int nb_minutes);  // Добавить заданное количество минут
void add_seconds(int nb_seconds);  // Добавить заданное количество секунд

static bool is_leapyear(int year); // Проверка года на високосность 
```

### Внешняя функция

```c++
std::string to_string(const datetime&);  // Преобразовать в строку в формате "yyyy.MM.dd HH:mm:ss"
```

#### Формат строки

| Спецификатор | Описание                               |
| ------------ | -------------------------------------- |
| yyyy         | Год                                    |
| MM           | Месяц от 01 до 12                      |
| dd           | День месяца от 01 до 31                |
| HH           | Часы в 24-часовом формате от 00 до 23  |
| mm           | Минуты от 00 до 59                     |
| ss           | Секунды от 00 до 59                    |

### Поддерживаемые операторы
```c++
datetime dt1 = datetime(2025, 2, 11, 12, 0, 0);
datetime dt2 = datetime(2025, 2, 12, 14, 1, 0);
datetime dt3 = dt1;
timediff ts(1, 2, 1, 0);
```

| Оператор             | Описание               | Пример использования          |
| -------------------- | ---------------------- | ----------------------------- |
| datetime == datetime | Equality operator      | assert(dt1 == dt3);           |
| datetime != datetime | Inequality operator    | assert(dt1 != dt2);           |
| datetime < datetime  | Less operator          | assert(dt1 < dt2);            |
| datetime <= datetime | Less equal operator    | assert(dt1 <= dt2);           |
| datetime > datetime  | Greater operator       | assert(dt2 > dt3);            |
| datetime >= datetime | Greater equal operator | assert(dt2 >= dt3);           |
| datetime - datetime  | Minus operator         | timediff ts = dt2 - dt1;<br>assert(ts.days() == 1);<br>assert(ts.hours() == 2); |
| datetime - ts        | Minus operator         | assert(dt2 - ts == dt1)       |
| datetime + ts        | Plus operator          | assert(dt1 + ts == dt2)       |


## Класс timediff
Класс для представления разности дат и времени. 

### Конструктор

```c++
timediff(int days, int hours, int minutes, int seconds);
```

#### Примечание
При неправильном задании аргументов бросать исключение `std::invalid_argument`.
Например, `throw std::invalid_argument("hours must be between -23 and 23");`
или `throw std::invalid_argument("all arguments must have the same sign");`

### Доступные методы
```c++
int days() const;            // Получить количество дней
int hours() const;           // Получить количество часов
int minutes() const;         // Получить количество минут   
int seconds() const;         // Получить количество секунд
int total_hours() const;     // Получить общее количество часов (с учётом количества дней)
int total_minutes() const;   // Получить общее количество минут
int total_seconds() const;   // Получить общее количество секунд
```

### Поддерживаемые операторы
```c++
timediff ts1(1, 2, 3, 10);
timediff ts2(1, 0, 4, 0);
timediff ts3 = ts1;
```

| Оператор             | Описание               | Пример использования          |
| -------------------- | ---------------------- | ----------------------------- |
| timediff == timediff | Equality operator      | assert(ts1 == ts3);           |
| timediff != timediff | Inequality operator    | assert(ts1 != ts2);           |
| timediff < timediff  | Less operator          | assert(ts2 < ts1);            |
| timediff <= timediff | Less equal operator    | assert(ts2 <= ts1);           |
| timediff > timediff  | Greater operator       | assert(ts1 > ts2);            |
| timediff >= timediff | Greater equal operator | assert(ts1 >= ts2);           |
| timediff >= timediff | Greater equal operator | assert(ts1 >= ts2);           |
| timediff + timediff  | Plus operator          | assert(ts1 >= ts2);           |
| timediff - timediff  | Minus operator         | assert(ts1 >= ts2);           |
