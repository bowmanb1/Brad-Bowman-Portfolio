/*
 Filename: HuffmanTree.cpp
 Description: Implementation of the class HuffmanTree to represent the binary Huffman Tree
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/
#include "HuffmanTree.h"
#include <fstream>
HuffmanTree::HuffmanTree() : _root(nullptr) {
    _nodeList = new List();
    _freqTable = new List();
    _junkDrawer = new List();
}
//
HuffmanTree::HuffmanTree(List *table) : _root(nullptr) {
    _nodeList = new List();
    _freqTable = table;
    _junkDrawer = new List();
}


HuffmanTree::~HuffmanTree() {
    delete _nodeList;
    delete _junkDrawer;
}

void HuffmanTree::Build() {
    TreeNode *neo = nullptr;
    for (size_t i = 0; i < _freqTable->Size(); i++) { //this builds a stack of nodes with LetterObjects as data
        neo = new TreeNode;
        neo->_data = dynamic_cast<LetterObject *>(_freqTable->Get(i));
        neo->_left = nullptr;
        neo->_right = nullptr;
        neo->_data = neo->_data;
        neo->_left = neo->_right = nullptr;
        _nodeList->Append(neo);
        _junkDrawer->Append(neo);
    }

    while (_nodeList->Size() != 1) {
        TreeNode *left = dynamic_cast<TreeNode*>(_nodeList->Remove(_nodeList->Size() - 1));

        TreeNode *right = dynamic_cast<TreeNode*>(_nodeList->Remove(_nodeList->Size() - 1));

        TreeNode *parent = left->Combine(right); //parent is combination of left and right

        _nodeList->Insert(parent);
        _junkDrawer->Append(parent->_data); //take care of memory to delete
        _junkDrawer->Append(parent);
    }

    _root = dynamic_cast<TreeNode*>(_nodeList->Remove(_nodeList->Size() - 1));

}


string HuffmanTree::ToString() {
    stringstream output("");
    output << "root: \n" << _root->ToString() << endl;
    return output.str();
}

void HuffmanTree::TraverseTree(TreeNode *node, string code[], size_t encodeSize) { //this assigns codes to the freqTable members
    if (node->_left != nullptr) {
        code[encodeSize] = "1"; //add to top of string array
        TraverseTree(node->_left, code, encodeSize + 1); //recursive call, increase recursive array size
    }

    if (node->_right != nullptr) {
        code[encodeSize] = "0"; //add to top of string array
        TraverseTree(node->_right, code, encodeSize + 1); //recursive call, increase recursive array size
    }

    if (node->_left == nullptr && node->_right == nullptr) {
        stringstream printCode("");
        for (size_t i = 0; i <encodeSize; i++) {
            printCode << code[i];

        }
        node->_data->AssignEncoding(printCode.str());
    }
}

void HuffmanTree::TraverseTree() { //this is what is called in main
    string codeArray[256]; //out of using a queue, stringstream, and string, an array was the only way I found that the codes would store properly. I would have used my list class, but didn't want to make another object class
    size_t arrSize = 0;
    TraverseTree(_root, codeArray, arrSize);
}

bool HuffmanTree::WriteCodes(const string &input, const string &output) { //write encoding and save frequency table
    ifstream inputFile;
    inputFile.open(input);
    ofstream outputFile;
    outputFile.open(output);
    char letter;
    size_t totalFreq = 0;
    for (size_t x = 0; x < _freqTable->Size(); x++) { //this gets the total frequency of the table. To be used with decoding
        totalFreq += dynamic_cast<LetterObject*>(_freqTable->Get(x))->GetFrequency();
    }
    outputFile << totalFreq << endl;
    for (size_t i = 0; i < _freqTable->Size(); i++) { //this writes the codes into the encoding file, space given a string name to be recognized during read
        LetterObject* temp = dynamic_cast<LetterObject*>(_freqTable->Get(i));
        if (temp->GetCharacter() == " ") {
            for (size_t j = 0; j < temp->GetFrequency(); j++) { //adds it into the file for however many times it occurs
                outputFile << "SPACE" << " ";
            }
        } else {
            for (size_t j = 0; j < temp->GetFrequency(); j++) { //adds it into the file for however many times it occurs
                outputFile << temp->GetCharacter() << " ";
            }
        }
    }

    outputFile << "\n"; //new line after table
    while (!inputFile.eof()) {
        letter = inputFile.get();
        string strLetter(1, letter);
        if (letter == '\n') {
            outputFile << dynamic_cast<LetterObject*>(_freqTable->GetLetter("CR"))->GetEncoding();
        } else if (letter == '\r') {
            outputFile << dynamic_cast<LetterObject*>(_freqTable->GetLetter("LF"))->GetEncoding();
        } else if (letter == ' ') {
            outputFile << dynamic_cast<LetterObject*>(_freqTable->GetLetter(" "))->GetEncoding();
        }
        else if (!inputFile.eof()){
            string strLetter(1, letter);
            outputFile << dynamic_cast<LetterObject*>(_freqTable->GetLetter(strLetter))->GetEncoding();
        }
    }

    return true;
}

bool HuffmanTree::WriteTable(const string &fileName) {
    ofstream fout;
    fout.open(fileName);
    if (fout.bad()) {
        cerr << "Invalid file name" << endl;
        return false;
    }

    fout << _freqTable->ToString();

    fout.close();
    return true;

}

List* HuffmanTree::GetFreqTable() {
    return _freqTable;
}

void HuffmanTree::Decode(const string &inputFile, const string &outputFile, size_t tableSize) {
    ifstream codedFile;
    codedFile.open(inputFile);

    string codeLetter;
    TreeNode *temp = _root;
    ofstream decodeFile;
    decodeFile.open(outputFile);
    string ignoreTable;
    for (size_t i = 0; i < tableSize; i++) { //this moves the cursor past the table written to the encoding file so the decode doesn't use any "1" or "0" characters
        codedFile >> ignoreTable;
    }

    while(!codedFile.eof()) {
        codeLetter = codedFile.get();
        if (codeLetter == "1") { //move left
            if (temp->_left) //check that it is not null!
                temp = temp->_left;
        } else if (codeLetter == "0") { //move right
            if (temp->_right) //check that it is not null!
                temp = temp->_right;
        }
        if (!temp->_left && !temp->_right) {
            if (temp->_data->GetCharacter() == "CR") { //revert to new line
                decodeFile << "\n";
            } else if (temp->_data->GetCharacter() == "LF") { //revert to carriage return
                decodeFile << "\r";
            } else {
                decodeFile << temp->_data->GetCharacter(); //add character
            }
            temp = _root; //reset to starting position!
        }
    }
    codedFile.close();
    decodeFile.close();
}