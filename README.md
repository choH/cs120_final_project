# CS 120 Final Project | Pizza Tracking System Program

> CSCI 120, Dr. BYRNES
> Henry ZHONG, ███ omitted due to privacy concerns ███.
> Due and Submitted by 2018.12.07, 9:00.
> 
> Edited for personal GitHub exhibition on 2019.07.29.

---
This document was edited based on the original lab report of CS 120's final project; as it was not written to be an introduction of the project itself, many knowledge of the project is presumed. Please checkout [project_instruction](https://github.com/choH/cs120_final_project/media/flow_chart) to get an insight of the project requirement, and refer to **Section 2. Sample Input/Output** for execution samples.

In short, it is a command line program which manages the workflow of a pizza deliver system. Supported features: order registering, pizza making, driver assigning, driver delivering, and performance review.

Note that although the professor has given a skeleton framework in [project_instruction](https://github.com/choH/cs120_final_project/media/flow_chart), I designed and implemented my own data structure as I believe my approach is neater in terms of lines of code, and uses more advance C++ features (we only exposed to such features for the last two projects). 
In reflection, I have to admit that although my design is shorter, it sacrifices the "loosely coupled" principle of software engineering. In the later year of study, I realized that I have somehow built a lightweight relational database (utilizing the idea of id-collision) with many design flaws from database perspective.

---
## 1. Program Design

### 1.1. Core Data Structure
Our core data structure are: 
* `vector<map<string, string>> order_rec`
* `vector<map<string, float>> driver_rec`

Whereas every order shall be store as a `vector` node within `order_rec` (in a chronological order) and every logged-in driver shall be store as a `vector` node within `driver_rec`.

I choose to use `vector<map<string, string>>` as the data structure for `order_rec` mainly due to three reasons: 1) the built-in feature of dynamic allocation fits the purpose of adding orders. 2) the versatile support of data retrieving methods provided by `STL <vector>` gives my high flexibility. 3) My familiarity with `vector` from the pervious Hash Table lab.

I decided to use `map<string, string>` as the inner data structure of `order_rec` because I want to set the `key` to be a descriptive word that describing the `value` it hold; thus, the `key` must be `string` type. Also, consider the `value` should be able to hold a variety set of information (`time`, `name`, `YES/NO`, and etc.), it is also reasonable to be `string`. Similarly, since most of the information regarding `driver` is number, so the `key` for `driver_rec` is set to be `float`.

Regarding some minor data structure design: 
* Some `queue` and `map` like `to_serve_queue`, `to_dept_queue`, `to_delv_map`, and `to_arrive_map` are created to simulate the matching of orders with implicit commands.
* `map<string, int> order_sys` and `map<string, float> driver_sys` are built to assign numerical ID to `order`s and `driver`s. 
* `stack<string> time_stack` and `queue<string> str_queue` are used in `main.c` to keep track of the latest time-related input, and to store tokenized inputs.

