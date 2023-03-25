# Laundry-Time-Sharing-System
## Introduction:
Laundry in shared accommodation buildings, such as the residential halls on campus, can often be a struggle. Personally, I have experienced first-hand the pain of going down to do laundry, realizing all the washing machines are in use, and coming back several times after that only to be faced with the same problem each time. This is why the idea of a laundry time-sharing system piqued my interest. In Europe and North America, the concept is not foreign at all; many shared laundry rooms utilize a system like this to simplify matters for tenants. Generally, systems like this are not only an easy way to keep track of what machines are in use at a given time, but also provide a mechanism by which payment can easily be regulated in areas where access to laundry machines is paid. Some examples include [AppWash](https://appwash.com/en/), [Tumble.to](https://appwash.com/en/), and Bosch’s [WeWash](https://www.bosch.com/stories/wewash/), which I relied on as inspiration for my program. They usually involve separate interfaces to moderate the laundry room operator’s experience (i.e., the landlord) and that of the residents, which is one aspect I decided to maintain in my version of a laundry time-sharing system.

This project was created as a term project for the Object-Oriented Programming course at NYU Abu Dhabi. The language used was C++.

## Approach:
Initially, I wanted my system to function as realistically as possible, studying what functions other applications and carefully thinking about how I could replicate them in software, without being attached to actual laundry machines, of course. I started by thinking about how I would separate functions into classes: I would need a general Machine class with functions that are common to both washers and dryers, as well as a separate Washer class and Dryer class that share some of the functions presented in Machine, but also have their own machine-specific functions and variables. For example, setting the mode for a washer would be different from setting the mode for a dryer. Additionally, I decided I should incorporate separate functionality to accommodate users as both residents and operators, since this made more sense to me than abstractly generating a laundry room with an ambiguous number of washing machines and dryers and a randomly set price. Hence, I needed to have a Resident class and an Operator class, each with specific variables and functions that would be used to customize the experience of the user. The operator, specifically, would keep track of the laundry room and all its machines, both washers and dryers. The Resident, on the other hand, would be able to do what anyone would expect from a laundry app, such as creating a profile, adding to their balance, starting a cycle on either kind of machine, and being informed once their cycle was complete.

## Solution:
To begin to visualize this, the following diagram displays the overall structure of my project:

![UML Diagram](images/Project%20UML%20diagram.jpg)

As explained above, these five classes were the way I decided to divide information. Of course, this is the fundamental principle underlying OOP logic, and it was crucial for my project. Washer and Dryer classes inherited from Machine, as many variables and functions were common. Machine stored the general information about the machine in variables, such as an int ID to make the machine notable, a bool isAvailable that can be used to deduce whether the machine is running or can be used, an int duration containing initial length of time the cycle will run for, among several other variables. Additionally, the Machine class contained several functions, including but not limited to accessor and mutator methods, that would be useful for both the Operator class and the Resident class.

To further illustrate the intersectionality between classes, one of the functions I used in Machine was a checkFunds() function that compares the Resident’s funds to the price of a cycle. This can be seen below:
```c++
bool checkFunds(Resident r) {
        if (r.getBalance()<price) {
            return false;
        }
        return true;
    }
```
Obviously, this is an example of inheritance, one of the other OOP concepts I implemented in my project.

Another important OOP concept I relied on was friendship. I had to declare Operator as a friend class of Machine, in order for Machine, Washer, and Dryer to access the private functions of Operator. This was important because of the clear overlap between the classes. For example, I implemented a washersAreAvailable() function in the Operator class to check whether any washers are available. This function iterates through a vector of Washer objects stored in the Operator class, checking each item on whether or not it fulfills the condition of being available. Naturally, this would need to access the isAvailable bool from the Washer class (inherited from Machine). The implementation can be seen below:
```c++
bool washersAreAvailable() {
        vector<Washer>::iterator v = washers.begin(); //initiate pointer at beginning of vector
        
        while (v != washers.end()) {
            if ((*v).isAvailable)
                return true; //return true at the first washer available
            v++;
        }
        
        return false; //otherwise return false
    }
```

To go into another crucial function of the Machine class, we can take a look at the startCycle() function. When I first began thinking about the possible implementation, my first concern was how I could initiate a timer to monitor the duration of a machine cycle without halting the entire program. At face value, it seemed trivial, yet impossible at the same time—surely there must be a way to run tasks in the background, like timers, without completely putting it to a stop. As I did some research into this, it seemed like multithreading was the only way. I really tried learning it on my own, using links like [this](https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm) and even implemented some of it, shown below, before deciding to abandon it:
```c++
void timer_thread_w(Washer *w) {
    this_thread::sleep_for(chrono::seconds(w->getDuration()));
    // cout << "Done\n";
    w->setIsRunning(false);
}
void startWasherCycle(Washer *w) {

        double minutes = w->getDuration();
        minutes = minutes/60;
        cout << "Cycle started on " << w->getMode() << " mode with ";
        printf("%.2f",minutes);
        cout << " minutes remaining.\n";
        thread t1(timer_thread_w,w);
        t1.join();

        w->setIsRunning(true);
        w->setIsAvailable(false);

    }
```
What you see here is the result of many hours of messing around with the code, trying to get it to work. I passed the function arguments normally first, before trying it by reference, and then finally passing by pointer, but to no avail. I was getting somewhere, though: the code worked, technically. It just didn’t do what I wanted it to. Specifically, it wouldn’t properly label the Washer as unavailable, so my suspicion is that the use of vectors somehow clashed with threading, or I went wrong somewhere I couldn’t figure out. Regardless, I was unfortunately forced to abandon this approach due to the time crunch. What I settled on ultimately was a rather rudimentary system instead, where the user has to wait for the machine cycle to be completed before they can do anything else. This was why I gave the option for unrealistically short cycle times in the setDuration() function, such as 10 seconds. The startCycle() function can be seen below for more detail:
```c++
    void startCycle() {
        
        double minutes = duration; //cast duration as double to convert to minutes
        minutes = minutes/60;
        
        isAvailable = false; //set isAvailable to false as machine is initiated
        startTime = time(nullptr); //store current time
        
        //display message to user
        cout << "Cycle started on " << mode << " mode with ";
        printf("%.2f",minutes);
        cout << " minutes remaining.\n";
        
        //use ctime library to begin timer
        duration *= CLOCKS_PER_SEC;
        clock_t now = clock();
        cout << "Machine in progress...\n";
        while(clock() - now<duration); //waits for duration
        
        cout << "Cycle is complete! Please retrieve your clothes.\n"; //display message to user once complete
        isAvailable = true; //set isAvailable to true again
    }
```
One can see above that I implemented a clock variable using the ctime standard library (adapted from [here](https://en.cppreference.com/w/c/chrono/time_t)) in order to keep track of the time that has passed since the cycle was started. In other words, I simply set a timer that ran until the time elapsed was equal to the duration, specified by the user, after which a completion message is printed. 

In regard to optimization concepts, I implemented an inline function in my main.cpp file to optimize performance at runtime. Specifically, the function was one that printed the main menu, which, of course, is called multiple time in the main() and thus must be executed efficiently. The code can be seen below:
```c++
inline void printMainMenu(Operator &o1) {
    cout << "Welcome to LaundryMate, here to make your life easier!\n"
        << "To get started, please choose what you are using the platform for.\n"
        << "For the operator menu, please press 1. \n"
    << "For the resident menu, press 2.\n"
    << "To exit the program, press 3.\n";
    mainMenuUserInput(o1); //separate function to avoid repeating the initial message
}
```
I would have implemented even more functions as inline, but many were recursive such as some of the other menu functions, which prevented me from declaring them as inline.

Another optimization concept I utilized was passing by reference. This was also very important for the functions called in main(), such as the printMainMenu() function seen above. In that case, it enabled the function to modify the Operator object passed to it, which was needed for the mainMenuUserInput function, some of which can be seen below:
```c++
void mainMenuUserInput(Operator &o1) {
    char c;
    cin >> c;
    switch(c) {
        case '1' : {
            printOperatorMenu(o1); //options specific for operator
            break;
            }
            }
}
```
Furthermore, I made use of pointers as an optimization for speed, such as in the case of using vectors--which is arguably another optimization in and of itself. To iterate through the vector, I had to use a pointer iterator, which was seen in the washersAreAvailable() function earlier. The vector itself optimizes the performance of the program as it relies on dynamic memory allocation, which can be argued to be more efficient than using an array that is continuously resized through copying to a new array.
### Output

```console
Welcome to LaundryMate, here to make your life easier!
To get started, please choose what you are using the platform for.
For the operator menu, please press 1. 
For the resident menu, press 2.
To exit the program, press 3.
1
What would you like to do?
To register a washing machine, press 1.
To register a dryer, press 2.
To set the price of a wash cycle, press 3.
To set the price of a dryer cycle, press 4.
To exit and return to main menu, press 5.
1
Successfully added washing machine with ID 76
What would you like to do?
To register a washing machine, press 1.
To register a dryer, press 2.
To set the price of a wash cycle, press 3.
To set the price of a dryer cycle, press 4.
To exit and return to main menu, press 5.
1
Successfully added washing machine with ID 34
What would you like to do?
To register a washing machine, press 1.
To register a dryer, press 2.
To set the price of a wash cycle, press 3.
To set the price of a dryer cycle, press 4.
To exit and return to main menu, press 5.
5
Returning to main menu...
Welcome to LaundryMate, here to make your life easier!
To get started, please choose what you are using the platform for.
For the operator menu, please press 1. 
For the resident menu, press 2.
To exit the program, press 3.
3
Thank you for using our services. Have a nice day!

```

### Bibliography
[Tumble.to](tumble.to) <br/>
[Appwash](https://appwash.com/en/) <br/>
[WeWash](https://www.bosch.com/stories/wewash/) <br/>
[CPP Reference](https://en.cppreference.com/w/c/chrono/time_t) <br/>
