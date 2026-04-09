#include "datetime.h"

#include <cstdint>

namespace date_time {
namespace {

bool GlobalIsLeapYear(int64_t year) noexcept {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

struct DateParts {
  int64_t day_plus_offset;
  int64_t gregorian_cycle;
  int64_t day_of_gregorian_cycle;
  int64_t julian_cycle;
  int64_t day_of_julian_cycle;
  int64_t month_param;
};

DateParts ComputeDateParts(int64_t julian_day_number) noexcept {
  DateParts parts{};
  parts.day_plus_offset = julian_day_number + 32044;
  parts.gregorian_cycle = (4 * parts.day_plus_offset + 3) / 146097;
  parts.day_of_gregorian_cycle =
      parts.day_plus_offset - ((146097 * parts.gregorian_cycle) / 4);
  parts.julian_cycle = (4 * parts.day_of_gregorian_cycle + 3) / 1461;
  parts.day_of_julian_cycle =
      parts.day_of_gregorian_cycle - ((1461 * parts.julian_cycle) / 4);
  parts.month_param = (5 * parts.day_of_julian_cycle + 2) / 153;
  return parts;
}

std::string FormatYear(int64_t year) noexcept {
  std::string year_string = std::to_string(year);
  if (year_string.size() >= 4) {
    return year_string;
  }
  return std::string(4 - year_string.size(), '0') + year_string;
}

std::string FormatTwoDigits(int64_t value) noexcept {
  std::string value_string = std::to_string(value);
  if (value_string.size() < 2) {
    value_string.insert(value_string.begin(), '0');
  }
  return value_string;
}
}  // namespace
Time::Time(int hour, int minute, int second) {
  if (hour < 0 || hour >= 24) {
    throw std::invalid_argument("hours must be between 0 and 23");
  }
  if (minute < 0 || minute >= 60) {
    throw std::invalid_argument("minutes must be between 0 and 59");
  }
  if (second < 0 || second >= 60) {
    throw std::invalid_argument("seconds must be between 0 and 59");
  }
  seconds_since_midnight_ = (static_cast<int64_t>(hour) * kSecondsPerHour) +
                            (static_cast<int64_t>(minute) * kSecondsPerMinute) +
                            static_cast<int64_t>(second);
}

int64_t Time::seconds_since_midnight() const noexcept {
  return seconds_since_midnight_;
}

int64_t Time::hour() const noexcept {
  return seconds_since_midnight_ / kSecondsPerHour;
}

int64_t Time::minute() const noexcept {
  return (seconds_since_midnight_ % kSecondsPerHour) / kSecondsPerMinute;
}

int64_t Time::second() const noexcept {
  return seconds_since_midnight_ % kSecondsPerMinute;
}

void Time::AddHours(int64_t num_hours) {
  seconds_since_midnight_ += num_hours * kSecondsPerHour;
  if (seconds_since_midnight_ >= kSecondsPerDay) {
    seconds_since_midnight_ = kSecondsPerDay - 1;
  }
  seconds_since_midnight_ = std::max<int64_t>(seconds_since_midnight_, 0);
}

void Time::AddMinutes(int64_t num_minutes) {
  seconds_since_midnight_ += num_minutes * kSecondsPerMinute;
  if (seconds_since_midnight_ >= kSecondsPerDay) {
    seconds_since_midnight_ = kSecondsPerDay - 1;
  }
  seconds_since_midnight_ = std::max<int64_t>(seconds_since_midnight_, 0);
}

void Time::AddSeconds(int64_t num_seconds) {
  seconds_since_midnight_ += num_seconds;
  if (seconds_since_midnight_ >= kSecondsPerDay) {
    seconds_since_midnight_ = kSecondsPerDay - 1;
  }
  seconds_since_midnight_ = std::max<int64_t>(seconds_since_midnight_, 0);
}

bool operator==(const Time& lhs, const Time& rhs) noexcept {
  return lhs.seconds_since_midnight() == rhs.seconds_since_midnight();
}
bool operator<(const Time& lhs, const Time& rhs) noexcept {
  return lhs.seconds_since_midnight() < rhs.seconds_since_midnight();
}
bool operator!=(const Time& lhs, const Time& rhs) noexcept {
  return !(lhs == rhs);
}

bool operator<=(const Time& lhs, const Time& rhs) noexcept {
  return lhs < rhs || lhs == rhs;
}
bool operator>(const Time& lhs, const Time& rhs) noexcept {
  return !(lhs <= rhs);
}
bool operator>=(const Time& lhs, const Time& rhs) noexcept {
  return !(lhs < rhs);
}
std::string ToString(const Time& time) noexcept {
  return FormatTwoDigits(time.hour()) + ':' + FormatTwoDigits(time.minute()) +
         ':' + FormatTwoDigits(time.second());
}

Date::Date(int year, int month, int day) {
  if (year < 0) {
    throw std::invalid_argument("year must be non-negative");
  }
  if (month < 1 || month > 12) {
    throw std::invalid_argument("month must be between 1 and 12");
  }
  int max_days = kDaysInMonth[month - 1];
  if (month == 2 && GlobalIsLeapYear(year)) {
    max_days = 29;
  }
  if (day < 1 || day > max_days) {
    throw std::invalid_argument("day must be between 1 and 31");
  }
  int64_t month_shift = (14 - static_cast<int64_t>(month)) / 12;
  int64_t shifted_year = static_cast<int64_t>(year) + 4800 - month_shift;
  int64_t shifted_month = static_cast<int64_t>(month) + (12 * month_shift) - 3;
  julian_day_number_ = static_cast<int64_t>(day) +
                       ((153 * shifted_month + 2) / 5) + (365 * shifted_year) +
                       (shifted_year / 4) - (shifted_year / 100) +
                       (shifted_year / 400) - 32045;
}
int64_t Date::julian_day_number() const noexcept { return julian_day_number_; }
int64_t Date::year() const noexcept {
  DateParts parts = ComputeDateParts(julian_day_number_);

  return (100 * parts.gregorian_cycle) + parts.julian_cycle - 4800 +
         (parts.month_param / 10);
}
int64_t Date::month() const noexcept {
  DateParts parts = ComputeDateParts(julian_day_number_);

  return parts.month_param + 3 - (12 * (parts.month_param / 10));
}
int64_t Date::day() const noexcept {
  DateParts parts = ComputeDateParts(julian_day_number_);

  return 1 + parts.day_of_julian_cycle - ((153 * parts.month_param + 2) / 5);
}
date_time::Weekday Date::weekday() const noexcept {
  int weekday_index = static_cast<int>(julian_day_number_ % 7);
  switch (weekday_index) {
    case 0:
      return Weekday::kMonday;
    case 1:
      return Weekday::kTuesday;
    case 2:
      return Weekday::kWednesday;
    case 3:
      return Weekday::kThursday;
    case 4:
      return Weekday::kFriday;
    case 5:
      return Weekday::kSaturday;
    case 6:
      return Weekday::kSunday;
    default:
      return Weekday::kMonday;
  }
}
bool Date::IsLeapYear() const noexcept { return GlobalIsLeapYear(year()); }
bool Date::IsLeapYear(int64_t year) noexcept { return GlobalIsLeapYear(year); }
void Date::AddDays(int64_t num_days) {
  int64_t new_julian_day_number = julian_day_number_ + num_days;
  if (new_julian_day_number < kOurEraJulianDayNumber) {
    throw std::invalid_argument("Date is out of supported range");
  }
  julian_day_number_ = new_julian_day_number;
}
Date Date::Next() const {
  Date next_date = *this;
  next_date.AddDays(1LL);
  return next_date;
}
Date Date::Prev() const {
  Date previous_date = *this;
  previous_date.AddDays(-1LL);
  return previous_date;
}

Date& Date::operator++() {
  this->AddDays(1);
  return *this;
}
Date Date::operator++(int) {
  Date previous_date = *this;
  ++*this;
  return previous_date;
}

Date& Date::operator--() {
  this->AddDays(-1);
  return *this;
}
Date Date::operator--(int) {
  Date previous_date = *this;
  --*this;
  return previous_date;
}

bool operator==(const Date& lhs, const Date& rhs) noexcept {
  return lhs.julian_day_number() == rhs.julian_day_number();
}
bool operator<(const Date& lhs, const Date& rhs) noexcept {
  return lhs.julian_day_number() < rhs.julian_day_number();
}
bool operator!=(const Date& lhs, const Date& rhs) noexcept {
  return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) noexcept {
  return lhs < rhs || lhs == rhs;
}
bool operator>(const Date& lhs, const Date& rhs) noexcept {
  return !(lhs <= rhs);
}
bool operator>=(const Date& lhs, const Date& rhs) noexcept {
  return !(lhs < rhs);
}

std::string ToString(const Date& date) noexcept {
  return FormatYear(date.year()) + '.' + FormatTwoDigits(date.month()) + '.' +
         FormatTwoDigits(date.day());
}

int64_t DateTime::julian_day_number() const noexcept {
  return date_.julian_day_number();
}
int64_t DateTime::seconds_since_midnight() const noexcept {
  return time_.seconds_since_midnight();
}
int64_t DateTime::year() const noexcept { return date_.year(); }
int64_t DateTime::month() const noexcept { return date_.month(); }
int64_t DateTime::day() const noexcept { return date_.day(); }
int64_t DateTime::hour() const noexcept { return time_.hour(); }
int64_t DateTime::minute() const noexcept { return time_.minute(); }
int64_t DateTime::second() const noexcept { return time_.second(); }

date_time::Weekday DateTime::weekday() const noexcept {
  return date_.weekday();
}
bool DateTime::IsLeapYear() const noexcept { return GlobalIsLeapYear(year()); }
bool DateTime::IsLeapYear(int64_t year) noexcept {
  return GlobalIsLeapYear(year);
}

void DateTime::AddDays(int64_t num_days) { date_.AddDays(num_days); }
void DateTime::AddHours(int64_t num_hours) {
  AddSeconds(num_hours * kSecondsPerHour);
}
void DateTime::AddMinutes(int64_t num_minutes) {
  AddSeconds(num_minutes * kSecondsPerMinute);
}
void DateTime::AddSeconds(int64_t num_seconds) {
  int64_t total_seconds = time_.seconds_since_midnight() + num_seconds;
  int64_t day_offset = total_seconds / kSecondsPerDay;
  int64_t total_seconds_normalized = total_seconds % kSecondsPerDay;
  if (total_seconds_normalized < 0) {
    total_seconds_normalized += kSecondsPerDay;
    --day_offset;
  }

  time_ = Time(total_seconds_normalized);
  date_.AddDays(day_offset);
}

bool operator==(const DateTime& lhs, const DateTime& rhs) noexcept {
  return (lhs.julian_day_number() == rhs.julian_day_number() &&
          lhs.seconds_since_midnight() == rhs.seconds_since_midnight());
}
bool operator<(const DateTime& lhs, const DateTime& rhs) noexcept {
  return (lhs.julian_day_number() < rhs.julian_day_number() ||
          (lhs.julian_day_number() == rhs.julian_day_number() &&
           lhs.seconds_since_midnight() < rhs.seconds_since_midnight()));
}

bool operator!=(const DateTime& lhs, const DateTime& rhs) noexcept {
  return !(lhs == rhs);
}

bool operator<=(const DateTime& lhs, const DateTime& rhs) noexcept {
  return (lhs < rhs || lhs == rhs);
}
bool operator>(const DateTime& lhs, const DateTime& rhs) noexcept {
  return !(lhs <= rhs);
}
bool operator>=(const DateTime& lhs, const DateTime& rhs) noexcept {
  return !(lhs < rhs);
}
std::string ToString(const DateTime& date_time) noexcept {
  return FormatYear(date_time.year()) + '.' +
         FormatTwoDigits(date_time.month()) + '.' +
         FormatTwoDigits(date_time.day()) + ' ' +
         FormatTwoDigits(date_time.hour()) + ':' +
         FormatTwoDigits(date_time.minute()) + ':' +
         FormatTwoDigits(date_time.second());
}

TimeDiff::TimeDiff(int64_t total_seconds) : total_seconds_(total_seconds) {}

TimeDiff::TimeDiff(int days, int hours, int minutes, int seconds) {
  bool has_positive_component =
      days > 0 || hours > 0 || minutes > 0 || seconds > 0;
  bool has_negative_component =
      days < 0 || hours < 0 || minutes < 0 || seconds < 0;
  if (has_positive_component && has_negative_component) {
    throw std::invalid_argument("all arguments must have the same sign");
  }
  int abs_hours = std::abs(hours);
  int abs_minutes = std::abs(minutes);
  int abs_seconds = std::abs(seconds);
  if (abs_hours > 23) {
    throw std::invalid_argument("hours must be between -23 and 23");
  }
  if (abs_minutes > 59) {
    throw std::invalid_argument("minutes must be between -59 and 59");
  }
  if (abs_seconds > 59) {
    throw std::invalid_argument("seconds must be between -59 and 59");
  }
  total_seconds_ = (static_cast<int64_t>(days) * kSecondsPerDay) +
                   (static_cast<int64_t>(hours) * kSecondsPerHour) +
                   (static_cast<int64_t>(minutes) * kSecondsPerMinute) +
                   static_cast<int64_t>(seconds);
}
int64_t TimeDiff::days() const noexcept {
  return static_cast<int>(total_seconds_ / kSecondsPerDay);
}
int TimeDiff::hours() const noexcept {
  return static_cast<int>((total_seconds_ % kSecondsPerDay) / kSecondsPerHour);
}
int TimeDiff::minutes() const noexcept {
  return static_cast<int>((total_seconds_ % kSecondsPerHour) /
                          kSecondsPerMinute);
}
int TimeDiff::seconds() const noexcept {
  return static_cast<int>(total_seconds_ % kSecondsPerMinute);
}
int64_t TimeDiff::total_hours() const noexcept {
  return total_seconds_ / kSecondsPerHour;
}
int64_t TimeDiff::total_minutes() const noexcept {
  return total_seconds_ / kSecondsPerMinute;
}
int64_t TimeDiff::total_seconds() const noexcept { return total_seconds_; }

bool operator==(const TimeDiff& lhs, const TimeDiff& rhs) noexcept {
  return (lhs.total_seconds() == rhs.total_seconds());
}
bool operator<(const TimeDiff& lhs, const TimeDiff& rhs) noexcept {
  return (lhs.total_seconds() < rhs.total_seconds());
}
bool operator!=(const TimeDiff& lhs, const TimeDiff& rhs) noexcept {
  return !(lhs == rhs);
}

bool operator<=(const TimeDiff& lhs, const TimeDiff& rhs) noexcept {
  return lhs == rhs || lhs < rhs;
}
bool operator>(const TimeDiff& lhs, const TimeDiff& rhs) noexcept {
  return !(lhs <= rhs);
}
bool operator>=(const TimeDiff& lhs, const TimeDiff& rhs) noexcept {
  return !(lhs < rhs);
}

TimeDiff operator+(const TimeDiff& lhs, const TimeDiff& rhs) {
  return TimeDiff(lhs.total_seconds() + rhs.total_seconds());
}

TimeDiff operator-(const TimeDiff& lhs, const TimeDiff& rhs) {
  return TimeDiff(lhs.total_seconds() - rhs.total_seconds());
}
TimeDiff operator-(const Time& lhs, const Time& rhs) {
  return TimeDiff(lhs.seconds_since_midnight() - rhs.seconds_since_midnight());
}
TimeDiff operator-(const Date& lhs, const Date& rhs) {
  return TimeDiff((lhs.julian_day_number() - rhs.julian_day_number()) *
                  kSecondsPerDay);
}
TimeDiff operator-(const DateTime& lhs, const DateTime& rhs) {
  int64_t seconds_difference =
      (lhs.julian_day_number() - rhs.julian_day_number()) * kSecondsPerDay;
  seconds_difference +=
      (lhs.seconds_since_midnight() - rhs.seconds_since_midnight());
  return TimeDiff(seconds_difference);
}
DateTime operator+(const DateTime& date_time, const TimeDiff& delta) {
  DateTime result(date_time);
  result.AddSeconds(delta.total_seconds());
  return result;
}
DateTime operator-(const DateTime& date_time, const TimeDiff& delta) {
  DateTime result(date_time);
  result.AddSeconds(-delta.total_seconds());
  return result;
}
}  // namespace date_time
