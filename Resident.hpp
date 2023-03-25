



#ifndef RESIDENT_H
#define RESIDENT_H

#include <iostream>
#include <string>

using namespace std;

//Resident class
class Resident {
private:
    string username;
    double balance;
public:
    Resident() {}; //default constructor
    
    Resident(string username) {this->username = username; } //non-default constructor

    //mutator methods
    void setUsername(string username) { this->username = username; }

    void setBalance(double balance) { this->balance = balance; }

    //accessor methods
    string getUsername() { return username; }

    double getBalance() { return balance; }
    
    //add amount to balance
    void topUp(double amount) { balance += amount; }
};


#endif
