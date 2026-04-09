# DateTime

C++ библиотека для работы с датами, временем и временными интервалами.

## Возможности

- Внутреннее представление дат через **Julian Day Number** (`int64_t`) - все календарные операции выполняются за O(1)
- Четыре класса: `Time`, `Date`, `DateTime`, `TimeDiff`
- Полный набор операторов сравнения и арифметики для каждого типа
- Валидация аргументов в конструкторах с выбросом исключений
- Поддержка високосных лет и вычисления дня недели
- Без внешних зависимостей

## Сборка

Требования: CMake 3.14+, компилятор с поддержкой C++17.

```bash
git clone https://github.com/kex1tu/date_time.git
cd date_time
cmake -B build
cmake --build build
./build/datetime
```

## Примеры использования

```cpp
#include "datetime.h"
using namespace date_time;

// --- Time ---
Time t(14, 30, 0);
t.AddMinutes(90);
ToString(t);          // "16:00:00"

// --- Date ---
Date d(2025, 2, 28);
++d;
ToString(d);          // "2025.03.01"
d.IsLeapYear();       // false
d.weekday();          // Weekday::kSaturday

// --- DateTime ---
DateTime dt1(2025, 3, 1, 9, 0, 0);
DateTime dt2(2025, 3, 2, 11, 30, 0);

TimeDiff diff = dt2 - dt1;
diff.days();          // 1
diff.hours();         // 2
diff.minutes();       // 30
diff.total_seconds(); // 95400

DateTime dt3 = dt1 + diff;
dt3 == dt2;           // true
```

## API

### `Time(int hour, int minute, int second)`
Время суток в диапазоне `[00:00:00, 23:59:59]`.  
Бросает `std::invalid_argument` при выходе за границы диапазона.

| Метод | Описание |
|---|---|
| `hour()`, `minute()`, `second()` | Геттеры компонентов |
| `AddHours(n)`, `AddMinutes(n)`, `AddSeconds(n)` | Добавить смещение (со знаком), с ограничением по границам суток |
| `seconds_since_midnight()` | Секунды с начала суток |
| `ToString(t)` | Строка в формате `"HH:mm:ss"` |

Операторы: `==`, `!=`, `<`, `<=`, `>`, `>=`, `time - time -> TimeDiff`

---

### `Date(int year, int month, int day)`
Хранится как Julian Day Number (`int64_t`).  
Бросает `std::invalid_argument` при некорректных аргументах (в том числе 29 февраля в не високосный год).

| Метод | Описание |
|---|---|
| `year()`, `month()`, `day()` | Геттеры компонентов |
| `weekday()` | День недели (`Weekday`) |
| `IsLeapYear()` | Метод экземпляра и статический перегруз |
| `AddDays(n)` | Добавить дни (со знаком) |
| `Next()`, `Prev()` | Следующий / предыдущий день |
| `ToString(d)` | Строка в формате `"yyyy.MM.dd"` |

Операторы: `==`, `!=`, `<`, `<=`, `>`, `>=`, `++`, `--`, `date - date -> TimeDiff`

---

### `DateTime(int year, int month, int day, int hour=0, int minute=0, int second=0)`
Композиция `Date` и `Time`. Также конструируется из `(const Date&, const Time&)`.

| Метод | Описание |
|---|---|
| `AddDays(n)`, `AddHours(n)`, `AddMinutes(n)`, `AddSeconds(n)` | Добавить смещение с автоматическим переносом через полночь |
| `ToString(dt)` | Строка в формате `"yyyy.MM.dd HH:mm:ss"` |

Операторы: `==`, `!=`, `<`, `<=`, `>`, `>=`, `datetime - datetime -> TimeDiff`, `datetime +- TimeDiff -> DateTime`

---

### `TimeDiff(int days, int hours, int minutes, int seconds)`
Знаковый временной интервал. Все компоненты должны иметь одинаковый знак.  
Бросает `std::invalid_argument` если `|hours| > 23`, `|minutes| > 59`, `|seconds| > 59` или знаки компонентов различаются.

| Метод | Описание |
|---|---|
| `days()`, `hours()`, `minutes()`, `seconds()` | Геттеры компонентов |
| `total_hours()`, `total_minutes()`, `total_seconds()` | Полное значение с учётом дней |

Операторы: `==`, `!=`, `<`, `<=`, `>`, `>=`, `+`, `-`

---

### Перечисление `Weekday`
`kMonday`, `kTuesday`, `kWednesday`, `kThursday`, `kFriday`, `kSaturday`, `kSunday`

## Структура проекта

```
.
├── datetime.h       # Объявления классов, константы
├── datetime.cpp     # Реализация
├── main.cc          # Набор тестов
└── CMakeLists.txt
```