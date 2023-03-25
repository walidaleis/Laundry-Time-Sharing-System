#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include "Resident.hpp"

using namespace std;

//general Machine class for functions and variables common to both washer and dryer
class Machine {
protected:
    int ID;
    bool isAvailable;
    int timeRemaining;
    int duration;
    string mode;
    time_t startTime;
    static double price; //static as one price for all machines
    friend class Operator; //must declare Operator as friend class so it can access member variables and functions
    
public:
    //default constructor randomly assigns ID between 0 and 99
    Machine() { ID = rand() % 99; }
    
    //non-default constructor
    Machine(int ID) {
        this->ID = ID;
    }
    
    //mutator functions
    void setID(int ID) {
        this->ID = ID;
    }
    
    void setPrice(double price) { this->price = price; }
    
    void setDuration() {
        cout << "How long would you like the machine to run?\n"; //prompt the user with options
        cout << "Press 1 for 10 seconds.\n"
            << "Press 2 for 30 seconds.\n"
            << "Press 3 for 1 minute.\n"
            << "Press 4 for 5 minutes.\n"
            << "Press 5 for 10 minutes.\n"
            << "Press 6 for 30 minutes.\n"
            << "Press 7 for 1 hour.\n"
            << "Press 8 for 2 hours.\n";
        char c;
        cin >> c;
        switch(c) {
            case '1' : { 
                duration = 10; 
                break;
            }
            case '2' : {
                duration = 30;
                break;
            }
            case '3' : {
                duration = 60;
                break;
            }
            case '4' : {
                duration = 5 * 60;
                break;
            }
            case '5' : {
                duration = 10 * 60;
                break;
            }
            case '6' : {
                duration = 30 * 60;
                break;
            }
            case '7' : {
                duration = 60 * 60;
                break;
            }
            case '8' : {
                duration = 2 * 60 * 60;
                break;
            }
            default : {
                cout << "Please enter a valid input. Your options are shown again below.\n";
                setDuration();
            }
        }
    }


    void setIsAvailable(bool isAvailable) { this->isAvailable = isAvailable; }

    //accessor methods for member variables
    int getID() { return ID; }
    
    double getPrice() { return price; }
    
    int getDuration() { return duration; }

    string getMode() { return mode; }

    bool getIsAvailable() {return isAvailable; }
    
    //print function for info about machine
    void printInfo() {
        cout << "ID: " << ID << endl;
        cout << "Current mode: " << mode << endl;
        cout << "Available: ";
        isAvailable ? (cout << "Yes\n") : (cout << "No\n");
    }

    //function to start a cycle given info
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

    //compare Resident balance to price of machine cycle
    bool checkFunds(Resident r) {
        if (r.getBalance()<price) {
            return false;
        }
        return true;
    }

};

double Machine::price = 0; //must be initiated outside class

#endif
