/* Documentation is provided in the Lab Report as well. */

#ifndef BASE_H
#define BASE_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <iomanip>

#include "Time.h"

using namespace std;

class Base {
    public:
        /* Documentation is provided in the Lab Report as well. */


        /* Since the `parameter`s are all quite self-explanatory in the
         * following functions, this documentation section will omit the
         * introduction of `parameter`s.
         */

        /* If  Requirement is not explicitly stated,
         * there is no requirement.
         */

        /* Constructor
         * Result: set `c_order_id` and `c_driver_id` to `0`.
         */
        Base();


        /* Triggered by `order` command.
         * Result: (In this order's `vector` node)
            * pushed `map`s with `key` of `order_info`, `order_time`, `is_serve`, `serve_time`, `is_dept`, `dept_time`, `driver_name`, `is_delv`, `delv_time`, `driver_tip`, `is_arrive`, and `arrive_time` to `order_rec`.
            * set key `order_info` to value `i_order_info`.
            * set key `order_time` to value `order_time`.
            * set rest of the keys to value `"NO"` or `"UNKNOWN"`.
         */
        void add_order (const string i_order_info, const string i_order_time); // order


        /* Triggered by `serve` command.
         * Requirement: There is a placed but not-yet-cooked order.
         * Result: (In this order's `vector` node)
             * set key `is_serve` to value `"YES"`;
             * set key `serve_time` to value `i_serve_time`;
         */
        void serve_order (const string i_serve_time) throw (logic_error); // serve


        /* Triggered by `depart` command.
         * Requirement:
             * There is a served but not-yet-departed order.
             * The assigned `i_driver_name` is available.
         * Result: (In this order's `vector` node)
             * set key `is_dept` to value `"YES"`.
             * set key `dept_time` to value `i_dept_time`.
             * set key `driver_name` to value `i_driver_name`.
         */
        void dept_driver (const string i_driver_name, const string i_dept_time) throw (logic_error); // depart

        /* Triggered by `delivery` command.
         * Requirement:
             * There is a departed but not-yet-delivered order.
             * The assigned `i_driver_name` is matched with the departed driver.
         * Result: (In this order's `vector` node)
             * set key `is_delv` to value `"YES"`.
             * set key `delv_time` to value `i_delv_time`.
             * set key `driver_tip` to value `i_driver_tip`.
         */
        void delv_driver (const string i_driver_name, const string i_delv_time, const string i_driver_tip) throw (logic_error); // delivery

        /* Triggered by `arrive` command.
         * Requirement:
             * There is a delivered but not-yet-arrived driver.
             * The assigned `i_driver_name` is matched with the delivered driver.
         * Result: (In this order's `vector` node)
             * set key `is_arrive` to `"YES"`.
             * set key `arrive_time` to `i_arrive_time`.
         */
        void arrive_driver (const string i_driver_name, const string i_arrive_time) throw (logic_error);  // arrive


        /* Triggered by `login` command.
         * Requirement: driver name has no white-spaces.
         * Result: (In this driver's `vector` node)
             * pushed `map`s with key of `driver_name`, `is_login`, `is_dept`, `total_delv_count`, `total_delv_time`, `total_drive_time`, and `total_tip` to `driver_rec`.
             * set key `driver_name` to value `driver_id`, which is obtained from `c_driver_id`.
             * set key `is_login` to value `1`.
             * set all other keys to value `0`.
         */
        void login_driver (const string i_driver_name); // login

        /* Triggered by `logout` command.
         * Requirement: `i_driver_name` must be available.
         * Result: (In this driver's `vector` node)
             * set key `is_login` to value `0`.
         */
        void logout_driver (const string i_driver_name) throw (logic_error); // logout

        /* Triggered by `status` command.
         * Result:
             * Loop through `order_rec` and print out all `is_delv = "NO"` order.
             * as required in the sample output.
         */
        void show_status (); // status

        /* Trigged by `summary` command.
         * Result:
            * Loop through `order_rec`, find all orders with `is_delv = "NO"`,
            * Calculate its values (as required in the sample output)
            * and then store it in `driver_rec`.
            * Then loop through `driver_rec` and print out all infomration as
            * required in the sample output.
         */
        void show_summary (); // summary

        /* Requirement: `i_driver_name` exists in `driver_sys`.
         * Result: return `i_drive_name`'s `driver_id` by checking `driver_sys`.
         */
        float get_driver_id (const string i_driver_name) throw (logic_error);

        /* Requirement: `i_driver_id` is bigger than `0` while less than `driver_sys.size()`;
         * Result: return `driver_id`'s `i_drive_name` by checking `driver_sys`.
         */
        string get_driver_name (const float i_driver_id) throw (logic_error);

        /* Requirement: `i_order_info` exists in `order_sys`.
         * Result: return `i_order_info`'s `order_id` by checking `order_sys`.
         */
        int get_order_id (const string i_order_info) throw (logic_error);

        /* Requirement: `i_driver_name` exists in `driver_sys`.
         * Result:
             * true: `i_driver_name` is logged-in but not departed.
             * false: otherwise.
         */
        bool is_driver_avbl (const string i_driver_name) throw (logic_error);

