/*
 Filename: List.cpp
 Description: Implementation of the class List which is a variable sized array to hold objects
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/
#include "List.h"
#include "TreeNode.h"
List::List() : _capacity(10) , _delta(.5) , _size(0) {
    _data = new Object*[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = nullptr;
    }
}

List::List(size_t capacity, double increasePercentage) : _capacity(capacity) , _delta(increasePercentage) , _size(0) {
    _data = new Object*[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = nullptr;
    }
}
List::~List(){
    for (size_t i = 0; i < _size; i++) {
             delete _data[i];
    }
    delete []_data;
}

const List& List::operator=(const List &rhs) {
    if (&rhs == this){
        return *this;
    }
    if (_capacity != rhs._capacity){
        Clear();
        delete[] _data;
        _capacity = rhs._capacity;
        _data = new Object*[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _data[i] = nullptr;
        }
    }
    for (size_t i = 0; i < rhs.Size(); i++) {
        _data[i] = rhs.Get(i)->Clone();
    }
    return *this;
}

bool List::Append(Object* element){ //adds object to end of list
    if (_capacity == _size) {
        Resize();
    }
    if (dynamic_cast<TreeNode*>(element) != nullptr) { //if dealing with TreeNode
        if (_size == 0) {
            _data[0] = element;
            _size++;
            return true;
        }
        int index = IndexOf(element);
        if (index != -1) {
            return false;
        }
        _data[_size] = element;
        _size++;
        return true;
    }
    if (dynamic_cast<LetterObject*>(element) != nullptr) { //if dealing with LetterObject
        if (_size == 0) {
            _data[0] = element;
            _size++;
            return true;
        }
        int index = IndexOf(element);
        if (index != -1) {
            _data[index]->IncreaseFrequency();
            delete element; //if it did not get inserted, then discard it after increasing frequency
            return false;
        }
        _data[_size] = element;
        _size++;
        return true;
    }
    if (_size == 0) {
        _data[0] = element;
        _size++;
        return true;
    }
    int index = IndexOf(element);
    if (index != -1) {
        _data[index]->IncreaseFrequency();
        return false;
    }
    _data[_size] = element;
    _size++;
    return true;

}

bool List::Insert(Object *element) { //inserts an element in sorted position
    if (_capacity == _size) {
        Resize();
    }
    if (_size == 0) {
        _data[0] = element;
        _size++;
        return true;
    }
    size_t index = 0;
    if (dynamic_cast<TreeNode*>(Get(_size - 1))->_data->GetFrequency() < dynamic_cast<TreeNode*>(element)->_data->GetFrequency()) { //for TreeNodes
        for (int i = _size - 1; i >= 0; i--) {
            if (dynamic_cast<TreeNode*>(Get(i))->_data->GetFrequency() < dynamic_cast<TreeNode*>(element)->_data->GetFrequency()) {
                index = i;
            }
        }
    } else {
        index = _size;
    }

    if (index < _size) { //shifts elements
        for (size_t i = _size; i > index; i--){
            _data[i] = _data[i - 1];
        }
    }
    _data[index] = element; //assign element
    _size++;
    return true;
}

int List::IndexOf(const Object *element) {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i]->Equals(*element)){
            return i;
        }
    }
    return -1;
}
Object *List::Remove(size_t position) {
    if (position >= _size){
        return nullptr;
    }
    Object *retVal = _data[position];
    for (size_t i = position; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }
    _data[_size - 1] = nullptr;
    _size--;
    return retVal;
}
Object* List::Get(size_t position) const{
    if (position >= _size)
        return nullptr;
    else
        return _data[position];
}

void List::Clear(){
    for (size_t i = 0; i < _size; i++) {
        delete _data[i];
        _data[i] = nullptr;
    }
    _size = 0;
}

void List::Resize() {
    size_t increase = _capacity * _delta;
    size_t newSize = _capacity + increase;
    Object** resize = nullptr;
    resize = new Object*[newSize];
    for (size_t i = 0; i < _size; i++) {
        resize[i] = _data[i];
    }
    _capacity = newSize;
    delete []_data;
    _data = resize;
}

size_t List::GetCapacity() const {
    return _capacity;
}

bool List::Read(const string &fileName) { //reads and makes list of LetterObjects
    ifstream fin;
    fin.open(fileName);
    if (fin.fail()) { //bad file
        return false;
    }
    char letter;

    while (!fin.eof()) {
        letter = fin.get(); //fin.get() allows for dealing with spaces
        string strLetter(1, letter);
        if (letter == '\n') {
            LetterObject *newLetter = new LetterObject("CR");
            Append(newLetter);
        } else if (letter == '\r') {
            LetterObject *newLetter = new LetterObject("LF");
            Append(newLetter);
        } else if (letter == ' ') {
            LetterObject *newLetter = new LetterObject(" ");
            Append(newLetter);
        }
        else if (!fin.eof()){
            string strLetter(1, letter); //conert from a char to a string
            LetterObject *newLetter = new LetterObject(strLetter);
            Append(newLetter);
        }
    }

    return true;
}

string List::ToString() {
    stringstream output;
    for (size_t i = 0; i < _size; i++)
        output << _data[i]->ToString() << endl;
    return output.str();
}

size_t List::Size() const{
    return _size;
}

void List::InsertionSort(bool sortFreq) { //this sorts LetterObjects
    LetterObject *letter;
    int j = 0; //I had to turn j into an integer because size_t j cannot go negative, which can occur for j = i - 1
    if (sortFreq) { //this sorts for frequency
        for (size_t i = 1; i < _size; i++) {
            letter = dynamic_cast<LetterObject*>(_data[i]);
            j = i - 1;
            while (j >= 0 && dynamic_cast<LetterObject*>(_data[j])->GetFrequency() <= letter->GetFrequency()) { //compare elements
                _data[j + 1] = _data[j]; //shift elements
                j = j - 1;
            }
            _data[j + 1] = letter;
        }
    } else { //sorts alphabetically
        for (size_t i = 1; i < _size; i++) {
            letter = dynamic_cast<LetterObject*>(_data[i]);
            j = i - 1;
            while (j >= 0 && (dynamic_cast<LetterObject*>(_data[j])->GetCharacter() >  letter->GetCharacter())) { //compare elements
                _data[j + 1] = _data[j]; //shift elements
                j = j - 1;
            }
            _data[j + 1] = letter;
        }
    }
}

Object* List::GetLetter(const string &letter) {
    for (size_t i = 0; i < _size; i++) {
        string objLetter = dynamic_cast<LetterObject*>(_data[i])->GetCharacter();
        if (objLetter == letter) {
            return dynamic_cast<LetterObject*>(_data[i]);
        }
    }
    return nullptr;
}
