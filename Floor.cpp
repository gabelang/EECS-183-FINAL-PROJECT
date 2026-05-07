/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

/*
 * Requires: nothing
 * Modifies: people
 * Effects:  Ticks each person on this floor
 *           Also removes any Person who explodes
 *           Returns the number of exploded people
 */

int Floor::tick(int currentTime) {
    //TODO: Implement tick
    //Person p;
    int explodedPeeps = 0;
    int countTemp = 0;
    int arr1[MAX_PEOPLE_PER_FLOOR] = {};
    //int exploded = 0;
    for (int i = 0; i < numPeople; i++)
       // bool doesExplode = people[i].tick(currentTime);
        //bool doesExplode = true;
        //doesExplode = true;
        
        if (people[i].tick(currentTime) == true) {
            //people = numPeople - people[i];
            explodedPeeps++;
            arr1[countTemp] = i;
            countTemp++;
        }
    removePeople(arr1, explodedPeeps);
    /* if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
    }
    if (angerLevel == MAX_ANGER) {
        return true;
        
    }
    else {
        return false;
    }*/
    //returning 0 to prevent compilation error
    return explodedPeeps;
}

/*
 * Requires: request != 0
 * Modifies: hasUpRequest, hasDownRequest, numPeople, people
 * Effects:  If there is still room, add newPerson to people.
 *           Updates hasUpRequest or hasDownRequest based on value of request
 */

void Floor::addPerson(Person newPerson, int request) {
    //TODO: Implement addPerson
    //int numUpRequest = 0;
    //int numDownRequest = 0;
    if (numPeople < MAX_PEOPLE_PER_FLOOR && request != 0) {
        people[numPeople] = newPerson;
        numPeople++;
        if (request > 0) {
            hasUpRequest = true;
        }
        if (request < 0) {
            hasDownRequest = true;
        }
    }
    //resetRequests();
    
    /*if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = people[numPeople] + newPerson;
        people = numPeople + newPerson;
    }
        if (newPerson.request() == hasUpRequest)
    while (numPeople < MAX_PEOPLE_PER_FLOOR) {
        //people = people + newPerson;
    }
    if (newPerson.hasUpRequest == true) {
        hasUpRequest += request;
    }
    else if (people(newPerson).hasUpRequest == false) {
        hasDownRequest += request;
    }*/
}

/*
 * Requires: numPeopleToRemove >= 0, numPeopleToRemove <= MAX_PEOPLE_PER_FLOOR,
 *           numPeopleToRemove >= 0, numPeopleToRemove <= numPeople,
 *           for all values of i such that 0 <= i < numPeopleToRemove, indicesToRemove[i] < numPeople
 * Modifies: people[], numPeople, hasUpRequest, hasDownRequest
 * Effects:  Removes objects from people[] at indices specified in indicesToRemove[].
 *           The size of indicesToRemove[] is given by numPeopleToRemove.
 *           After removals, calls resetRequests() to update hasUpRequest and hasDownRequest.
 */

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    //TODO: Implement removePeople
    int greaterOrEqualNumPeople = 0;
    for (int i = 0; i < numPeople; i++) {
        if (indicesToRemove[i] >= numPeople) {
            greaterOrEqualNumPeople++;
        }
    }
    if (numPeopleToRemove < 0 || numPeopleToRemove > MAX_PEOPLE_PER_FLOOR || numPeopleToRemove > numPeople || greaterOrEqualNumPeople != 0) {
        return;
    }
    Person tempArr[MAX_PEOPLE_PER_FLOOR];
    int numPeepsInTempArr = 0;
    for (int a = 0; a < numPeople; a++) {
        bool add = true;
        for (int j = 0; j < numPeopleToRemove; j++) {
            if (indicesToRemove[j] == a) {
                add = false;
            }
        }
        if (add == true) {
            tempArr[numPeepsInTempArr] = people[a];
            numPeepsInTempArr++;
        }
    }
    numPeople = numPeepsInTempArr;
    for (int k = 0; k < numPeople; k++) {
        people[k] = tempArr[k];
    }
    resetRequests();
}
    
    
    
    
    
    
    
    
    
    
    
    
    
   /* if (numPeopleToRemove >= 0 && numPeopleToRemove <= MAX_PEOPLE_PER_FLOOR && numPeopleToRemove <= numPeople) {
        for (int i = 0; i < numPeopleToRemove; i++) {
            if (indicesToRemove[i] < numPeople) {
                for (int j = 0; j < numPeople - 1 - indicesToRemove[i]; j++) {
                    //Person at index is copied from the next, and then the next from the one after.
                    people[indicesToRemove[i] + j] = people[indicesToRemove[i] + 1 + j];
                }
                //Number of people on the floor is reduced by 1 and the indices to remove is offset by 1 to compensate.
                numPeople--;
                indicesToRemove[i] -= 1;
            }
        }
        resetRequests();
    }
}*/

/*
 * Requires: nothing
 * Modifies: hasUpRequest, hasDownRequest
 * Effects: Search through people to find if there are any
 *          pending up requests or down requests. Set the
 *          values of hasUpRequest and hasDownRequest appropriately.
 *          This function is used to recalculate requests whenever
 *          the people on this floor are added or removed.
 */

void Floor::resetRequests() {
    //TODO: Implement resetRequests
    hasUpRequest = false;
    hasDownRequest = false;
    for(int i = 0; i < numPeople; i++) {
        if (people[i].getTargetFloor() > people[i].getCurrentFloor()) {
            hasUpRequest = true;
        }
        if (people[i].getTargetFloor() < people[i].getCurrentFloor()) {
            hasDownRequest = true;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
