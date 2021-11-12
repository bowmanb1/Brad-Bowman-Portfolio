/*
 Filename: Object.h
 Description: Declaration of the class Object to represent a general object
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_BOWMANB1_OBJECT_H
#define HUFFMAN_BOWMANB1_OBJECT_H

#include <iostream>
#include <string>
using std::string;
using std::stringstream;
class Object {
protected:

public:
    Object();
    virtual ~Object();
    virtual string ToString();
    virtual bool Equals(const Object& rhs);
    virtual Object* Clone()const;
    virtual Object& operator=(Object* rhs);
    virtual void IncreaseFrequency(); //included just for LetterObject
    virtual Object Combine(Object *rhs);
};


#endif //HUFFMAN_BOWMANB1_OBJECT_H
