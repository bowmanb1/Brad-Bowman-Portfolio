/*
 Filename: LetterObject.h
 Description: Declaration of the class LetterObject, which represents a letter with frequency and an encoding
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/
#ifndef HUFFMAN_BOWMANB1_LETTEROBJECT_H
#define HUFFMAN_BOWMANB1_LETTEROBJECT_H

#include <glob.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include "List.h"

using std::string;
using std::stringstream;
using namespace std;

class LetterObject : public Object {
protected:
    string _character;
    size_t _frequency;
    string _encoding;
public:
    LetterObject(); //default
    LetterObject(const string &character);
    virtual LetterObject& operator=(const LetterObject *rhs);
    virtual ~LetterObject();
    virtual bool Equals(const Object& rhs);
    virtual bool Equals(const LetterObject* rhs);
    virtual LetterObject *Combine(LetterObject *rhs) ;
    virtual void AssignEncoding(const string &encoding);
    virtual void IncreaseFrequency();
    virtual string GetCharacter();
    virtual size_t GetFrequency();
    virtual string GetEncoding();
    virtual string ToString();
    virtual void operator=(LetterObject* rhs);
};


#endif //HUFFMAN_BOWMANB1_LETTEROBJECT_H
