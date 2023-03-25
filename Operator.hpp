//
//  Operator.hpp
//  Laundry Time-Sharing System
//
//  Created by Walid Al-Eisawi on 02/03/2023.
//

#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include "Washer.hpp"
#include "Dryer.hpp"

using namespace std;

//Operator class
class Operator {
private:
    vector<Washer> washers; //vector of objects from Washer class
    vector<Dryer> dryers;   //vector of objects from Dryer class
    int num_of_washers = 0; //count of number of washing machines
    int num_of_dryers = 0;  //count of number of dryers

public:
    Operator() {}; //default constructor does nothing
    
    //take existing Washer object and add to vector of Washers
    void addWasher(Washer w1) {
        washers.push_back(w1);
        num_of_washers++; //must increment washer count
    }
    
    //take existing Dryer object and add to vector
    void addDryer(Dryer d1) {
        dryers.push_back(d1);
        num_of_dryers++; //must increment Dryer count
    }
    
    //check if any washers are available by iterating through vector
    bool washersAreAvailable() {
        vector<Washer>::iterator v = washers.begin(); //initiate pointer at beginning of vector
        
        while (v != washers.end()) {
            if ((*v).isAvailable)
                return true; //return true at the first washer available
            v++;
        }
        
        return false; //otherwise return false
    }
    
    //check if any dryers are available by iterating through vector, same as above
    bool dryersAreAvailable() {
        vector<Dryer>::iterator v = dryers.begin();
        
        while (v != dryers.end()) {
            if ((*v).isAvailable)
                return true;
            v++;
        }
        
        return false;
    }
    
    //function to retrieve ID of available washer
    int getWashersAvailable() {
        vector<Washer>::iterator v = washers.begin();
        
        while (v != washers.end()) {
            if ((*v).isAvailable)
                return (*v).ID; //returns ID of first available washer
            v++;
        }
        
        return 0;
    }
    
    //function to retrieve ID of first available dryer
    int getDryersAvailable() {
        vector<Dryer>::iterator v = dryers.begin();
        
        while (v != dryers.end()) {
            if ((*v).isAvailable)
                return (*v).ID; //returns ID of first available dryer
            v++;
        }
        
        return 0;
    }

};


#endif
