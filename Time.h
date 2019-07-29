/* Documentation is provided in the Lab Report as well. */

#ifndef TIME_H
#define TIME_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

#include "Base.h"
using namespace std;

class Time {
    public:
        /* Documentation is provided in the Lab Report as well. */

        /* If  Requirement is not explicitly stated,
         * there is no requirement.
         */

        /* Constructor. */
        Time();

        /* Parameters:
            * `time_str` in Hour:Min format.
         * Result: return a Time object that converted from  `time_str`.
         */
        Time str_to_time (const string time_str);

        /* Parameters:
             * `time`: time to be convert.
         * Result: return a valid `Time time` from hour-min format to minutes.
         */
        float time_to_min (const Time time);

        /* Requirement: `Time end` is later than `Time start`.
         * Parameters:
            * `start`: start time.
            * `end`: end time.
         * Result: return the passed duration from `Time start` to `Time end`.
         */
        Time elapsed_time (const Time start, const Time end);

        /* Parameters:
             * `i_hour`: input time's hour value for checking.
             * `i_min`: input time's min value for checking.
         * Result:
                * true: `0 <= i_hour <= 23` and `0 <= i_min <= 59`.
                * false: otherwise.
         */
        bool is_time (const int i_hour, const int i_min);

        /* Parameters:
            * `time_1` and `time_2`: times to check.
         * Result:
            * true: `time_2` is same or later than `time_1`.
            * false: otherwise.
         */
        bool is_same_or_later (const Time time_1, const Time time_2);

        /* Parameters:
         * `last_time_str`, `current_time_str`: times to check, in Hour:Min format.
         * Result:
            * true: if `current_time_str` is later than `last_time_str` whereas both of them are legit time (`is_time() == true`).
            * false: otherwise.
         */
        bool is_legal_input (const string last_time_str, const string current_time_str);


    private:
        int hour;
        int min;
};

Time :: Time() {
}


Time Time :: str_to_time (const string time_str) {
    istringstream is (time_str);
    string str_token;
    string str_list[2];
    int i = 0;
    while (getline(is, str_token, ':') && i <= 2) {
        str_list[i] = str_token;
        i++;
    }

    int i_hour = stoi (str_list[0]);
    int i_min= stoi (str_list[1]);

    Time time_temp;
    time_temp.hour = i_hour;
    time_temp.min = i_min;
    return time_temp;

}

float Time :: time_to_min (const Time time) {
    float total_min = 0;
    total_min = time.hour * 60 + time.min;
    return total_min;
}


Time Time :: elapsed_time (const Time start, const Time end) {
    Time time_temp;
    if (end.hour == start.hour) {
        time_temp.hour = 0;
        time_temp.min = end.min - start.min;
    }
    if (end.hour > start.hour) {
        time_temp.hour = end.hour - start.hour - 1;
        time_temp.min = end.min + 60 - start.min;
    }

    return time_temp;
}

bool Time :: is_time (const int i_hour, const int i_min) {
    if (0 <= i_hour && i_hour <= 23 && 0 <= i_min && i_min <= 59) {
        return true;
    }
    else {
        return false;
    }
}




bool Time :: is_same_or_later (const Time time_1, const Time time_2) {
    if (time_2.hour > time_1.hour) {
        return true;
    }
    else if (time_2.hour == time_1.hour && time_2.min >= time_1.min) {
        return true;
    }
    else {
        return false;
    }
}


bool Time :: is_legal_input (const string last_time_str, const string current_time_str) {
    Time last_time, current_time;
    last_time = str_to_time (last_time_str);
    current_time = str_to_time (current_time_str);
    if (is_time (last_time.hour, last_time.min) &&
        is_time (current_time.hour, current_time.min) &&
        is_same_or_later (last_time, current_time)) {
        return true;
    }
    else {
        return false;
    }
}


#endif
