#include "Operator.hpp"
#include "Machine.hpp"
#include "Washer.hpp"
#include "Dryer.hpp"
#include "Resident.hpp"

//forward function declarations
//all assume operator object already exists
void printOperatorMenu(Operator &o1);

void printResidentMenu(Resident &r, Operator &o);

void mainMenuUserInput(Operator &o1);

//main menu display function
inline void printMainMenu(Operator &o1) {
    cout << "Welcome to LaundryMate, here to make your life easier!\n"
        << "To get started, please choose what you are using the platform for.\n"
        << "For the operator menu, please press 1. \n"
    << "For the resident menu, press 2.\n"
    << "To exit the program, press 3.\n";
    mainMenuUserInput(o1); //separate function to avoid repeating the initial message
}

//main menu user input function
void mainMenuUserInput(Operator &o1) {
    char c;
    cin >> c;
    switch(c) {
        case '1' : {
            printOperatorMenu(o1); //options specific for operator
            break;
            }
        case '2' : {
            Resident r1; //create object for resident
            
            cout << "Please start by creating a username below.\n";
            string username;
            cin >> username;
            r1.setUsername(username);
            printResidentMenu(r1,o1); // options specific for resident

            break;
            }
        case '3' : {
            cout << "Thank you for using our services. Have a nice day!\n"; //terminates program
            return;
        }
        default : {
            cout << "Invalid input! Please try again.\n";
            mainMenuUserInput(o1); //recursively call function to ensure valid input
            }
    }
}

//pass by reference to edit object
void printOperatorMenu(Operator& o1) {

    //print options for operator
    cout << "What would you like to do?\n"
        << "To register a washing machine, press 1.\n"
        << "To register a dryer, press 2.\n"
        << "To set the price of a wash cycle, press 3.\n"
        << "To set the price of a dryer cycle, press 4.\n"
    << "To exit and return to main menu, press 5.\n";
    char c;
    cin >> c;
    switch(c) {
            //registering a washing machine
        case '1' : {
            Washer w1; //create new washer object
            o1.addWasher(w1); //add to vector of washers
            cout << "Successfully added washing machine with ID " << w1.getID() << endl; //show ID
                                                                            //using getter function of Washer class
            
            printOperatorMenu(o1); //return to menu for operator to do something else
            break;
        }
            
            //registering a dryer
        case '2' :  {
            Dryer d1; //create new dryer object
            o1.addDryer(d1); //add to vector of dryers
            cout << "Successfully added drying machine with ID " << d1.getID() << endl; //display ID
                                                                        //using getter function of Dryer class
            
            printOperatorMenu(o1); //return to menu
            break;
        }
            
            //setting price of wash cycle
        case '3' : {
            Washer wTemp; //create temp object of Washer class to assign a value to static variable price
            cout << "Please enter the price you would like to set (as a number).\n";
            
            double price;
            cin >> price; //take input from user
            wTemp.setPrice(price); //assign to price with mutator function of Washer class
            
            cout << "Succesfully set wash cycle price at $"; //confirm price
            printf("%.2f",price); //rounding to two decimal places
            cout << "\n";
            
            printOperatorMenu(o1); //return to menu
            break;
        }
            
            //setting price of dryer cycle
        case '4' : {
            Dryer dTemp; //temp object of Dryer class to assign value to static member variable price
            cout << "Please enter the price you would like to set (as a number).\n";
            double price;
            cin >> price; //same process followed above
            dTemp.setPrice(price);
            cout << "Succesfully set dryer cycle price at $";
            printf("%.2f",price);
            cout << "\n";
            printOperatorMenu(o1);
            break;
        }
            
            //return to main menu
        case '5' : {
            cout << "Returning to main menu...\n";
            printMainMenu(o1); //call main menu function to allow operator to take over or to exit program
            break;
        }
        default : {
            cout << "Please enter a valid input.\n";
            printOperatorMenu(o1); //recursion to ensure valid input
        }
        
        
    }
}

//menu for resident
//takes Resident and Operator objects as arguments by reference as these will need to be modified
void printResidentMenu(Resident &r1, Operator &o1) {
    //prompt user with options
    cout << "What would you like to do now?\n"
        << "To check your balance, press 1.\n"
        << "To add to your balance, press 2.\n"
        << "To start a wash cycle, press 3.\n"
        << "To start a dryer cycle, press 4.\n"
    << "To return to the main menu, press 5.\n";
    
    char c;
    cin >> c;
    
    switch(c) {
            //checking current balance
        case '1' : {
            cout << "Your current balance is: $";
            printf("%.2f",r1.getBalance()); //display resident's current balance rounded to two decimal places
                                            //using getter function of Resident class
            
            cout << "\n";
            
            printResidentMenu(r1,o1); //return to main resident menu to show other options
            break;
        }
            
            //adding to balance
        case '2' : {
            cout << "Please enter the amount you would like to add to your balance.\n";
            double amount;
            cin >> amount;
            r1.topUp(amount); //add amount using member function of Resident class
            
            cout << "Successfully added to your balance.\n";
            cout << "Your current balance is now ";
            printf("%.2f",r1.getBalance()); //display balance rounded to two decimal places
                                            // getter function from Resident class
            
            cout << "\n";
            
            printResidentMenu(r1,o1); //returning to menu
            break;
        }
            
            //starting wash cycle
        case '3' : {
            if (o1.washersAreAvailable()==false) { //check if washers available using Operator member function
                cout << "No washers are currently available.\n";
            }
            
            else {
                Washer w;
                cout << "A washer is available.\n"; //inform user if a washer is available
                
                if (w.checkFunds(r1)) { //first check if resident has sufficient funds
                    w.setMode();        //set washer mode mutator function
                    w.setDuration();    //set washer duration mutator function
                    w.startCycle();     //start washer cycle
                }
                
                else {
                    cout << "Insufficient funds!\n Returning to menu...\n"; //inform user if insufficient funds
                }
            }
            printResidentMenu(r1,o1); //return to menu
            break;
        }
            
            //starting dryer cycle - same process followed above
        case '4' : {
            if (o1.dryersAreAvailable()==false) {
                cout << "No dryers are currently available.\n";
            }
            else {
                Dryer d;
                cout << "A dryer is available.\n";
                if (d.checkFunds(r1)) {
                    d.setMode();
                    d.setDuration();
                    d.startCycle();
                    cout << d.getIsAvailable();
                }
                else {
                    cout << "Insufficient funds!\n Returning to menu...\n";
                }
            }
            printResidentMenu(r1,o1);
            break;
        }
            
            //returning to main menu
        case '5' : {
            printMainMenu(o1);
            break;
        }
        default : {
            cout << "Please enter a valid input. \n";
            printResidentMenu(r1, o1);
            break;
        }
            
    }
}


int main(int argc, const char * argv[]) {
    
//default operator needed to start program
    Operator o1;
    
    //initiate program with o1 as input to main menufunction
    printMainMenu(o1);
    
    return 0;
}
