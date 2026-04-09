#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "datetime.h"

using namespace date_time;

void TestAll();

int main() {
  TestAll();
  return 0;
}

// Tests

void TestTime();
void TestDate();
void TestDateTime();
void TestTimediff();

void TestAll() {
  try {
    TestTime();
    TestDate();
    TestDateTime();
    TestTimediff();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    assert(false);
  }
}
/*
        Tests for class `Time`
*/
void TestTime() {
  {
    // Default constructor
    date_time::Time tm;
    assert(0 == tm.hour());
    assert(0 == tm.minute());
    assert(0 == tm.second());
    assert(std::string("00:00:00") == date_time::ToString(tm));
  }

  {  // seconds since_midnight 0
    date_time::Time tm(0);
    assert(0 == tm.seconds_since_midnight());
  }
  {  // seconds since_midnight 43200
    date_time::Time tm(12, 0, 0);
    assert(43200 == tm.seconds_since_midnight());
  }

  {  // seconds since_midnight 86399
    date_time::Time tm(23, 59, 59);
    assert(86399 == tm.seconds_since_midnight());
  }

  {  // add seconds 10800
    date_time::Time tm(0);
    tm.AddSeconds(10800);
    assert(10800 == tm.seconds_since_midnight());
  }

  {  // add minutes
    date_time::Time tm(0);
    tm.AddMinutes(1200);
    assert(72000 == tm.seconds_since_midnight());
  }

  {  // add hours 3
    date_time::Time tm(0);
    tm.AddHours(3);
    assert(10800 == tm.seconds_since_midnight());
  }

  {  // add days
    date_time::Time tm1(0);
    date_time::Time tm2(23, 59, 59);
    tm1.AddHours(25);
    assert(tm2.seconds_since_midnight() == tm1.seconds_since_midnight());
  }

  {  // Valid Time 00:01:02
    date_time::Time tm(0, 1, 2);
    assert(0 == tm.hour());
    assert(1 == tm.minute());
    assert(2 == tm.second());
    assert(std::string("00:01:02") == date_time::ToString(tm));
  }

  {  // Valid Time 00:00:00
    date_time::Time tm(0, 0, 0);
    assert(0 == tm.hour());
    assert(0 == tm.minute());
    assert(0 == tm.second());
    assert(std::string("00:00:00") == date_time::ToString(tm));
  }

  {  // Valid Time 23:59:59
    date_time::Time tm(23, 59, 59);
    assert(23 == tm.hour());
    assert(59 == tm.minute());
    assert(59 == tm.second());
    assert(std::string("23:59:59") == date_time::ToString(tm));
  }

  {  // Invalid Time
    try {
      date_time::Time tm(23, 59, 60);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time
    try {
      date_time::Time tm(23, 60, 59);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time
    try {
      date_time::Time tm(24, 10, 9);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time (negative)
    try {
      date_time::Time time1(-11, 10, 9);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time (negative)
    try {
      date_time::Time time1(11, -10, 9);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time (negative)
    try {
      date_time::Time time1(11, 10, -9);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Add 10 hours
    date_time::Time tm(0, 0, 0);
    tm.AddHours(10);
    assert(10 == tm.hour());
    assert(0 == tm.minute());
    assert(0 == tm.second());
    assert(std::string("10:00:00") == date_time::ToString(tm));
  }

  {  // Add 61 minutes
    date_time::Time tm(0, 0, 0);
    tm.AddMinutes(61);
    assert(std::string("01:01:00") == date_time::ToString(tm));
  }

  {  // Add 4321 seconds
    date_time::Time tm(0, 0, 0);
    tm.AddSeconds(4321);
    assert(std::string("01:12:01") == date_time::ToString(tm));
  }

  {  // Add -72 seconds
    date_time::Time tm(1, 1, 1);
    tm.AddSeconds(-72);
    assert(std::string("00:59:49") == date_time::ToString(tm));
  }

  {  // Add 10 seconds to 23:59:58
    date_time::Time tm(23, 59, 58);
    tm.AddSeconds(10);
    assert(23 == tm.hour());
    assert(59 == tm.minute());
    assert(59 == tm.second());
    assert(std::string("23:59:59") == date_time::ToString(tm));
  }

  {  // Add -10 seconds to 00:00:01
    date_time::Time tm(0, 0, 1);
    tm.AddSeconds(-10);
    assert(0 == tm.hour());
    assert(0 == tm.minute());
    assert(0 == tm.second());
    assert(std::string("00:00:00") == date_time::ToString(tm));
  }

  {  // Time operators
    date_time::Time time1(12, 50, 0);
    date_time::Time time2(13, 40, 0);
    date_time::Time time3(time1);
    assert(time1 == time3);
    assert(time1 != time2);
    assert(time1 < time2);
    assert(time1 <= time2);
    assert(time1 <= time3);
    assert(time2 > time1);
    assert(time2 >= time3);
    assert(time1 >= time3);
  }

  std::cout << "TestTime OK" << '\n';
}

/*
        Tests for class `Date`
*/

void TestDate() {
  {  // 0000.01.01
    date_time::Date dt(0, 1, 1);
    assert(0 == dt.year());
    assert(1 == dt.month());
    assert(1 == dt.day());
    assert(true == dt.IsLeapYear());
    assert(std::string("0000.01.01") == date_time::ToString(dt));
  }

  {  // julian_day_number()
    date_time::Date dt(2026, 4, 9);
    assert(2461140 == dt.julian_day_number());
  }
  {  // julian_day_number()
    date_time::Date dt(2000, 01, 01);
    assert(2451545 == dt.julian_day_number());
  }

  {  // Valid Date 2025.02.01
    date_time::Date dt(2025, 2, 1);
    assert(2025 == dt.year());
    assert(2 == dt.month());
    assert(1 == dt.day());
    assert(date_time::Weekday::kSaturday == dt.weekday());
    assert(false == dt.IsLeapYear());
    assert(std::string("2025.02.01") == date_time::ToString(dt));
  }

  {  // Invalid dates.  0000.00.00. Throw invalid argument exception
    try {
      date_time::Date dt(0, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid dates. Throw invalid argument exception
    try {
      date_time::Date date1(2025, 13, 10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid dates. Throw invalid argument exception
    try {
      date_time::Date date2(2025, 0, 10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid dates. Throw invalid argument exception
    try {
      date_time::Date date3(2025, -1, 10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid dates. Throw invalid argument exception
    try {
      date_time::Date dt4(2025, 1, -10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid dates. Throw invalid argument exception
    try {
      date_time::Date dt5(2025, 1, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid day 32 for months with 31 days. Throw invalid argument
     // exception
    int month_to_check_31[] = {1, 3, 5, 7, 8, 10, 12};
    for (int i : month_to_check_31) {
      try {
        date_time::Date date1(2025, i, 32);
        assert(false);
      } catch (const std::invalid_argument& error) {
      } catch (...) {
        assert(false);
      }
    }
  }

  {  // Invalid day 31 for months with 30 days. Throw invalid argument
     // exception
    int month_to_check_30[] = {4, 6, 9, 11};
    for (int i : month_to_check_30) {
      try {
        date_time::Date date1(2025, i, 31);
        assert(false);
      } catch (const std::invalid_argument& error) {
      } catch (...) {
        assert(false);
      }
    }
  }

  {  // Invalid day 30 for february. Throw invalid argument exception
    bool res{true};
    try {
      date_time::Date date1(2000, 2, 30);
      assert(res == false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(res == false);
    }
  }

  {  // Valid day 29 for february. Throw invalid argument exception
    date_time::Date dt(2000, 2, 29);
    assert(2000 == dt.year());
    assert(2 == dt.month());
    assert(29 == dt.day());
    assert(date_time::Weekday::kTuesday == dt.weekday());
    assert(true == dt.IsLeapYear());
    assert(std::string("2000.02.29") == date_time::ToString(dt));
  }

  {  // Valid day 29 for february. Throw invalid argument exception
    date_time::Date dt(2024, 2, 29);
    assert(2024 == dt.year());
    assert(2 == dt.month());
    assert(29 == dt.day());
    assert(date_time::Weekday::kThursday == dt.weekday());
    assert(true == dt.IsLeapYear());
    assert(std::string("2024.02.29") == date_time::ToString(dt));
  }

  {  // Add days
    date_time::Date dt(2019, 12, 31);
    dt.AddDays(60);
    assert(std::string("2020.02.29") == date_time::ToString(dt));
  }

  {  // Add days
    date_time::Date dt(2019, 12, 31);
    dt.AddDays(61);
    assert(std::string("2020.03.01") == date_time::ToString(dt));
  }

  {  // Add days
    date_time::Date dt(2020, 3, 1);
    dt.AddDays(-61);
    assert(std::string("2019.12.31") == date_time::ToString(dt));
  }

  {  // Next Date
    date_time::Date date1(2024, 2, 29);
    date_time::Date date2 = date1.Next();
    assert(std::string("2024.02.29") == date_time::ToString(date1));
    assert(std::string("2024.03.01") == date_time::ToString(date2));
  }

  {  // Next Date
    date_time::Date date1(2025, 2, 28);
    date_time::Date date2 = date1.Next();
    assert(std::string("2025.02.28") == date_time::ToString(date1));
    assert(std::string("2025.03.01") == date_time::ToString(date2));
  }

  {  // Next Date
    date_time::Date date1(2024, 3, 31);
    date_time::Date date2 = date1.Next();
    assert(std::string("2024.03.31") == date_time::ToString(date1));
    assert(std::string("2024.04.01") == date_time::ToString(date2));
  }

  {  // Prev Date
    date_time::Date date1(2024, 3, 1);
    date_time::Date date2 = date1.Prev();
    assert(std::string("2024.03.01") == date_time::ToString(date1));
    assert(std::string("2024.02.29") == date_time::ToString(date2));
  }

  {  // Prev Date
    date_time::Date date1(2025, 3, 1);
    date_time::Date date2 = date1.Prev();
    assert(std::string("2025.03.01") == date_time::ToString(date1));
    assert(std::string("2025.02.28") == date_time::ToString(date2));
  }

  {  // Prev Date
    date_time::Date date1(2024, 4, 1);
    date_time::Date date2 = date1.Prev();
    assert(std::string("2024.04.01") == date_time::ToString(date1));
    assert(std::string("2024.03.31") == date_time::ToString(date2));
  }

  {  // Next and Prev dates
    date_time::Date previous_date(2023, 12, 31);
    date_time::Date dt(2024, 1, 1);
    date_time::Date next_date(2024, 1, 2);
    for (int i = 0; i < 1000; ++i) {
      date_time::Date cur = previous_date.Next();
      assert(cur == dt);
      cur = dt.Next();
      assert(cur == next_date);
      cur = dt.Prev();
      assert(cur == previous_date);
      cur = next_date.Prev();
      assert(cur == dt);
      previous_date = previous_date.Next();
      assert(previous_date == dt);
      dt = dt.Next();
      assert(dt == next_date);
      next_date = dt.Next();
    }
  }

  {  // Pre-Increment test
    date_time::Date dt(2023, 12, 31);
    date_time::Date next_date(2024, 1, 1);
    for (int i = 0; i < 1000; ++i) {
      assert(++dt == next_date);
      next_date = next_date.Next();
    }
  }

  {  // Post-Increment test
    date_time::Date dt(2023, 12, 31);
    date_time::Date next_date(2024, 1, 1);
    for (int i = 0; i < 1000; ++i) {
      dt++;
      assert(dt == next_date);
      next_date = next_date.Next();
    }
  }

  {  // Post-Increment test
    date_time::Date dt(2023, 12, 31);
    date_time::Date next_date = dt;
    for (int i = 0; i < 1000; ++i) {
      assert(dt++ == next_date);
      next_date = next_date.Next();
    }
  }

  {  // Pre-decrement test
    date_time::Date dt(2025, 1, 1);
    date_time::Date previous_date(2024, 12, 31);
    for (int i = 0; i < 1000; ++i) {
      assert(--dt == previous_date);
      previous_date = previous_date.Prev();
    }
  }

  {  // Post-decrement test
    date_time::Date dt(2025, 1, 1);
    date_time::Date previous_date(2024, 12, 31);
    for (int i = 0; i < 1000; ++i) {
      dt--;
      assert(dt == previous_date);
      previous_date = previous_date.Prev();
    }
  }

  {  // Post-decrement test
    date_time::Date dt(2023, 12, 31);
    date_time::Date next_date = dt;
    for (int i = 0; i < 1000; ++i) {
      assert(dt-- == next_date);
      next_date = next_date.Prev();
    }
  }

  {  // Is leap tests
    assert(date_time::Date::IsLeapYear(2025) == false);
    assert(date_time::Date::IsLeapYear(2024) == true);
    assert(date_time::Date::IsLeapYear(2023) == false);
    assert(date_time::Date::IsLeapYear(2020) == true);
    assert(date_time::Date::IsLeapYear(2019) == false);
    assert(date_time::Date::IsLeapYear(2000) == true);
    assert(date_time::Date::IsLeapYear(1999) == false);
    assert(date_time::Date::IsLeapYear(1900) == false);
    assert(date_time::Date::IsLeapYear(1800) == false);
    assert(date_time::Date::IsLeapYear(1600) == true);
  }

  {
    date_time::Date date1 = Date(2025, 2, 11);
    date_time::Date date2 = Date(2025, 2, 12);
    date_time::Date date3 = date1;
    assert(date1 == date3);
    assert(date1 != date2);
    assert(date1 < date2);
    assert(date1 <= date2);
    assert(date1 <= date3);
    assert(date2 > date1);
    assert(date2 >= date3);
    assert(date1 >= date3);
  }
  {  // test weekdays
    date_time::Date dt(2026, 1, 1);
    assert(date_time::Weekday::kThursday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kFriday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kSaturday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kSunday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kMonday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kTuesday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kWednesday == dt.weekday());
    dt.AddDays(1);
    assert(date_time::Weekday::kThursday == dt.weekday());
  }

  std::cout << "TestDate OK" << '\n';
}

/*
        Tests for class `DateTime`
*/

void TestDateTime() {
  {  // julian_day_number()
    date_time::Date dt(2000, 01, 01);
    assert(2451545 == dt.julian_day_number());
  }

  {  // Valid Date 2025.02.01
    date_time::DateTime dt(2025, 2, 1);
    assert(2025 == dt.year());
    assert(2 == dt.month());
    assert(1 == dt.day());
    assert(0 == dt.hour());
    assert(0 == dt.minute());
    assert(0 == dt.second());
    assert(date_time::Weekday::kSaturday == dt.weekday());
    assert(false == dt.IsLeapYear());
    assert(std::string("2025.02.01 00:00:00") == date_time::ToString(dt));
  }

  {  // Valid Date 2025.02.01 12:40:15
    date_time::DateTime dt(2025, 2, 1, 12, 40, 15);
    assert(2025 == dt.year());
    assert(2 == dt.month());
    assert(1 == dt.day());
    assert(12 == dt.hour());
    assert(40 == dt.minute());
    assert(15 == dt.second());
    assert(date_time::Weekday::kSaturday == dt.weekday());
    assert(false == dt.IsLeapYear());
    assert(std::string("2025.02.01 12:40:15") == date_time::ToString(dt));
  }

  {  // Invalid Date. Throw invalid argument exception
    try {
      date_time::DateTime date1(2025, 13, 10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Date (zero). Throw invalid argument exception
    try {
      date_time::DateTime date2(2025, 0, 10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Date (negative). Throw invalid argument exception
    try {
      date_time::DateTime date3(2025, -1, 10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Date (negative). Throw invalid argument exception
    try {
      date_time::DateTime dt4(2025, 1, -10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Date (zero). Throw invalid argument exception
    try {
      date_time::DateTime dt5(2025, 1, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time (negative). Throw invalid argument exception
    try {
      date_time::DateTime dt6(2025, 1, 10, -10, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time (negative). Throw invalid argument exception
    try {
      date_time::DateTime dt7(2025, 1, 10, 10, -10, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time (negative). Throw invalid argument exception
    try {
      date_time::DateTime dt8(2025, 1, 10, 10, 10, -10);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time. Throw invalid argument exception
    try {
      date_time::DateTime dt9(2025, 1, 10, 24, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time. Throw invalid argument exception
    try {
      date_time::DateTime dt10(2025, 1, 10, 10, 60, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid Time. Throw invalid argument exception
    try {
      date_time::DateTime dt11(2025, 1, 10, 10, 10, 60);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Invalid day 32 for months with 31 days. Throw invalid argument
     // exception
    int month_to_check_31[] = {1, 3, 5, 7, 8, 10, 12};
    for (int i : month_to_check_31) {
      bool res{true};
      try {
        date_time::DateTime date1(2025, i, 32);
        assert(res == false);
      } catch (const std::invalid_argument& error) {
      } catch (...) {
        assert(res == false);
      }
    }
  }

  {  // Invalid day 31 for months with 30 days. Throw invalid argument
     // exception
    int month_to_check_30[] = {4, 6, 9, 11};
    for (int i : month_to_check_30) {
      bool res{true};
      try {
        date_time::DateTime date1(2025, i, 31);
        assert(res == false);
      } catch (const std::invalid_argument& error) {
      } catch (...) {
        assert(res == false);
      }
    }
  }

  {  // Invalid day 30 for february. Throw invalid argument exception
    bool res{true};
    try {
      date_time::DateTime date1(2000, 2, 30);
      assert(res == false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(res == false);
    }
  }

  {  // Valid day 29 for february. Throw invalid argument exception
    date_time::DateTime dt(2000, 2, 29);
    assert(2000 == dt.year());
    assert(2 == dt.month());
    assert(29 == dt.day());
    assert(date_time::Weekday::kTuesday == dt.weekday());
    assert(true == dt.IsLeapYear());
    assert(std::string("2000.02.29 00:00:00") == date_time::ToString(dt));
  }

  {  // Valid day 29 for february. Throw invalid argument exception
    date_time::DateTime dt(2024, 2, 29);
    assert(2024 == dt.year());
    assert(2 == dt.month());
    assert(29 == dt.day());
    assert(date_time::Weekday::kThursday == dt.weekday());
    assert(true == dt.IsLeapYear());
    assert(std::string("2024.02.29 00:00:00") == date_time::ToString(dt));
  }

  {  // Add days
    date_time::DateTime dt(2019, 12, 31, 10, 0, 0);
    dt.AddDays(60);
    assert(std::string("2020.02.29 10:00:00") == date_time::ToString(dt));
  }

  {  // Add days
    date_time::DateTime dt(2019, 12, 31, 10, 0, 0);
    dt.AddDays(61);
    assert(std::string("2020.03.01 10:00:00") == date_time::ToString(dt));
  }

  {  // Add days
    date_time::DateTime dt(2020, 3, 1, 10, 0, 0);
    dt.AddDays(-61);
    assert(std::string("2019.12.31 10:00:00") == date_time::ToString(dt));
  }

  {  // Add hours
    date_time::DateTime dt(2020, 2, 28, 23, 0, 0);
    dt.AddHours(60);
    assert(std::string("2020.03.02 11:00:00") == date_time::ToString(dt));
  }

  {  // Add minutes
    date_time::DateTime dt(2020, 2, 28, 23, 59, 0);
    dt.AddMinutes(59);
    assert(std::string("2020.02.29 00:58:00") == date_time::ToString(dt));
  }

  {  // Add seconds
    date_time::DateTime dt(2020, 2, 28, 23, 59, 50);
    dt.AddSeconds(59);
    assert(std::string("2020.02.29 00:00:49") == date_time::ToString(dt));
  }

  {  // Add seconds
    date_time::DateTime dt(2024, 12, 31, 23, 59, 59);
    dt.AddSeconds(1);
    assert(std::string("2025.01.01 00:00:00") == date_time::ToString(dt));
  }

  {  // Add seconds
    date_time::DateTime dt(2025, 1, 1, 0, 0, 0);
    dt.AddSeconds(-1);
    assert(std::string("2024.12.31 23:59:59") == date_time::ToString(dt));
  }

  {  // Is leap tests
    assert(date_time::DateTime::IsLeapYear(2025) == false);
    assert(date_time::DateTime::IsLeapYear(2024) == true);
    assert(date_time::DateTime::IsLeapYear(2023) == false);
    assert(date_time::DateTime::IsLeapYear(2020) == true);
    assert(date_time::DateTime::IsLeapYear(2019) == false);
    assert(date_time::DateTime::IsLeapYear(2000) == true);
    assert(date_time::DateTime::IsLeapYear(1999) == false);
    assert(date_time::DateTime::IsLeapYear(1900) == false);
    assert(date_time::DateTime::IsLeapYear(1800) == false);
    assert(date_time::DateTime::IsLeapYear(1600) == true);
  }

  {
    date_time::DateTime date1 = DateTime(2025, 2, 11);
    date_time::DateTime date2 = DateTime(2025, 2, 12);
    date_time::DateTime date3 = date1;
    assert(date1 == date3);
    assert(date1 != date2);
    assert(date1 < date2);
    assert(date1 <= date2);
    assert(date1 <= date3);
    assert(date2 > date1);
    assert(date2 >= date3);
    assert(date1 >= date3);
  }

  {
    date_time::DateTime date1 = DateTime(2025, 2, 11, 23, 59, 0);
    date_time::DateTime date2 = DateTime(2025, 2, 11, 23, 59, 1);
    date_time::DateTime date3 = date1;
    assert(date1 == date3);
    assert(date1 != date2);
    assert(date1 < date2);
    assert(date1 <= date2);
    assert(date1 <= date3);
    assert(date2 > date1);
    assert(date2 >= date3);
    assert(date1 >= date3);
  }

  {  // Get friday
    date_time::DateTime dt = DateTime(2024, 12, 27, 23, 59, 0);
    assert(dt.weekday() == date_time::Weekday::kFriday);
  }

  {  // Get saturday
    date_time::DateTime dt = DateTime(2024, 12, 28, 23, 59, 0);
    assert(dt.weekday() == date_time::Weekday::kSaturday);
  }

  {  // Get sunday
    date_time::DateTime dt = DateTime(2024, 12, 29, 23, 59, 0);
    assert(dt.weekday() == date_time::Weekday::kSunday);
  }

  std::cout << "TestDateTime OK" << '\n';
}

void TestTimediff() {
  {  // Throw invalid argument exception
    try {
      date_time::TimeDiff ts(0, -24, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Throw invalid argument exception
    try {
      date_time::TimeDiff ts(0, 24, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Throw invalid argument exception
    try {
      date_time::TimeDiff ts(0, -60, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Throw invalid argument exception
    try {
      date_time::TimeDiff ts(0, 60, 0, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Throw invalid argument exception
    try {
      date_time::TimeDiff ts(0, 0, -60, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Throw invalid argument exception
    try {
      date_time::TimeDiff ts(0, 0, 60, 0);
      assert(false);
    } catch (const std::invalid_argument& error) {
    } catch (...) {
      assert(false);
    }
  }

  {  // Valid TimeDiff
    date_time::TimeDiff ts(0, 0, 0, 0);
    assert(0 == ts.days());
    assert(0 == ts.hours());
    assert(0 == ts.minutes());
    assert(0 == ts.seconds());
  }

  {  // Valid TimeDiff
    date_time::TimeDiff ts(1, 2, 3, 4);
    assert(1 == ts.days());
    assert(2 == ts.hours());
    assert(3 == ts.minutes());
    assert(4 == ts.seconds());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(0, 0, 0, 50);
    assert(50 == ts.total_seconds());
    assert(0 == ts.total_minutes());
    assert(0 == ts.total_hours());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(0, 0, 3, 50);
    assert(230 == ts.total_seconds());
    assert(3 == ts.total_minutes());
    assert(0 == ts.total_hours());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(0, 2, 3, 50);
    assert(7430 == ts.total_seconds());
    assert(123 == ts.total_minutes());
    assert(2 == ts.total_hours());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(1, 2, 3, 50);
    assert(93830 == ts.total_seconds());
    assert(1563 == ts.total_minutes());
    assert(26 == ts.total_hours());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(0, 0, 0, -50);
    assert(-50 == ts.total_seconds());
    assert(0 == ts.total_minutes());
    assert(0 == ts.total_hours());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(0, 0, -3, -50);
    assert(-230 == ts.total_seconds());
    assert(-3 == ts.total_minutes());
    assert(0 == ts.total_hours());
  }

  {  // Total seconds, minutes, hours
    date_time::TimeDiff ts(0, -2, -3, -50);
    assert(-7430 == ts.total_seconds());
    assert(-123 == ts.total_minutes());
    assert(-2 == ts.total_hours());
  }

  {  // Total seconds
    date_time::TimeDiff ts(-1, -2, -3, -50);
    assert(-93830 == ts.total_seconds());
    assert(-1563 == ts.total_minutes());
    assert(-26 == ts.total_hours());
  }

  {
    date_time::TimeDiff time_diff1(1, 2, 3, 10);
    date_time::TimeDiff time_diff2(1, 0, 4, 0);
    date_time::TimeDiff time_diff3 = time_diff1;
    date_time::TimeDiff time_diff4(-1, -2, -3, -10);
    assert(time_diff1 == time_diff3);
    assert(time_diff1 != time_diff2);
    assert(time_diff2 < time_diff1);
    assert(time_diff3 <= time_diff1);
    assert(time_diff4 < time_diff2);
    assert(time_diff1 > time_diff2);
    assert(time_diff1 >= time_diff3);
    assert(time_diff2 > time_diff4);
  }

  {
    date_time::Time time1(10, 52, 10);
    date_time::Time time2(11, 12, 5);
    date_time::TimeDiff time_diff1 = time2 - time1;
    assert(time_diff1.days() == 0);
    assert(time_diff1.hours() == 0);
    assert(time_diff1.minutes() == 19);
    assert(time_diff1.seconds() == 55);
    assert(time_diff1.total_hours() == 0);
    assert(time_diff1.total_minutes() == 19);
    assert(time_diff1.total_seconds() == 1195);
  }

  {
    date_time::Date date1(2024, 12, 31);
    date_time::Date date2(2024, 12, 25);
    date_time::TimeDiff time_diff1 = date1 - date2;
    assert(time_diff1.days() == 6);
    assert(time_diff1.hours() == 0);
    assert(time_diff1.minutes() == 0);
    assert(time_diff1.seconds() == 0);
    assert(time_diff1.total_hours() == 144);
    assert(time_diff1.total_minutes() == 8640);
    assert(time_diff1.total_seconds() == 518400);
  }

  {
    date_time::DateTime date1(2024, 12, 31);
    date_time::DateTime date2(2024, 12, 25);
    date_time::TimeDiff time_diff1 = date1 - date2;
    assert(time_diff1.days() == 6);
    assert(time_diff1.hours() == 0);
    assert(time_diff1.minutes() == 0);
    assert(time_diff1.seconds() == 0);
    assert(time_diff1.total_hours() == 144);
    assert(time_diff1.total_minutes() == 8640);
    assert(time_diff1.total_seconds() == 518400);
  }

  {
    date_time::DateTime date1(2024, 12, 31);
    date_time::DateTime date2(2024, 11, 25);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == -36);
    assert(time_diff1.hours() == 0);
    assert(time_diff1.minutes() == 0);
    assert(time_diff1.seconds() == 0);
  }

  {
    date_time::DateTime date1(2024, 12, 31);
    date_time::DateTime date2(2024, 11, 25);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == -36);
    assert(time_diff1.hours() == 0);
    assert(time_diff1.minutes() == 0);
    assert(time_diff1.seconds() == 0);
  }
  {
    date_time::DateTime date1(2024, 12, 31, 11, 0, 0);
    date_time::DateTime date2(2024, 12, 25, 13, 0, 0);
    date_time::TimeDiff time_diff1 = date2 - date1;
    std::cerr << time_diff1.days() << std::endl;
    std::cerr << time_diff1.hours() << std::endl;
    assert(time_diff1.days() == -5);
    assert(time_diff1.hours() == -22);
  }

  {
    date_time::DateTime date1(2024, 12, 31, 11, 55, 12);
    date_time::DateTime date2(2024, 12, 25, 13, 32, 5);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == -5);
    assert(time_diff1.hours() == -22);
    assert(time_diff1.minutes() == -23);
    assert(time_diff1.seconds() == -7);
  }

  {
    date_time::DateTime date1(2024, 12, 31, 11, 32, 5);
    date_time::DateTime date2(2024, 12, 25, 13, 55, 12);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == -5);
    assert(time_diff1.hours() == -21);
    assert(time_diff1.minutes() == -36);
    assert(time_diff1.seconds() == -53);
  }

  {
    date_time::DateTime date1(2024, 12, 31, 13, 32, 5);
    date_time::DateTime date2(2024, 12, 25, 11, 55, 12);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == -6);
    assert(time_diff1.hours() == -1);
    assert(time_diff1.minutes() == -36);
    assert(time_diff1.seconds() == -53);
  }

  {
    date_time::DateTime date1(2024, 12, 31);
    date_time::DateTime date2(2023, 11, 25);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == -402);
    assert(time_diff1.hours() == 0);
    assert(time_diff1.minutes() == 0);
    assert(time_diff1.seconds() == 0);
  }

  {
    date_time::DateTime date1(2024, 12, 31, 7, 32, 5);
    date_time::DateTime date2(2024, 12, 31, 14, 55, 12);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == 0);
    assert(time_diff1.hours() == 7);
    assert(time_diff1.minutes() == 23);
    assert(time_diff1.seconds() == 7);
  }

  {
    date_time::DateTime date1(2025, 2, 27, 15, 58, 2);
    date_time::DateTime date2(2025, 3, 2, 9, 0, 0);
    date_time::TimeDiff time_diff1 = date2 - date1;
    assert(time_diff1.days() == 2);
    assert(time_diff1.hours() == 17);
    assert(time_diff1.minutes() == 1);
    assert(time_diff1.seconds() == 58);
    assert(time_diff1.total_seconds() == ((2 * 24 + 17) * 60 + 1) * 60 + 58);
  }

  {
    date_time::DateTime date1(2025, 2, 27, 15, 58, 2);
    date_time::DateTime date2(2025, 3, 2, 9, 0, 0);
    date_time::TimeDiff time_diff1 = date2 - date1;
    date_time::DateTime date3 = date1 + time_diff1;
    assert(date3 == date2);
    date3 = date2 - time_diff1;
    assert(date3 == date1);
  }

  {
    date_time::DateTime date1(2000, 2, 27, 15, 0, 30);
    date_time::DateTime date2(2000, 3, 2, 9, 0, 10);
    date_time::TimeDiff time_diff1 = date2 - date1;
    date_time::DateTime date3 = date1 + time_diff1;
    assert(date3 == date2);
    date3 = date2 - time_diff1;
    assert(date3 == date1);
  }

  std::cout << "TestTimeDiff OK" << '\n';
}