    private:
        vector<map<string, string>> order_rec;
        vector<map<string, float>> driver_rec;

        int c_order_id;
        float c_driver_id;
        map<string, int> order_sys;
        map<string, float> driver_sys;

        queue<int> to_serve_queue;
        queue<int> to_dept_queue;
        map<float, int> to_delv_map; // driver_id, order_id.
        map<float, int> to_arrive_map; // driver_id, order_id.

};


Base :: Base () {
    c_order_id = 0;
    c_driver_id = 0.0;
}

void Base :: add_order (const string i_order_info, const string i_order_time) {
    map<string, string> n_map;
    n_map.insert (pair<string, string> ("order_info", i_order_info));
    n_map.insert (pair<string, string> ("order_time", i_order_time));
    n_map.insert (pair<string, string> ("is_serve", "NO"));
    n_map.insert (pair<string, string> ("serve_time", "UNKNOWN"));
    n_map.insert (pair<string, string> ("is_dept", "NO"));
    n_map.insert (pair<string, string> ("dept_time", "UNKNOWN"));
    n_map.insert (pair<string, string> ("driver_name", "UNKNOWN"));
    n_map.insert (pair<string, string> ("is_delv", "NO"));
    n_map.insert (pair<string, string> ("delv_time", "UNKNOWN"));
    n_map.insert (pair<string, string> ("driver_tip", "UNKNOWN"));
    n_map.insert (pair<string, string> ("is_arrive", "NO"));
    n_map.insert (pair<string, string> ("arrive_time", "UNKNOWN"));
    order_rec.push_back (n_map);

    int order_id = c_order_id;
    to_serve_queue.push (order_id);
    order_sys.insert (pair<string, int> (i_order_info, order_id));
    c_order_id++;
}


void Base :: serve_order (const string i_serve_time) throw (logic_error) {
    if (to_serve_queue.empty()) {
        throw logic_error ("No order to serve.");
    }
    int order_id = to_serve_queue.front();
    order_rec[order_id]["is_serve"] = "YES";
    order_rec[order_id]["serve_time"] = i_serve_time;
    to_dept_queue.push (order_id);
    to_serve_queue.pop();
}

void Base :: dept_driver (const string i_driver_name, const string i_dept_time) throw (logic_error) {
    if (to_dept_queue.empty() || !is_driver_avbl (i_driver_name)) {
        throw logic_error ("No served order to depart, or assigned driver is not available.");
    }

    int order_id = to_dept_queue.front();
    float driver_id = get_driver_id (i_driver_name);
    order_rec[order_id]["is_dept"] = "YES";
    order_rec[order_id]["dept_time"] = i_dept_time;
    order_rec[order_id]["driver_name"] = i_driver_name;
    to_delv_map.insert (pair<float, int> (driver_id, order_id));
    to_dept_queue.pop();
}


void Base :: delv_driver (const string i_driver_name, const string i_delv_time, const string i_driver_tip) throw (logic_error) {
    float driver_id = get_driver_id (i_driver_name);
    if (to_delv_map.empty() || (to_delv_map.count (driver_id) == 0)) {
        throw logic_error ("No departed order to delivery, or delivering driver does not match with the departed driver.");
    }
    auto delv_it = to_delv_map.find (driver_id);
    int order_id = delv_it->second;
    order_rec[order_id]["is_delv"] = "YES";
    order_rec[order_id]["delv_time"] = i_delv_time;
    order_rec[order_id]["driver_tip"] = i_driver_tip;
    to_arrive_map.insert (pair<float, int> (driver_id, order_id));
    to_delv_map.erase (delv_it);
}

void Base :: arrive_driver (const string i_driver_name, const string i_arrive_time) throw (logic_error) {
    float driver_id = get_driver_id (i_driver_name);
    if (to_arrive_map.empty() || (to_arrive_map.count (driver_id) == 0)) {
        throw logic_error ("No delivered order to arrive from, or arriving driver does not match with the delivered driver.");
    }
    auto arrive_it = to_arrive_map.find (driver_id);
    int order_id = arrive_it->second;
    order_rec[order_id]["is_arrive"] = "YES";
    order_rec[order_id]["arrive_time"] = i_arrive_time;
    to_arrive_map.erase (arrive_it);
}

void Base :: login_driver (const string i_driver_name) {
    map<string, float> n_map;
    float driver_id = c_driver_id;
    n_map.insert (pair<string, float> ("driver_name", driver_id));
    n_map.insert (pair<string, float> ("is_login", 1));
    n_map.insert (pair<string, float> ("is_dept", 0));

    n_map.insert (pair<string, float> ("total_delv_count", 0));
    n_map.insert (pair<string, float> ("total_delv_time", 0));
    n_map.insert (pair<string, float> ("total_drive_time", 0));
    n_map.insert (pair<string, float> ("total_tip", 0));
    driver_rec.push_back (n_map);

    driver_sys.insert (pair<string, float> (i_driver_name, driver_id));
    c_driver_id++;
}

