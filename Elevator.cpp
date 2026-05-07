/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Elevator.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Elevator.h"
#include <iostream>

using namespace std;

/**
* Requires: currentTime is valid
* Modifies: currentFloor, servicing
* Effects:  Moves the value of current floor by 1 in the direction of the target
*           floor if the currentTime is divisible by TICKS_PER_ELEVATOR_MOVE and
*           the elevator is servicing a request.
*           If the new current floor is the target floor, servicing is set to false
*/

void Elevator::tick(int currentTime) {
    //TODO: Implement tick
    int newCurrentFloor = 0;
    if ((currentTime % TICKS_PER_ELEVATOR_MOVE == 0) && (servicing == true)) {
        if (targetFloor > currentFloor) {
            currentFloor++;
            newCurrentFloor = currentFloor;
        }
        else if (targetFloor < currentFloor) {
            currentFloor--;
            newCurrentFloor = currentFloor;
        }
    }
    if (newCurrentFloor == targetFloor) {
        servicing = false;
    }
}

/**
 * Requires: 0 <= floorNum <= NUM_FLOORS
 * Modifies: targetFloor, servicing
 * Effects:  Sets the targetFloor and marks the Elevator as
 *           currently servicing
 */

void Elevator::serviceRequest(int floorNum) {
    //TODO: Implement serviceRequest
    if (floorNum >= 0 && floorNum <= NUM_FLOORS) {
        targetFloor = floorNum;
        servicing = true;
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
