#ifndef WASHER_H
#define WASHER_H

#include "Machine.hpp"

//Washer class inherits from Machine
class Washer : public Machine {
public:
    Washer () : Machine() {}; //inherit default constructor
    
    Washer(int ID) : Machine(ID) {}; //inherit non-default constructor
    
    //add a mutator function custom for Washer
    void setMode() {
        cout << "Please enter what mode you would like the machine to run.\n Press m for mix, c for cottons, s for synthetics, d for delicates, or w for whites.\n";
        char Mode;
        cin >> Mode;
        
         switch(Mode) {
             case 'm' : case 'M' :{
                 mode = "Mix";
                 break;
             }
             case 'c' : case 'C' :{
                 mode = "Cottons";
                 break;
             }
             case 's' : case 'S' :{
                 mode = "Synthetics";
                 break;
             }
             case 'd' : case 'D' : {
                 mode = "Delicates";
                 break;
             }
             case 'w' : case 'W' : {
                 mode = "Whites";
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