---
### 1.2. Workflow
![flow_chart](https://github.com/choH/cs120_final_project/media/flow_chart)

The workflow logic is simple. `main.c` reads the input commands from the `input.txt` in a line by line manner and calling their *input functions* in `Base.h #1 (input functions)` accordingly. Thus `Base.h #1 (input functions)` shall therefore store data into `Base.h #3 (private data members)` in a organized form.

Once the *output functions* are called in `main.c`, `Base.h #2 (output function)` will be triggered, it shall retrieve data from `Base.h #3 (private data members)`, process these data with functions from `Time.h`, and therefore produce the output.

---
## 2. Sample Input/Output

### 2.1. Given Sample Input

```
>> Program Input
login Bev
order 18:00 1 mushroom to 123 Holden Hall
order 18:02 4 spinach to 100 Liberty St
login Abe
serve 18:20
depart 18:20 Abe
serve 18:28
deliver 18:30 Abe 2.00
order 18:30 1 cheese 1 sausage to 1000 Beall Ave
depart 18:31 Bev
arrive 18:40 Abe
logout Abe
status
summary
quit
```

```
>> Program Output
Orders waiting to cook: 
    18:30 1 cheese 1 sausage to 1000 Beall Ave 
Orders waiting to depart: 
Drivers: 
    Bev 18:02 4 spinach to 100 Liberty St 
Number of orders completed: 1 
Average time per delivery: 30.0 
Driver Bev: 
    Number of deliveries completed: 0 
    Average time per delivery: N/A 
    Total driving time: 0 
    Total tips: 0.00 
Driver Abe: 
    Number of deliveries completed: 1 
    Average time per delivery: 10.0 
    Total driving time: 20 
    Total tips: 2.00 

Program ended with exit code: 0 
```

### 2.2. Self-designed Input

```
>> Program Input
login Mike
order 18:15 10 Pepperoni pizzas, 10 hotdogs, 10 Fanta orange drinks, 10 mozzarella cheese sticks to 11 Babcock Hall
login Alex
order 18:30 15 cheese sticks to Taylor 200
serve 19:00
depart 19:00 Mike
serve 19:10
deliver 19:30 Mike 10.00
depart 19:50 Alex
deliver 20:00 Alex 0.50
arrive 20:10 Mike
login Jen
order 20:35 1 milkshake, 1 small cheesecake, 1 strawberry parfait to Taylor 200
logout Mike
serve 20:45
arrive 20:55 Alex
logout Alex
status
summary
quit
```

```
>> Program Output
Orders waiting to cook: 
Orders waiting to depart: 
    20:35 1 milkshake, 1 small cheesecake, 1 strawberry parfait to Taylor 200 
Drivers: 
    
Number of orders completed: 2 
Average time per delivery: 82.5 
Driver Mike: 
    Number of deliveries completed: 1 
    Average time per delivery: 30.0 
    Total driving time: 70 
    Total tips: 10.00 
Driver Alex: 
    Number of deliveries completed: 1 
    Average time per delivery: 10.0 
    Total driving time: 65 
    Total tips: 0.50 
Driver Jen: 
    Number of deliveries completed: 0 
    Average time per delivery: N/A 
    Total driving time: 0 Total tips: 0.00 
    
Program ended with exit code: 0 
```
---
## 3. Work Distribution & Reflection

███ Edited & omitted due to privacy concerns ███

I've written `Base.h`, `Time.h`, and `main.cpp` files.
My teammate has designed and verified two sample inputs demonstrated in **Section 2.1 & 2.2**. We also designed and discussed the framework (use of data structure and etc.) together.


███ Edited & omitted due to privacy concerns ███

We used `Bitbucket` and `slack` for collaboration, and we have met on 11.28, 12.5, and 12.6 for discussion.

---
## 4. Documentation
### 4.1. Base.h

Since the `parameter`s are all quite self-explanatory in the following functions, this documentation section will omit the introduction of `parameter`s.

* **Base()**
    * Constructor
    * Result: set `c_order_id` and `c_driver_id` to `0`.

* **void add_order (const string i_order_info, const string i_order_time);**
    * Triggered by `order` command.
    * Result: (In this order's `vector` node)
        * pushed `map`s with `key` of `order_info`, `order_time`, `is_serve`, `serve_time`, `is_dept`, `dept_time`, `driver_name`, `is_delv`, `delv_time`, `driver_tip`, `is_arrive`, and `arrive_time` to `order_rec`.
        * set key `order_info` to value `i_order_info`.
        * set key `order_time` to value `order_time`.
        * set rest of the keys to value `"NO"` or `"UNKNOWN"`. 
* **void serve_order (const string i_serve_time) throw (logic_error);**
    * Triggered by `serve` command.
    * Requirement: There is a placed but not-yet-cooked order.
    * Result: (In this order's `vector` node)
        * set key `is_serve` to value `"YES"`;
        * set key `serve_time` to value `i_serve_time`;
    
* **void dept_driver (const string i_driver_name, const string i_dept_time) throw (logic_error)**
    * Triggered by `depart` command.
    * Requirement: 
        * There is a served but not-yet-departed order.
        * The assigned `i_driver_name` is available.
    * Result: (In this order's `vector` node)
        * set key `is_dept` to value `"YES"`.
        * set key `dept_time` to value `i_dept_time`.
        * set key `driver_name` to value `i_driver_name`.

* **void delv_driver (const string i_driver_name, const string i_delv_time, const string i_driver_tip) throw (logic_error)**
    * Triggered by `delivery` command.
    * Requirement:
        * There is a departed but not-yet-delivered order.
        * The assigned `i_driver_name` is matched with the departed driver.
    * Result: (In this order's `vector` node)
        * set key `is_delv` to value `"YES"`.
        * set key `delv_time` to value `i_delv_time`.
        * set key `driver_tip` to value `i_driver_tip`.

* **void arrive_driver (const string i_driver_name, const string i_arrive_time) throw (logic_error)**
    * Triggered by `arrive` command.
    * Requirement: 
        * There is a delivered but not-yet-arrived driver.
        * The assigned `i_driver_name` is matched with the delivered driver.
    * Result: (In this order's `vector` node)
        * set key `is_arrive` to `"YES"`.
        * set key `arrive_time` to `i_arrive_time`.

* **void login_driver (const string i_driver_name)**
    * Triggered by `login` command.
    * Requirement: driver name has no white-spaces.
    * Result: (In this driver's `vector` node)
        * pushed `map`s with key of `driver_name`, `is_login`, `is_dept`, `total_delv_count`, `total_delv_time`, `total_drive_time`, and `total_tip` to `driver_rec`.
        * set key `driver_name` to value `driver_id`, which is obtained from `c_driver_id`.
        * set key `is_login` to value `1`.
        * set all other keys to value `0`.

* **void logout_driver (const string i_driver_name) throw (logic_error)**
    * Triggered by `logout` command.
    * Requirement: `i_driver_name` must be available.
    * Result: (In this driver's `vector` node)
        * set key `is_login` to value `0`.

* **float get_driver_id (const string i_driver_name) throw (logic_error)**
    * Requirement: `i_driver_name` exists in `driver_sys`.
    * Result: return `i_drive_name`'s `driver_id` by checking `driver_sys`.

* **string get_driver_name (const float i_driver_id) throw (logic_error);**
    * Requirement: `i_driver_id` is bigger than `0` while less than `driver_sys.size()`;
    * Result: return `driver_id`'s `i_drive_name` by checking `driver_sys`.

* **get_order_id (const string i_order_info) throw (logic_error);**
    * Requirement: `i_order_info` exists in `order_sys`.
    * Result: return `i_order_info`'s `order_id` by checking `order_sys`.

* **bool is_driver_avbl (const string i_driver_name) throw (logic_error);**
    * Requirement: `i_driver_name` exists in `driver_sys`.
    * Result: 
        * true: `i_driver_name` is logged-in but not departed.
        * false: otherwise.

---
### 4.2. Time.h
* **Time();**
    * Constructor. 
* **float time_to_min (const Time time);**
    * Parameters: 
        * `time`: time to be convert.
    * Result: return a valid `Time time` from hour-min format to minutes.
* **Time elapsed_time (const Time start, const Time end);**
    * Requirement: `Time end` is later than `Time start`.
    * Parameters: 
        * `start`: start time.
        * `end`: end time.
    * Result: return the passed duration from `Time start` to `Time end`.
* **bool is_time (const int i_hour, const int i_min);**
    * Parameters:
        * `i_hour`: input time's hour value for checking.
        * `i_min`: input time's min value for checking.
    * Result: 
        * true: `0 <= i_hour <= 23` and `0 <= i_min <= 59`.
        * false: otherwise.
* **bool is_same_or_later (const Time time_1, const Time time_2);**
    * Parameters:
        * `time_1` and `time_2`: times to check.
    * Result:
        * true: `time_2` is same or later than `time_1`.
        * false: otherwise.
* **bool is_legal_input (const string last_time_str, const string current_time_str);**
    * Parameters:
        * `last_time_str`, `current_time_str`: times to check, in `string` format.
    * Result:
        * true: if `current_time_str` is later than `last_time_str` whereas both of them are legit time (`is_time() == true`).
        * false: otherwise.

---
### 4.3. main.c

Please refer to the actual `main.c` file, in-line comments/documentations is provided.

It might be worthy to mention that code in `main.c` shall keep track of the two latest time-related inputs (`order_time`, `serve_time`, and etc.), and it shall return and exit the program if the current input is invalid (earlier than pervious input, or not in a correct `Hour:Min` time format);