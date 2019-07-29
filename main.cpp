#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <stack>

#include "Base.h"
#include "Time.h"

int main () {
    Base base;

    // Input file path, given and self-designed input. Comment out one of them to proceed.
     ifstream input_file ("/Users/zhonghenry/Desktop/input.txt");
//    ifstream input_file ("/Users/zhonghenry/Desktop/input_2.txt");
    queue<string> str_queue;
    if (!input_file.is_open()) {
        cout << "Error occured while opening file." << endl;
        return 1;
    }

    Time time_temp;
    stack<string> time_stack; // stack to hold perviously input time.
    string line_buffer;
    /* To use user_input mode, undo command out of the following line,
    and then comment out line 30 */
    // while (getline (cin, line_buffer)) {
    while (getline (input_file, line_buffer)) { // read one line of input into string.
        istringstream is(line_buffer);
        string str_token;
        while (getline(is, str_token, ' ')) { // tokenize line into strings.
            str_queue.push (str_token);
        }

        string command = str_queue.front(); str_queue.pop(); // store the command from the line input.
        if (command == "login") { // check command.
            string driver_name = str_queue.front(); str_queue.pop(); // store other input according to the command.
            base.login_driver (driver_name); // call command function accordingly.
        }

        else if (command == "order") {
            string order_time = str_queue.front(); str_queue.pop();
            string order_info = order_time;

            if (!time_stack.empty()) { // invalid input protection code.
                string last_time = time_stack.top();
                if (!time_temp.is_legal_input (last_time, order_time)) {
                    cout << "Invalid time input." << endl;
                    return 2; // return if current input time is not later than/same as the pervious input.
                }
                time_stack.pop(); time_stack.push (order_time);
            }
            else {
                if (!time_temp.is_legal_input ("00:00", order_time)) {
                    cout << "Invalid time input." << endl;
                    return 2;
                }
                time_stack.push (order_time);
            }

            while (!str_queue.empty()) { // stiching order_info together.
                order_info += " ";
                order_info += str_queue.front(); str_queue.pop();
            }
            base.add_order (order_info, order_time);
        }

        else if (command == "serve") {
            string serve_time = str_queue.front(); str_queue.pop();
            if (!time_temp.is_legal_input (time_stack.top(), serve_time) || time_stack.empty()) {
                cout << "Invalid time input." << endl;
                return 2;
            }
            else {
                time_stack.pop(); time_stack.push (serve_time);
            }
            base.serve_order (serve_time);
        }

        else if (command == "depart") {
            string dept_time = str_queue.front(); str_queue.pop();
            string driver_name = str_queue.front(); str_queue.pop();
            if (!time_temp.is_legal_input (time_stack.top(), dept_time) || time_stack.empty()) {
                cout << "Invalid time input." << endl;
                return 2;
            }
            else {
                time_stack.pop(); time_stack.push (dept_time);
            }
            base.dept_driver (driver_name, dept_time);
        }

        else if (command == "deliver") {
            string delv_time = str_queue.front(); str_queue.pop();
            string driver_name = str_queue.front(); str_queue.pop();
            string driver_tip = str_queue.front(); str_queue.pop();
            if (!time_temp.is_legal_input (time_stack.top(), delv_time) || time_stack.empty()) {
                cout << "Invalid time input." << endl;
                return 2;
            }
            else {
                time_stack.pop(); time_stack.push (delv_time);
            }
            base.delv_driver (driver_name, delv_time, driver_tip);
        }

        else if (command == "arrive") {
            string arrive_time = str_queue.front(); str_queue.pop();
            string driver_name = str_queue.front(); str_queue.pop();
            if (!time_temp.is_legal_input (time_stack.top(), arrive_time) || time_stack.empty()) {
                cout << "Invalid time input." << endl;
                return 2;
            }
            else {
                time_stack.pop(); time_stack.push (arrive_time);
            }
            base.arrive_driver (driver_name, arrive_time);
        }

        else if (command == "logout") {
            string driver_name = str_queue.front(); str_queue.pop();
            base.logout_driver (driver_name);
        }

        else if (command == "status") {
            base.show_status();
            cout << endl;
        }

        else if (command == "summary") {
            base.show_summary();
            cout << endl;
        }

        else if (command == "quit") {
           // cout << "The program has been quit." << endl;
            return 0;
        }

        else {
            cout << "Invalid command input." << endl;
        }
    }

    return 3;
}
