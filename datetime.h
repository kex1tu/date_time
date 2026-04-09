#ifndef DATETIME_H_
#define DATETIME_H_
#include <cstdint>
#include <stdexcept>
#include <string>

namespace date_time {

constexpr int kDaysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
constexpr int64_t kSecondsPerDay = 86400LL;
constexpr int64_t kSecondsPerHour = 3600LL;
constexpr int64_t kSecondsPerMinute = 60LL;
constexpr int64_t kMinutesPerHour = 60LL;
constexpr int64_t kMinutesPerDay = 1440LL;
constexpr int64_t kHoursPerDay = 24LL;
constexpr int64_t kOurEraJulianDayNumber = 1721057LL;  // 0000.01.01

enum class Weekday : uint8_t {
  kSunday,
  kMonday,
  kTuesday,
  kWednesday,
  kThursday,
  kFriday,
  kSaturday
};

class Time {
 private:
  int64_t seconds_since_midnight_;
  explicit Time(int64_t seconds)
      : seconds_since_midnight_(std::abs(seconds % kSecondsPerDay)) {}
  friend class DateTime;

 public:
  explicit Time(int hour = 0, int minute = 0, int second = 0);
  int64_t seconds_since_midnight() const noexcept;
  int64_t hour() const noexcept;
  int64_t minute() const noexcept;
  int64_t second() const noexcept;
  void AddHours(int64_t num_hours);
  void AddMinutes(int64_t num_minutes);
  void AddSeconds(int64_t num_seconds);
};

bool operator==(const Time& lhs, const Time& rhs) noexcept;
bool operator!=(const Time& lhs, const Time& rhs) noexcept;
bool operator<(const Time& lhs, const Time& rhs) noexcept;
bool operator<=(const Time& lhs, const Time& rhs) noexcept;
bool operator>(const Time& lhs, const Time& rhs) noexcept;
bool operator>=(const Time& lhs, const Time& rhs) noexcept;
std::string ToString(const Time& time) noexcept;

class Date {
 private:
  int64_t julian_day_number_;

 public:
  explicit Date(int year = 0, int month = 1, int day = 1);
  int64_t julian_day_number() const noexcept;
  int64_t year() const noexcept;
  int64_t month() const noexcept;
  int64_t day() const noexcept;
  date_time::Weekday weekday() const noexcept;
  bool IsLeapYear() const noexcept;
  static bool IsLeapYear(int64_t year) noexcept;
  void AddDays(int64_t num_days);
  Date Next() const;
  Date Prev() const;
  Date& operator++();
  Date operator++(int);
  Date& operator--();
  Date operator--(int);
};

bool operator==(const Date& lhs, const Date& rhs) noexcept;
bool operator!=(const Date& lhs, const Date& rhs) noexcept;
bool operator<(const Date& lhs, const Date& rhs) noexcept;
bool operator<=(const Date& lhs, const Date& rhs) noexcept;
bool operator>(const Date& lhs, const Date& rhs) noexcept;
bool operator>=(const Date& lhs, const Date& rhs) noexcept;
std::string ToString(const Date& date) noexcept;

class DateTime {
 private:
  Date date_;
  Time time_;

 public:
  DateTime(int year, int month, int day, int hour = 0, int minute = 0,
           int second = 0)
      : date_(year, month, day), time_(hour, minute, second) {}
  DateTime(const Date& date, const Time& time) : date_(date), time_(time) {}
  int64_t julian_day_number() const noexcept;
  int64_t seconds_since_midnight() const noexcept;
  int64_t year() const noexcept;
  int64_t month() const noexcept;
  int64_t day() const noexcept;
  int64_t hour() const noexcept;
  int64_t minute() const noexcept;
  int64_t second() const noexcept;
  date_time::Weekday weekday() const noexcept;
  bool IsLeapYear() const noexcept;
  static bool IsLeapYear(int64_t year) noexcept;
  void AddDays(int64_t num_days);
  void AddHours(int64_t num_hours);
  void AddMinutes(int64_t num_minutes);
  void AddSeconds(int64_t num_seconds);
};

bool operator==(const DateTime& lhs, const DateTime& rhs) noexcept;
bool operator!=(const DateTime& lhs, const DateTime& rhs) noexcept;
bool operator<(const DateTime& lhs, const DateTime& rhs) noexcept;
bool operator<=(const DateTime& lhs, const DateTime& rhs) noexcept;
bool operator>(const DateTime& lhs, const DateTime& rhs) noexcept;
bool operator>=(const DateTime& lhs, const DateTime& rhs) noexcept;
std::string ToString(const DateTime& date_time) noexcept;

class TimeDiff {
 private:
  int64_t total_seconds_;

 public:
  explicit TimeDiff(int64_t total_seconds = 0);
  TimeDiff(int days, int hours, int minutes, int seconds);
  int64_t days() const noexcept;
  int hours() const noexcept;
  int minutes() const noexcept;
  int seconds() const noexcept;
  int64_t total_hours() const noexcept;
  int64_t total_minutes() const noexcept;
  int64_t total_seconds() const noexcept;
};

bool operator==(const TimeDiff& lhs, const TimeDiff& rhs) noexcept;
bool operator!=(const TimeDiff& lhs, const TimeDiff& rhs) noexcept;
bool operator<(const TimeDiff& lhs, const TimeDiff& rhs) noexcept;
bool operator<=(const TimeDiff& lhs, const TimeDiff& rhs) noexcept;
bool operator>(const TimeDiff& lhs, const TimeDiff& rhs) noexcept;
bool operator>=(const TimeDiff& lhs, const TimeDiff& rhs) noexcept;
TimeDiff operator+(const TimeDiff& lhs, const TimeDiff& rhs);
DateTime operator+(const DateTime& date_time, const TimeDiff& delta);
TimeDiff operator-(const TimeDiff& lhs, const TimeDiff& rhs);
TimeDiff operator-(const Time& lhs, const Time& rhs);
TimeDiff operator-(const Date& lhs, const Date& rhs);
TimeDiff operator-(const DateTime& lhs, const DateTime& rhs);
DateTime operator-(const DateTime& date_time, const TimeDiff& delta);

}  // namespace date_time
#endif  // DATETIME_H_
