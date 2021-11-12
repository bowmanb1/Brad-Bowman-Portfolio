/*
 Filename: TreeNode.cpp
 Description: Implementation of the class TreeNode to represent a node of a huffman tree
 Author: Brad Bowman
 Date: 06/12/2020
 Course: Data Structures II
*/

#include "TreeNode.h"
TreeNode::TreeNode() : Object() {
}

TreeNode::TreeNode(TreeNode *node) : Object () {
    _data = node->_data;
    _left = node->_left;
    _right = node->_right;
}

TreeNode::~TreeNode() {
}

TreeNode *TreeNode::Combine(TreeNode *rhs) {
    TreeNode *retVal = new TreeNode;
    TreeNode b = rhs;

    retVal->_data = _data->Combine(rhs->_data);
    retVal->_left = this;
    retVal->_right = rhs;
    return retVal;
}

string TreeNode::ToString() {
    stringstream output("{");
    output << "\tparent: " << _data->ToString() << endl;
    if (left != nullptr)
        output << "left: " << _left->ToString() << endl;

    if (right != nullptr)
        output << "right: " << _right->ToString() << endl;
    output << "}" << endl;
    return output.str();
}

void TreeNode::operator=(TreeNode *rhs) {
    _data = rhs->_data;
    _left = rhs->_left;
    _right = rhs->_right;
}

bool TreeNode::Equals(const Object &rhs){
    const TreeNode* rhsNode = dynamic_cast<const TreeNode*>(&rhs);
    if (rhsNode == nullptr) {
        return false;
    }

    return (_data->Equals(rhsNode->_data));
}

bool TreeNode::Equals(Object *rhs) {
    const TreeNode* rhsNode = dynamic_cast<const TreeNode*>(rhs);
    if (rhsNode == nullptr) {
        return false;
    }

    return (_data->Equals(rhsNode->_data));
}