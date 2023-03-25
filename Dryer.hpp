

#ifndef DRYER_HPP
#define DRYER_HPP

#include "Machine.hpp"

//Dryer class inherits from Machine
class Dryer : public Machine {
public:
    Dryer() : Machine() {}; //default constructor inherits from machine
    
    Dryer(int ID) : Machine(ID) {}; //non-default constructor inherits from machine
    
    //custom mutator function to set mode
    void setMode() {
        cout << "Please enter what mode you would like the machine to run.\n Press n for normal, d for delicate, or h for heavy duty.\n";
        char Mode;
        cin >> Mode;
         switch(Mode) {
             case 'n' : case 'N' :{
                 mode = "Normal";
                 break;
             }
             case 'd' : case 'D' :{
                 mode = "Delicate";
                 break;
             }
             case 'h' : case 'H' :{
                 mode = "Heavy duty";
                 break;
             }
             default: {
                 cout << "Please enter a valid input!\n Your options are shown again below.\n";
                 setMode();
             }
             }
        cout << "You have selected: " << mode << endl;
    }
};


#endif
