/*
 Filename: Object.cpp
 Description: Implementation of the class Object to represent a general object
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/
#include "Object.h"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
Object::Object() {

}

Object::~Object() {

}

string Object::ToString() {
    stringstream retVal;
    retVal << "Object @ " << this;
    return retVal.str();
}

bool Object::Equals(const Object &rhs){
    std::cout << "INHERITANCE ISSUE " << std::endl;
    return this == &rhs;
}

Object* Object::Clone() const {
    return new Object();
}

void Object::IncreaseFrequency() {
}

Object Object::Combine(Object *rhs) {
    return *rhs;
}

Object& Object::operator=(Object *rhs) {
    *this = rhs;
    return *this;
}