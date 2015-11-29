//
//  linkedBinaryTree.h
//  c++初体验
//
//  Created by SXB on 15/11/11.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#ifndef c______linkedBinaryTree_h
#define c______linkedBinaryTree_h


#endif
#include "binaryTreeNode.h"
#include "arrayqueue.h"
template<class E>
class linkedBinaryTree{
public:
    linkedBinaryTree();
    void makeTree(E  x);
    //    ~linkedBinaryTree(){ erase(); };
    binaryTreeNode<E>* getroot();
    bool empty() const { return treeSize == 0; }
    int size() const{ return treeSize; }
    void visit(binaryTreeNode<E> *x);
    void preOrder(binaryTreeNode<E> *x);
    void inOrder(binaryTreeNode<E> * x);
    void postOrder(binaryTreeNode<E> * x);
    void levelOrder(binaryTreeNode<E> * x);
    int height(binaryTreeNode<E> * x);
    void erase()
    {
        //postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    
private:
    binaryTreeNode<E> *root;
    int treeSize;
};


template<class E>
linkedBinaryTree<E>::linkedBinaryTree(){
    root = NULL; treeSize = 0;
}

template<class E>
binaryTreeNode<E> * linkedBinaryTree<E>::getroot(){
    return root;
}

template<class E>
void linkedBinaryTree<E>::makeTree(E  x){
    arrayqueue<binaryTreeNode<E>*> *q =new arrayqueue<binaryTreeNode<E>*>(100);
    binaryTreeNode<E> * temp = root;
    binaryTreeNode<E> * temp1 = root;
    if (temp == NULL)
    {
        cout << "temp = null" << endl;
        root = new binaryTreeNode<E>(x, NULL, NULL);
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->leftChild != NULL)
            {
                cout << "temp->leftChild = null" << endl;
                q->push(temp->leftChild);
            }
            if (temp->rightChild != NULL)
            {
                cout << "temp->rightChild = null" << endl;
                q->push(temp->rightChild);
            }
            if (!q->empty()){
                cout << "!q->empty" << endl;
                temp1=temp;
                temp = q->front();
                q->pop();
            }
            else break;
        }
        temp = new binaryTreeNode<E>(x, NULL, NULL);
        temp1.leftadd(temp);
    }
    if (root == NULL) {
        cout << "root = null" << endl;
    }
    treeSize++;
}

template<class E>//访问树节点
void linkedBinaryTree<E>::visit(binaryTreeNode<E> * x){
    cout << x->element<< endl;
}

template<class E>//前序遍历
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *x){
    cout << "进入preOrder方法" << endl;
    cout << "当前的binaryTreeNode x的值是：" << x->element << endl;
    if (x != NULL){
        visit(x);
        preOrder(x->leftChild);
        preOrder(x->rightChild);
    }
}
template<class E>//中序遍历
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *x){
    cout << "进入inOrder方法" << endl;
    cout << "当前的binaryTreeNode x的值是：" << x->element << endl;
    if (x != NULL){
        inOrder(x->leftChild);
        visit(x);
        inOrder(x->rightChild);
    }
}
template<class E>//后序遍历
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *x){
    if (x != NULL){
        postOrder(x->leftChild);
        postOrder(x->rightChild);
        visit(x);
    }
}
template<class E>//层次遍历
void linkedBinaryTree<E>::levelOrder(binaryTreeNode<E> *x){
    arrayqueue<binaryTreeNode<E>*> q =new arrayqueue<binaryTreeNode<E>*>(100);
    while (x!=NULL)
    {
        visit(x);
        if (x->element != NULL)
            q->push(x->leftChild);
        if (x->rightChild != NULL)
            q->push(x->rightChild);
        if (!q.empty()){
            x = q->front();
            q->pop();
        }
        else break;
    }
}

template<class E>//树的高度。
int linkedBinaryTree<E>::height(binaryTreeNode<E> * x){
    if (x == NULL)
        return 0;
    int h1 = height(x->leftChild);
    int h2 = height(x->rightChild);
    if (h1 > h2)
        return ++h1;
    else
        return ++h2;
}

