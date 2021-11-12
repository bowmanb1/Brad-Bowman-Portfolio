/*
 Filename: LetterObject.cpp
 Description: Implementation of the class LetterObject, which represents a letter with frequency and an encoding
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/

#include "LetterObject.h"
LetterObject::LetterObject() : Object(){ //I was given warnings when I had these variables in the same format as object, so I moved them inside the constructor
    _character = "";
    _encoding = "";
    _frequency = 1;
}

LetterObject::LetterObject(const string &character) :  Object(){ //I was given warnings when I had these variables in the same format as object, so I moved them inside the constructor
    if (_character == " ") {
        _character = " ";
    } else if (character == "\r") {
        _character = "LF";
    } else if (character == "\n") {
        _character = "CR";
    } else {
        _character = character;
    }
    _encoding = "";
    _frequency = 1;
}


LetterObject& LetterObject::operator=(const LetterObject *rhs) {
    _character = rhs->_character;
    _frequency = rhs->_frequency;
    _encoding = rhs->_encoding;
    return *this;
}



LetterObject::~LetterObject() {
}

bool LetterObject::Equals(const Object& rhs) {
    const LetterObject* rhsLetter = dynamic_cast<const LetterObject*>(&rhs);
    if (rhsLetter == nullptr)
        return false;

    return (_character == rhsLetter->_character); //check if characters are equal, frequancy is irrelevant
}

LetterObject *LetterObject::Combine(LetterObject *rhs)  {
    LetterObject *retVal = new LetterObject(); //create a new LetterObject
    size_t x = _frequency;
    size_t y = rhs->_frequency;
    retVal->_frequency = x + y; //add frequencies
    retVal->_character += _character;
    retVal->_character += rhs->_character; //combine letters
    return retVal;

}

void LetterObject::AssignEncoding(const string &encoding) {
    _encoding = encoding;
}

void LetterObject::IncreaseFrequency() {
    _frequency++;
}

string LetterObject::GetCharacter() {
    return _character;
}

size_t LetterObject::GetFrequency() {
    return _frequency;
}

string LetterObject::GetEncoding() {
    return _encoding;
}
#include <iomanip>
string LetterObject::ToString() {
    stringstream output("");
    output << "{key:" << std::setw(3) << _character << ", code: " << _encoding << "}";
    return output.str();
}

void LetterObject::operator=(LetterObject *rhs) {
    _frequency = rhs->_frequency;
    _character = rhs->_character;
    _encoding = rhs->_encoding;
}

bool LetterObject::Equals(const LetterObject *rhs) {
    if (rhs == nullptr)
        return false;
    return (_character == rhs->_character);
}

