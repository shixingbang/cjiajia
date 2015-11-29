//
//  binaryTreeNode.h
//  c++初体验
//
//  Created by SXB on 15/11/11.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#ifndef c______binaryTreeNode_h
#define c______binaryTreeNode_h


#endif
template<class T>
struct binaryTreeNode{
    T element;
    binaryTreeNode<T> *leftChild,	*rightChild;
    bool hasbro = false;
    
    binaryTreeNode(){
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement){
        element = theElement;
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode *theleft, binaryTreeNode *theright){
        element = theElement;
        leftChild = theleft;
        rightChild = theright;
    }
    
};