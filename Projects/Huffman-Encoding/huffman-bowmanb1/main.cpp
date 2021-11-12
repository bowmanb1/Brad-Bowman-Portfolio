//
// Created by 13bra on 5/30/2020.
//
#include "List.h"
#include "HuffmanTree.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    string action = argv[1]; //encode or decode
    string input = argv[2]; //inputFile
    string output = argv[3]; //outputFile
    ifstream inputTest; //test the files
    ofstream outputTest; //test the files
    inputTest.open(input);
    outputTest.open(output);

    if (inputTest.fail()) { //test input file
        cerr << "Input file: " << input << " is not valid\n";
        return 1;
    }
    if (outputTest.fail()) { //test output file
        cerr << "Output file: " << output << " is not valid\n";
        return 1;
    }
    inputTest.close();
    outputTest.close();

    if (action != "-encode" && action != "-decode") { //only two actions
        cerr << "Invalid action: use -encode or -decode\n";
        return 1;
    }

    if (action == "-encode") {
        List *table = new List(10, .5);
        table->Read(input);
        table->InsertionSort(false); //this sorts in alphebetical
        table->InsertionSort(true); //this sorts by frequency

        HuffmanTree *myHuffman = new HuffmanTree(table);
        myHuffman->Build();
        myHuffman->TraverseTree();

        cout << myHuffman->GetFreqTable()->ToString();

        myHuffman->WriteCodes(input, output);

        delete table;
        delete myHuffman;
    } else if (action == "-decode") {
        List *table = new List(10, .5);

        ifstream encodedFile;
        encodedFile.open(input);

        string tableLetter;
        string strtableSize;
        getline(encodedFile, strtableSize);
        size_t tableSize = stoi(strtableSize);

        for (size_t i = 0; i < tableSize; i++) { //this will build the frequency table
            encodedFile >> tableLetter; //because of how I stored the table, the characters are repeated for the frequency so the table is accurate

            if (tableLetter == "SPACE") {
                LetterObject *addLetter = new LetterObject(" "); //turn to space
                table->Append(addLetter);
            } else {
                LetterObject *addLetter = new LetterObject(tableLetter); //append
                table->Append(addLetter);
            }
        } //the list does not need to be sorted since it was saved in sorted order!

        HuffmanTree *myHuffman = new HuffmanTree(table);
        myHuffman->Build();
        myHuffman->TraverseTree();
        cout << myHuffman->GetFreqTable()->ToString();
        myHuffman->Decode(input, output, tableSize);

        delete table;
        delete myHuffman;
    }

    return 0;
}


