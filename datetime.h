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

 public:
  explicit Time(int hour = 0, int minute = 0, int second = 0);
  int64_t seconds_since_midnight() const;
  int64_t hour() const;
  int64_t minute() const;
  int64_t second() const;
  void AddHours(int64_t num_hours);
  void AddMinutes(int64_t num_minutes);
  void AddSeconds(int64_t num_seconds);
};

bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
bool operator<(const Time& lhs, const Time& rhs);
bool operator<=(const Time& lhs, const Time& rhs);
bool operator>(const Time& lhs, const Time& rhs);
bool operator>=(const Time& lhs, const Time& rhs);
std::string ToString(const Time& time);

class Date {
 private:
  int64_t julian_day_number_;

 public:
  explicit Date(int year = 0, int month = 1, int day = 1);
  int64_t julian_day_number() const;
  int64_t year() const;
  int64_t month() const;
  int64_t day() const;
  date_time::Weekday weekday() const;
  bool IsLeapYear() const;
  static bool IsLeapYear(int64_t year);
  void AddDays(int64_t num_days);
  Date Next() const;
  Date Prev() const;
  Date& operator++();
  Date operator++(int);
  Date& operator--();
  Date operator--(int);
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
std::string ToString(const Date& date);

class DateTime {
 private:
  int64_t seconds_since_midnight_;
  int64_t julian_day_number_;
  void AddSecondsChecked(int64_t delta);
  DateTime(int64_t julian_day_number, int64_t seconds_since_midnight);

 public:
  explicit DateTime(int64_t seconds_from_our_era = 0);
  DateTime(int year, int month, int day, int hour = 0, int minute = 0,
           int second = 0);
  DateTime(const Date& date, const Time& time);
  int64_t julian_day_number() const;
  int64_t seconds_since_midnight() const;
  int64_t year() const;
  int64_t month() const;
  int64_t day() const;
  int64_t hour() const;
  int64_t minute() const;
  int64_t second() const;
  date_time::Weekday weekday() const;
  bool IsLeapYear() const;
  static bool IsLeapYear(int64_t year);
  void AddDays(int64_t num_days);
  void AddHours(int64_t num_hours);
  void AddMinutes(int64_t num_minutes);
  void AddSeconds(int64_t num_seconds);
};

bool operator==(const DateTime& lhs, const DateTime& rhs);
bool operator!=(const DateTime& lhs, const DateTime& rhs);
bool operator<(const DateTime& lhs, const DateTime& rhs);
bool operator<=(const DateTime& lhs, const DateTime& rhs);
bool operator>(const DateTime& lhs, const DateTime& rhs);
bool operator>=(const DateTime& lhs, const DateTime& rhs);
std::string ToString(const DateTime& date_time);

class TimeDiff {
 private:
  int64_t total_seconds_;

 public:
  explicit TimeDiff(int64_t total_seconds = 0);
  TimeDiff(int days, int hours, int minutes, int seconds);
  int64_t days() const;
  int hours() const;
  int minutes() const;
  int seconds() const;
  int64_t total_hours() const;
  int64_t total_minutes() const;
  int64_t total_seconds() const;
};

bool operator==(const TimeDiff& lhs, const TimeDiff& rhs);
bool operator!=(const TimeDiff& lhs, const TimeDiff& rhs);
bool operator<(const TimeDiff& lhs, const TimeDiff& rhs);
bool operator<=(const TimeDiff& lhs, const TimeDiff& rhs);
bool operator>(const TimeDiff& lhs, const TimeDiff& rhs);
bool operator>=(const TimeDiff& lhs, const TimeDiff& rhs);
TimeDiff operator+(const TimeDiff& lhs, const TimeDiff& rhs);
DateTime operator+(const DateTime& date_time, const TimeDiff& delta);
TimeDiff operator-(const TimeDiff& lhs, const TimeDiff& rhs);
TimeDiff operator-(const Time& lhs, const Time& rhs);
TimeDiff operator-(const Date& lhs, const Date& rhs);
TimeDiff operator-(const DateTime& lhs, const DateTime& rhs);
DateTime operator-(const DateTime& date_time, const TimeDiff& delta);

}  // namespace date_time
#endif  // DATETIME_H_
