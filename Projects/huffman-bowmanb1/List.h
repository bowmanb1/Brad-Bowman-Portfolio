/*
 Filename: List.h
 Description: Declaration of the class List which is a variable sized array to hold objects
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_BOWMANB1_LIST_H
#define HUFFMAN_BOWMANB1_LIST_H

#include "Object.h"
#include "LetterObject.h"
#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
class List {
protected:
    Object** _data;
    size_t _capacity;
    double _delta;
    List(const List&);
    const List& operator=(const List &rhs);
    void Resize();
public:
    size_t _size;
    List();
    List(size_t capacity, double increasePercentage = 0.5);
    virtual ~List();
    virtual bool Append(Object* element);
    virtual bool Insert(Object *element);
    virtual int IndexOf(const Object *element);
    virtual Object *Remove(size_t position);
    virtual Object* Get(size_t position)  const;
    virtual void Clear();
    size_t GetCapacity()const;
    string ToString();
    size_t Size() const;
    virtual bool Read(const string &fileName);
    void InsertionSort(bool sortFreq);
    Object* GetLetter(const string &letter);
};


#endif //HUFFMAN_BOWMANB1_LIST_H
