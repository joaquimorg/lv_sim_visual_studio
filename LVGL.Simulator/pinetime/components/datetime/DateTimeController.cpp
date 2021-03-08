#include "DateTimeController.h"

#include <chrono>
#include <ctime>

namespace Pinetime {
  namespace Controllers {
        void DateTime::SetTime(std::uint16_t year, 
        std::uint8_t month, 
        std::uint8_t day, 
        std::uint8_t dayOfWeek, 
        std::uint8_t hour, 
        std::uint8_t minute, 
        std::uint8_t second, 
        std::uint32_t systickCounter)
        {
            this->year = year;
            this->month = static_cast<Months>(month);
            this->day = day;
            if(dayOfWeek != 0){
                this->dayOfWeek = static_cast<Days>(dayOfWeek);
            } else {
                this->dayOfWeek = Days::Sunday;
            }
            this->hour = hour;
            this->minute = minute;
            this->second = second;
        }

        void DateTime::UpdateTime(std::uint32_t systickCounter){
            currentDateTime =  std::chrono::system_clock::now();
            auto t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto now = std::localtime(&t_c);
            SetTime((now->tm_year + 1900),
                (now->tm_mon + 1),
                now->tm_mday,
                now->tm_wday,
                now->tm_hour,
                now->tm_min,
                now->tm_sec,
                0
            );

        }


        const char* DateTime::MonthShortToString() {
            return DateTime::MonthsString[(uint8_t)month];
        }

        const char* DateTime::MonthShortToStringLow() {
            return DateTime::MonthsStringLow[(uint8_t)month];
        }

        const char* DateTime::MonthsToStringLow() {
            return DateTime::MonthsLow[(uint8_t)month];
        }

        const char* DateTime::DayOfWeekToString() {
            return DateTime::DaysString[(uint8_t)dayOfWeek];
        }

        const char* DateTime::DayOfWeekShortToString() {
            return DateTime::DaysStringShort[(uint8_t)dayOfWeek];
        }

        const char* DateTime::DayOfWeekToStringLow() {
            return DateTime::DaysStringLow[(uint8_t)dayOfWeek];
        }

        const char* DateTime::DayOfWeekShortToStringLow() {
            return DateTime::DaysStringShortLow[(uint8_t)dayOfWeek];
        }


        char const* DateTime::DaysStringLow[] = {
                "--",
                "Monday",
                "Tuesday",
                "Wednesday",
                "Thursday",
                "Friday",
                "Saturday",
                "Sunday"
        };

        char const* DateTime::DaysStringShortLow[] = {
                "--",
                "Mon",
                "Tue",
                "Wed",
                "Thu",
                "Fri",
                "Sat",
                "Sun"
        };

        char const* DateTime::DaysStringShort[] = {
                "--",
                "MON",
                "TUE",
                "WED",
                "THU",
                "FRI",
                "SAT",
                "SUN"
        };

        char const* DateTime::DaysString[] = {
                "--",
                "MONDAY",
                "TUESDAY",
                "WEDNESDAY",
                "THURSDAY",
                "FRIDAY",
                "SATURDAY",
                "SUNDAY"
        };

        char const* DateTime::MonthsString[] = {
                "--",
                "JAN",
                "FEB",
                "MAR",
                "APR",
                "MAY",
                "JUN",
                "JUL",
                "AUG",
                "SEP",
                "OCT",
                "NOV",
                "DEC"
        };

        char const* DateTime::MonthsStringLow[] = {
                "--",
                "Jan",
                "Feb",
                "Mar",
                "Apr",
                "May",
                "Jun",
                "Jul",
                "Aug",
                "Sep",
                "Oct",
                "Nov",
                "Dec"
        };

        char const* DateTime::MonthsLow[] = {
                "--",
                "January",
                "February",
                "March",
                "April",
                "May",
                "June",
                "July",
                "August",
                "September",
                "October",
                "November",
                "December"
        };
  }
}
