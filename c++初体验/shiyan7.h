//
//  shiyan7.h
//  c++初体验
//
//  Created by SXB on 15/11/22.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#ifndef c______shiyan7_h
#define c______shiyan7_h
#include<iostream>
#include "shiyan6.h"  //  因为我要用到实验六里的BinaryTree
#include "shiyan5.h"  //  因为我又想用堆栈了。。。
using namespace std;

//  MARK:  最大堆
template<class T>
class MaxHeap
{
public:
    MaxHeap(int MaxHeapSize = 10);
    ~MaxHeap() {delete [] heap;}
    int Size() const { return CurrentSize;}
    T Max() {
        if (CurrentSize == 0) {
//            throw OutOfBounds()
        }
        return heap[1];
    }
    MaxHeap<T>& Insert(const T& x );
    MaxHeap<T>& DeleteMax(T& x );
    MaxHeap<T>& Delete(T x);
    void Initialize(T a[], int size, int ArraySize);
    void Output();
    

    int CurrentSize, MaxSize;
    T *heap; //  元素数组
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
//    构造函数
    MaxSize = MaxHeapSize;
    heap = new T[MaxSize + 1];
    CurrentSize = 0;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x )
{
//    把 x插入到最大堆中
    if (CurrentSize == MaxSize) {
//        throw NoMem()
    }
    
//    为 x寻找应插入位置
//    i从新的叶节点开始， 并沿着树上升
    int i = ++CurrentSize;
    while (i != 1 && x > heap[i/2]) {
//        不能够把x 放入 heap[i]
        heap[i] = heap[i/2];   //  将元素下移
        i /= 2;                //  移向父节点
    }
    heap[i] = x;
    return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x )
{
//    将最大元素放入x，并从堆中删除最大元素
//    检查堆是否为空
    if (CurrentSize == 0) {
//        throw OutOfBounds();
    }
    
    x = heap[1];                //  最大元素
    
//    重构堆（将右下角元素放入由于上移缺省掉的位置，保持原形态）
    T y = heap[CurrentSize--];  //  最后一个元素
    
//    从根开始，为y寻找合适的位置
    int i = 1;      //  堆的当前节点
    int ci = 2;     //  i的孩子
    while (ci <= CurrentSize) {
//        heap[ci]应是i的较大的孩子
        if (ci < CurrentSize && heap[ci] < heap[ci+1]) {
            ci++;
        }
        
//        能把y放入heap[i]吗?
        if (y >= heap[ci]) {
            break;      //  能
        }
        
//        不能
        heap[i] = heap[ci];   //  将孩子上移
        i = ci;               //  下移一层
        ci *= 2;
    }
    heap[i] = y;
    
    return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Delete(T x)
{
    int i=1;
    while (heap[i]) {
        if (heap[i] == x) {
            break;
        }
        i++;
    }
//    重构堆
    T y = heap[CurrentSize--];      //  最后一个元素
    heap[CurrentSize+1] = 0;
//    从根开始，为y 寻找合适的位置
//    i为堆的当前节点
    int ci = 2*i;  // i的孩子
    while (ci <= CurrentSize) {
        if (ci < CurrentSize && heap[ci] < heap[ci+1]) {
            ci++;
        }
        
        if (y >= heap[ci]) {
            break;
        }
        
        heap[i] = heap[ci];
        i = ci;
        ci *= 2;
    }
    heap[i] = y;
    
    return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
//    把最大堆初始化为数组 a
    delete [] heap;
    heap = new T[ArraySize+1];
    for (int i=1; i<size+1; i++) {
        heap[i] = a[i-1];
    }
    CurrentSize = size;
    MaxSize = ArraySize;
    
//    产生一个最大堆
    for (int i = CurrentSize/2; i >= 1; i--) {
        T y = heap[i];              //  子树的根
        
//        寻找放置y的位置
        int c = 2*i;                // c的父节点是y的目标位置
        while (c <= CurrentSize) {
//            heap[c]应是较大的同胞节点
            if (c < CurrentSize && heap[c] < heap[c+1]) {
                c++;
            }
//            把 y 放入heap[c/2]
            if (y >= heap[c]) {
                break;              //  能
            }
            
//            不能
            heap[c/2] = heap[c];    //  将孩子上移
            c *= 2;                 //  下移一层
        }
        
        heap[c/2] = y;
    }
}

template<class T>
void MaxHeap<T>::Output()
{
    int i=1;
    while (heap[i] != 0) {
        cout << heap[i] << " ";
        i++;
    }
}

//  MARK:  堆排序
template<class T>
void HeapSort(T a[], int n)
{
    MaxHeap<T> H(1);
    H.Initialize(a, n ,n);
    
    T x;
    for (int i=n; i>=1; i--) {
        H.DeleteMax(x);
        a[i-1] = x;
    }
    
    cout << "堆排序后: " << endl;
    for (int i=0; i<n; i++) {
        cout << a[i] << " ";
    }
}


//  MARK: 最小堆

template<class T>
class MinHeapNode
{
    MinHeapNode()
    {
        LeftChild = RightChild = 0;
    }
    MinHeapNode(const T& e)
    {
        data = e;
        LeftChild = RightChild = 0;
    }
    MinHeapNode(const T& e,MinHeapNode *l, MinHeapNode *r){
        data = e;
        LeftChild = l;
        RightChild = r;
    }
    T data;
    MinHeapNode<T> *LeftChild;
    MinHeapNode<T> *RightChild;
};

template<class T>
class MinHeap {
public:
    MinHeap(int MinHeapSize = 10);
    ~MinHeap() {delete [] heap;}
    int Size() const {return CurrentSize;}
    T Min() {
        if (CurrentSize == 0) {
            //            throw OutOfBounds();
        }
        return heap[1];
    }
    MinHeap<T>& Insert(const T& x);
    MinHeap<T>& DeleteMin(T &x);
    void Initialize(T a[], int size, int ArraySize);
    void Output();
    
private:
    int CurrentSize, MaxSize;
    T *heap;
    MinHeapNode<T> *root;
};

template<class T>
MinHeap<T>::MinHeap(int MinHeapSize)
{
    MaxSize = MinHeapSize;
    heap = new T[MaxSize + 1];
//    heap = new MinHeapNode<T>[MaxSize + 1];
    CurrentSize = 0;
    root = 0;
}

template<class T>
MinHeap<T>& MinHeap<T>::Insert(const T& x )
{
//    MinHeapNode<T> tmp_x = new MinHeapNode<T>(x);
//    
//    MinHeapNode<T> father = heap[(++CurrentSize)/2];
//    if (CurrentSize % 2 == 0) {
//        father =  MinHeapNode<T>(father->data, heap[CurrentSize-1], tmp_x);
//    }else
//        father = MinHeapNode<T>(father->data, tmp_x, NULL);
//    
//    if (CurrentSize == MaxSize) {
//        //        throw NoMem();
//    }
//    
//    int i = ++CurrentSize;
//    while (i != 1 && x < heap[i/2]->data) {
//        heap[i]->data = heap[i/2]->data;
//        i /= 2;
//    }
//    
//    heap[i]->data = x;
//    return *this;
    if (CurrentSize == MaxSize) {
//        throw NoMem();
    }
    int i = ++CurrentSize;
    while (i != 1 && x.weight < heap[i/2].weight) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = x;
    return *this;
}

template<class T>
MinHeap<T>& MinHeap<T>::DeleteMin(T &x)
{
    if (CurrentSize == 0) {
        //        throw OutOfBounds();
    }
    
    x = heap[1];
    
    T y = heap[CurrentSize--];
    
    int i= 1, ci = 2;
    while (ci <= CurrentSize) {
        if (ci < CurrentSize && heap[ci].weight > heap[ci+1].weight) {
            ci++;
        }
        
        if (y.weight <= heap[ci].weight) {
            break;
        }
        
        heap[i] = heap[ci];
        i = ci;
        ci *= 2;
    }
    heap[i] = y;
    
    return *this;
}

template<class T>
void MinHeap<T>::Initialize(T a[], int size, int ArraySize)
{
    delete [] heap;
    heap = new T[ArraySize+1];
    for (int i=1; i<size+1; i++) {
        heap[i] = a[i];
    }
    CurrentSize = size;
    MaxSize = ArraySize;
    
    for (int i = CurrentSize/2; i >= 1; i--) {
        T y = heap[i];              //  子树的根
        
        //        寻找放置y的位置
        int c = 2*i;                // c的父节点是y的目标位置
        while (c <= CurrentSize) {
            if (c < CurrentSize && heap[c].weight > heap[c+1].weight) {
                c++;
            }
            //            把 y 放入heap[c/2]
            if (y.weight <= heap[c].weight) {
                break;              //  能
            }
            
            //            不能
            heap[c/2] = heap[c];    //  将孩子上移
            c *= 2;                 //  下移一层
        }
        
        heap[c/2] = y;
    }
}

template<class T>
void MinHeap<T>::Output()
{
    for (int i=1; i<=CurrentSize; i++) {
        cout << heap[i].weight << " ";
    }
}


template<class T>
class Huffman {
    friend BinaryTree<int> HuffmanTree(T [], int);
    
public:
    operator T() const { return weight;}
    
//private:
    BinaryTree<int> tree;
    T weight;
};

template<class T>
BinaryTree<int> HuffmanTree(T a[], int n)
{
//    根据权重 a[1:n] 构造霍夫曼树
//    创建一个单节点树的数组
    T aa[n+1];
    for (int i=0; i<n; i++) {
        aa[i+1] = a[i];
    }
    
    Huffman<T> *w = new Huffman<T>[n+1];
    BinaryTree<int> z,zero;
    for (int i = 1; i <= n; i++) {
        z.MakeTree(aa[i], zero, zero);
        w[i].weight = aa[i];
        w[i].tree = z;
    }
    
//    把数组变成一个最小堆
    MinHeap<Huffman<T>> H(1);
    H.Initialize(w, n, n);
    H.Output();
    //  标记一下。这里的w的类型是Huffman，应该不能直接用w来互相比大小吧。
//    如果我用w的weight属性来建树呢。
//    如果Huffman可以直接比大小的话，w会变成一个最小堆。元素都是Huffman，H确实可以直接提元素出来合并了。
    
//    将堆中的树不断合并
    Huffman<T> x,y;
    for (int i = 1; i < n; i++) {
        H.DeleteMin(x);
        H.DeleteMin(y);
        z.MakeTree(0, x.tree, y.tree);
        x.weight += y.weight;
        x.tree= z;
        H.Insert(x);
    }
    
    H.DeleteMin(x);  //  最后的树
    delete [] w;
    return x.tree;
}

Stack<int> *sta = new Stack<int>(100);
void OutputHuffman(BinaryTreeNode<int> *bt)
{
    int x;
    if (bt) {
        if (bt->data != 0) {
            cout << bt->data << "对应的编码是: ";
            sta->Output2();
            cout << endl;
        }
        
        if (bt->LeftChild) {
            sta->Add(0);
            OutputHuffman(bt->LeftChild);
            sta->Delete(x);
        }
        
        if (bt->RightChild) {
            sta->Add(1);
            OutputHuffman(bt->RightChild);
            sta->Delete(x);
        }
    }
}

//  MARK:  二叉搜索树
template<class T>
class BSTree: BinaryTree<T> {
public:
    bool Search(const T& t, T& x) const;
    BSTree<T>& Insert(const T& t);
    BSTree<T>& Delete(const T& t);
    
    void InOrder(void(*Visit) (BinaryTreeNode<T> *u ))
    {
        InOrder(Visit, this->root );
    }
    void InOrder(void(*Visit)(BinaryTreeNode<T> *u ), BinaryTreeNode<T> *t );

    
};

template<class T>
void BSTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T> *u ), BinaryTreeNode<T> *t)
{
    //    中序遍历
    if (t) {
        InOrder(Visit, t->LeftChild);
        Visit(t);
        //        treeSize++;
        InOrder(Visit, t->RightChild);
    }
}


