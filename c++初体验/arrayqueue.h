//
//  arrayqueue.h
//  c++初体验
//
//  Created by SXB on 15/11/11.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#ifndef c______arrayqueue_h
#define c______arrayqueue_h


#endif
template<class K>
class arrayqueue
{public:
    arrayqueue(int initialCapacity = 10);
    bool empty() const { return theFront == theBack; }
    int size() const
    {return (theBack - theFront + arrayLength) % arrayLength;}
    K & front()
    {if (theFront == theBack)
        cout << "error~~" << endl;
        return queue[(theFront + 1) % arrayLength];}
    K & back()
    {if (theFront == theBack)
        cout << "error~~" << endl;
        return queue[theBack];
    }
    void pop()
    {//删除队列首元素。
        if (theFront == theBack)
            cout << "error~~" << endl;
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~K();
    }
    void push(const K& theElement);
private:
    int theFront;
    int theBack;
    int arrayLength;
    K * queue;
};

template<class K>
arrayqueue<K>::arrayqueue(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        cout << "error~~" << endl;
    }
    arrayLength = initialCapacity;
    queue = new K[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<class K>
void arrayqueue<K>::push(const K& theElement)
{
    if ((theBack + 1) % arrayLength == theFront)//如果需要增加数组长度。
    {
        K* newQueue = new K[2 * arrayLength];
        int start = (theFront + 1) % arrayLength;
        if (start < 2)//没有形成环
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else
        { //队列形成环
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }
        //设置新的队列的首和尾的元素位置
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;
        arrayLength *= 2;
        queue = newQueue;
    }
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}





