/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    //TODO: Implement non-default constructor
    stringstream ss(commandString);
        char input;
        if (commandString != "") {
            ss >> input;
            if (input == 's' || input == 'S') {
                isSave = true;
            }
            else if (input == 'q' || input == 'Q') {
                isQuit = true;
            }
            else if (input == 'e') {
                ss >> elevatorId;
                ss >> input;
                if (input == 'p') {
                    isPickup = true;
                }
                else {
                    ss >> targetFloor;
                }
            }
        }
        else {
            isPass = true;
        }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    //TODO: Implement isValidMove
    //Check for pass, quit, or save.
    if (isSave == true || isPass == true || isQuit == true) {
        return true;
    }
    //Check for pickup moves
    else if (isPickup == true && (0 <= elevatorId && elevatorId < NUM_ELEVATORS) && !elevators[elevatorId].isServicing()) {
        return true;
    }
    //Check for servicing moves
    else if ((0 <= targetFloor && targetFloor < NUM_FLOORS) && targetFloor != elevators[elevatorId].getCurrentFloor() && !elevators[elevatorId].isServicing()
        && (0 <= elevatorId && elevatorId < NUM_ELEVATORS) && isPickup == false) {
        return true;
    }
    else {
        return false;
    }
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    //TODO: Implement setPeopleToPickup
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    //num of people list, iterate and find max/min target floor
    int targetFloor = 0;
    for (int i = 0; i < pickupList.length(); i++) {
        peopleToPickup[numPeopleToPickup++] = pickupList.at(i) - '0';
        Person target = pickupFloor.getPersonByIndex(peopleToPickup[i]);
        totalSatisfaction += MAX_ANGER - target.getAngerLevel();
        
        if (abs(target.getTargetFloor() - currentFloor) > targetFloor) {
            targetFloor = abs(currentFloor - target.getTargetFloor());
            setTargetFloor(target.getTargetFloor());
        }
    }
    
    
    
    
    
    
    /*stringstream ss(pickupList);
    char input;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int diff = 0;
    for (int i = 0; i < pickupList.length(); i++) {
        ss >> input;
        peopleToPickup[i] = input - '0';
        numPeopleToPickup++;
        totalSatisfaction += MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        if (diff <= abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor())) {
            diff = abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor);
            targetFloor = getTargetFloor();
        }
    }
    //targetFloor = currentFloor + diff;*/
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
