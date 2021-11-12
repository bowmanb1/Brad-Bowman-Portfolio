/*
 Filename: TreeNode.h
 Description: Declaration of the class TreeNode to represent a node of a huffman tree
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_BOWMANB1_TREENODE_H
#define HUFFMAN_BOWMANB1_TREENODE_H
#include "LetterObject.h"
class TreeNode : public Object {
protected:

public:
    LetterObject *_data;
    TreeNode *_left;
    TreeNode *_right;
    TreeNode();
    TreeNode(TreeNode *node);
    virtual ~TreeNode();
    virtual TreeNode *Combine(TreeNode *rhs);
    virtual string ToString();
    virtual void operator=(TreeNode *rhs);
    virtual bool Equals(const Object &rhs);
    virtual bool Equals(Object* rhs);
};


#endif //HUFFMAN_BOWMANB1_TREENODE_H
