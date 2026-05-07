/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

// declare your test functions here
void person_tests();
void elevator_tests();
void floor_tests();

void start_tests() {
    // call your test functions here
    person_tests();
    elevator_tests();
    floor_tests();
    return;
}

// write test functions here
void person_tests() {
    //initialize a person with targetFloor 5, anger 5
    Person p("0f0t5a5");
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    Person g("1f6t2a8");
    cout << "\nThe person you just entered is: ";
    g.print(cout);
    exploded = g.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << g.getCurrentFloor() << " " << g.getTurn() << endl;
    cout << g.getTargetFloor() << " " << g.getAngerLevel() << " Expected 2 8" << endl;
    g.tick(TICKS_PER_ANGER_INCREASE);
    cout << g.getAngerLevel() << endl;
    exploded = g.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    g.tick(TICKS_PER_ANGER_INCREASE);
    exploded = g.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    g.tick(TICKS_PER_ANGER_INCREASE);
    g.tick(2);
    cout << g.getAngerLevel() << endl;
    exploded = g.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    Person m("2f3t4a2");
    cout << "\nThe person you just entered is: ";
    g.print(cout);
    exploded = m.tick(TICKS_PER_ANGER_INCREASE);
    cout << m.getTargetFloor() << " " << m.getAngerLevel() << " Expected 4 2" << endl;
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    cout << exploded << " Expected 0" << endl;
    m.tick(6);
    cout << m.getTargetFloor() << " " << m.getAngerLevel() << " Expected 4 1" << endl;
    //simulate time not being a multiple
    m.tick(TICKS_PER_ANGER_INCREASE);
    //no change
    cout << m.getTargetFloor() << " " << m.getAngerLevel() << " Expected 4 0" << endl;
    m.tick(TICKS_PER_ANGER_INCREASE);
    exploded = m.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    m.tick(TICKS_PER_ANGER_INCREASE + 3);
    cout << m.getAngerLevel() << endl;
    m.tick(TICKS_PER_ANGER_INCREASE - 3);
    exploded = m.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
}
void elevator_tests() {
    // NOTE - there is an Elevator::print function!
    // this will not find any of the bugs for the lab assignment
    Elevator e1;
    e1.print(cout);
    cout << e1.isServicing() << endl;
    e1.serviceRequest(2);
    e1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << e1.isServicing() << endl;
    e1.serviceRequest(1);
    e1.tick(3);
    cout << e1.isServicing() << endl;
    e1.setCurrentFloor(0);
    e1.serviceRequest(1);
    e1.tick(1);
    e1.getCurrentFloor();
    e1.serviceRequest(-2);
    e1.tick(-2);
    e1.print(cout);
    cout << e1.isServicing() << endl;
    if (e1.isServicing() != true) {
        e1.serviceRequest(-1);
    }
    Elevator e2;
    e2.setCurrentFloor(0);
    e2.getCurrentFloor();
    e2.serviceRequest(3);
    e2.getTargetFloor();
    e2.tick(TICKS_PER_ELEVATOR_MOVE);
    e2.getCurrentFloor();
    cout << e2.isServicing() << endl;
    e2.tick(1);
    cout << e2.isServicing() << endl;
    e2.tick(3);
    e2.getCurrentFloor();
    cout << e2.isServicing() << endl;
    e2.setCurrentFloor(3);
    e2.serviceRequest(0);
    e2.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << e2.isServicing() << endl;
    e2.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << e2.isServicing() << endl;
    e2.tick(3);
    cout << e2.isServicing() << endl;
    e2.print(cout);
    if (e2.isServicing() != true) {
        e2.serviceRequest(3);
    }
    else {
        e2.tick(4);
    }
    e2.tick(NUM_FLOORS);
    e2.setCurrentFloor(0);
    e2.serviceRequest(NUM_FLOORS + 3);
    e2.tick(NUM_FLOORS + 5);
    cout << e2.isServicing() << endl;
    e2.print(cout);
    return;
}

void floor_tests() {
    Floor f1;
    Person person1;
    Person person2;
    f1.tick(0);
    f1.addPerson(person1, 3);
    f1.tick(3);
    f1.tick(1);
    //f1.resetRequests();
    f1.addPerson(person2, 5);
    f1.tick(-3);
    //f1.removePeople(<#int *indicesToRemove#>, <#const int numPeopleToRemove#>)
}
