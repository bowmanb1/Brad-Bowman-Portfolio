/*
 Filename: HuffmanTree.h
 Description: Declaration of the class HuffmanTree to represent the binary Huffman Tree
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_BOWMANB1_HUFFMANTREE_H
#define HUFFMAN_BOWMANB1_HUFFMANTREE_H
#include "TreeNode.h"
#include "LetterObject.h"
#include "List.h"
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
class HuffmanTree {
private:
    TreeNode* _root;
    List *_nodeList;
    List *_freqTable;
    List *_junkDrawer; //this is my method to handle memory leaks. Anything that was getting leaked gets added to the drawer and deleted at the end
    void TraverseTree(TreeNode* node, string arr[], size_t arrSize);
public:
    HuffmanTree();
    HuffmanTree(List *table);
    ~HuffmanTree();
    void Build();
    string ToString();
    void TraverseTree();
    List *GetFreqTable();
    bool WriteTable(const string &fileName);
    bool WriteCodes(const string &input, const string &output);
    void Decode(const string &inputFile, const string &outputFile, size_t tableSize);
};


#endif //HUFFMAN_BOWMANB1_HUFFMANTREE_H