void Base :: logout_driver (const string i_driver_name) throw (logic_error) {
    float driver_id = get_driver_id (i_driver_name);
    if (!is_driver_avbl(i_driver_name)) {
        throw logic_error ("Attempted to logout a driver who is not available.");
    }
    driver_rec[driver_id]["is_login"] = 0;
}

float Base :: get_driver_id (const string i_driver_name) throw (logic_error) {
    if (driver_sys.count (i_driver_name) == 0) {
        throw logic_error ("Searched driver is not registered.");
    }
    auto driver_it = driver_sys.find (i_driver_name);
    float driver_id = driver_it->second;
    return driver_id;
}

string Base :: get_driver_name (const float i_driver_id) throw (logic_error) {
    if (i_driver_id + 1 > driver_sys.size() || i_driver_id < 0) {
        throw logic_error ("Invalid driver_id input.");
    }
    for (auto& driver_i : driver_sys) {
        if (driver_i.second == i_driver_id) {
            string driver_name = driver_i.first;
            return driver_name;
        }
    }
    return "NO_SEARCHED_DRIVER";
}

int Base :: get_order_id (const string i_order_info) throw (logic_error) {
    if (order_sys.count (i_order_info) == 0) {
        throw logic_error ("Searched order is not registered.");
    }
    auto order_it = order_sys.find (i_order_info);
    int order_id = order_it->second;
    return order_id;
}

bool Base :: is_driver_avbl (const string i_driver_name) throw (logic_error) {
    if (driver_sys.count (i_driver_name) == 0) {
        throw logic_error ("Searched driver is not registered.");
    }
    float driver_id = get_driver_id (i_driver_name);
    auto& is_login = driver_rec[driver_id].at("is_login");
    auto& is_dept = driver_rec[driver_id].at("is_dept");

    if (is_login == 1 && is_dept == 0) {
        return true;
    }
    else {
        return false;
    }
}

void Base :: show_status () {
    cout << "Orders waiting to cook:" << endl;
    for (auto& order_i : order_rec) {
        if (order_i["is_serve"] == "NO") {
            cout << "\t" << order_i["order_info"] << endl;
        }
    }
    cout << "Orders waiting to depart:" << endl;
    for (auto& order_i : order_rec) {
        if (order_i["is_serve"] == "YES" && order_i["is_dept"] == "NO") {
            cout << "\t" << order_i["order_info"] << endl;
        }
    }
    cout << "Drivers:" << endl;
    for (auto& order_i : order_rec) {
        if (order_i["is_serve"] == "YES" && order_i["is_dept"] == "YES"
            && order_i["is_delv"] == "NO") {
            cout << "\t" << order_i["driver_name"] << " " << order_i["order_info"] << endl;
        }
    }
}

void Base :: show_summary () {
    int completed_order_counter = 0;
    float all_order_durt = 0;

    for (auto& order_i : order_rec) {
        if (order_i["is_delv"] == "YES") {
            completed_order_counter++;
            Time time_temp;
            all_order_durt += time_temp.time_to_min ( time_temp.elapsed_time ( time_temp.str_to_time (order_i["order_time"]),
                                                                              time_temp.str_to_time (order_i["delv_time"]) ));

            float driver_id = get_driver_id(order_i["driver_name"]);
            driver_rec[driver_id]["total_delv_count"]++;

            float this_delv_durt;
            float this_drive_durt;
            this_delv_durt = time_temp.time_to_min ( time_temp.elapsed_time ( time_temp.str_to_time (order_i["dept_time"]),
                                                                             time_temp.str_to_time (order_i["delv_time"]) ));
            this_drive_durt = time_temp.time_to_min ( time_temp.elapsed_time ( time_temp.str_to_time (order_i["dept_time"]),
                                                                              time_temp.str_to_time (order_i["arrive_time"]) ));
            driver_rec[driver_id]["total_delv_time"] += this_delv_durt;
            driver_rec[driver_id]["total_drive_time"] += this_drive_durt;
            driver_rec[driver_id]["total_tip"] += stof (order_i["driver_tip"]);
        }
    }

    cout << "Number of orders completed: " << completed_order_counter << endl;
    cout << "Average time per delivery: ";
    if (completed_order_counter == 0) {
        cout << "N/A" << endl;
    }
    else {
        cout << fixed << setprecision(1) << all_order_durt / float (completed_order_counter) << endl;
    }


    for (auto& driver_i : driver_rec) {
        cout << "Driver " << get_driver_name(driver_i["driver_name"]) << ":" << endl;
        cout << "\t" << "Number of deliveries completed: " <<  fixed << setprecision(0) << driver_i["total_delv_count"] << endl;
        cout << "\t" << "Average time per delivery: ";
        if (driver_i["total_delv_count"] == 0) {
            cout << "N/A" << endl;
        }
        else {
            cout << fixed << setprecision(1) << driver_i["total_delv_time"] / driver_i["total_delv_count"] << endl;
        }
        cout << "\t" << "Total driving time: " << fixed << setprecision(0) << driver_i["total_drive_time"] << endl;
        cout << "\t" << "Total tips: ";
        cout << fixed << setprecision(2) << driver_i["total_tip"] << endl;
    }

}

#endif