template<class T>
bool BSTree<T>::Search(const T& t, T& x) const
{
//    搜索与k匹配的元素
//    指针p从树根开始进行查找
    BinaryTreeNode<T> *p = this->root;
    while (p) {
        if (t < p->data) {
            p = p->LeftChild;
        }
        else if (t > p->data)
            p = p->RightChild;
        else {
            x = p->data;
            return true;
        }
    }
    return false;
}

template<class T>
BSTree<T>& BSTree<T>::Insert(const T& t)
{
    BinaryTreeNode<T> *p = this->root, *pp=0;
    
    while (p) {
        pp = p;
        if (t <= p->data) {
            p = p->LeftChild;
        }
        else if (t > p->data)
            p = p->RightChild;
        else{
//            throw BadInput();
        }
    }
    
    BinaryTreeNode<T> *r = new BinaryTreeNode<T>(t);
    if (this->root) {
        if (t < pp->data) {
            pp->LeftChild = r;
        }
        else
            pp->RightChild = r;
    }
    else
        this->root = r;
    
    return *this;
}

//  MARK:  实验6main方法

//#include "shiyan7.h"
//
//int main()
//{
//    //    int t[5] = {3,5,2,1,4};
//    int a;
//    
//    int treesiz;
//    cout << "输入堆/树的大小: " << endl;
//    cin >> treesiz;
//    int *treenodes = new int[treesiz];
//    
//    cout << "输入堆/树中的各个元素: " << endl;
//    for (int i=0; i<treesiz; i++) {
//        cin >> treenodes[i];
//    }
//    MaxHeap<int> *mh = new MaxHeap<int>(30);
//    
//    mh->Initialize(treenodes , treesiz, 30);
//    
//    cout << "初始化出的最大堆: " << endl;
//    mh->Output();
//    cout << endl;
//    
//    cout << "初始化出的二叉搜索树: " << endl;
//    BSTree<int> *bst = new BSTree<int>();
//    for (int i=0; i<treesiz; i++) {
//        bst->Insert(treenodes[i]);
//    }
//    bst->InOrder(ct );
//    cout << endl;
//    
//    cout << "初始化出的霍夫曼编码:" << endl;
//    BinaryTree<int> test = HuffmanTree(treenodes , treesiz);
//    cout << endl;
//    OutputHuffman(test.root);
//    
//    cout << "输入最大堆中要删除的元素: " << endl;
//    cin >> a;
//    mh->Delete(a);
//    cout << "删除元素后的最大堆:" << endl;
//    mh->Output();
//    cout << endl;
//    
//    cout << "输入最大堆中要插入的元素: " << endl;
//    cin >> a;
//    mh->Insert(a );
//    cout << "插入元素后的最大堆: " << endl;
//    mh->Output();
//    cout << endl;
//    
//    
//    cout << "堆排序。输入一串数字的长度:" << endl;
//    cin >> a;
//    treenodes = new int[a];
//    cout << endl;
//    cout << "输入这些数字: " << endl;
//    for (int i=0; i<a; i++) {
//        cin >> treenodes[i];
//    }
//    HeapSort(treenodes, a);
//    
//}
#endif
