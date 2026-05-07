/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

/*
 * Requires: inputString is correctly formatted
 * Modifies: turn, currentFloor, targetFloor, angerLevel
 * Effects:  Parses input_string to set member variables
 *           An example of input_string is "7f4t8a3".
*/

Person::Person(string inputString) : Person() {
    //TODO: Implement non-default constructor
    stringstream inString(inputString);
    char f;
    char t;
    char a;
    inString >> turn;
    inString >> f;
    inString >> currentFloor;
    inString >> t;
    inString >> targetFloor;
    inString >> a;
    inString >> angerLevel;
}

/**
 * Requires: nothing
 * Modifies: angerLevel
 * Effects:  Every TICKS_PER_ANGER_INCREASE, this function increases the
 *           person's anger level by 1. If, after increasing, the person
 *           has an anger level of MAX_ANGER, the function will return
 *           true. If the person has an anger level less than MAX_ANGER,
 *           the function will return false.
 */

bool Person::tick(int currentTime) {
    //TODO: Implement tick
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
    }
    if (angerLevel == MAX_ANGER) {
        return true;
        
    }
    else {
        return false;
    }
    
    //Returning false to prevent compilation error
    return false;
}

/**
 * Requires: nothing
 * Modifies: outs
 * Effects:  Prints the infoString of the person NOT including the turn
 *
 * Example:  Person p("7f4t8a3");
 *           cout << "\nThe person you just entered is: ";
 *           p.print(cout);
 *
 *           This will print "f4t8a3"
 */

void Person::print(ostream &outs) {    
    //TODO: Implement print
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;

}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
