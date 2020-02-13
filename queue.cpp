//queue
#include <iostream>
using namespace std;
template <typename T>
class Queue
{
private:
    struct Node//节点定义
    {
        T value;
        Node *next;
        Node(T x)//初始化
        {
            this->value=x;
            this->next= nullptr;
        }
    };
    Node *first;//指向最早添加节点的链接
    Node *last;//指向最近添加节点的链接
    int theSize;

    /*init()
    {
        theSize=0;
        first=new Node;
        last=first;
    }*/
public:
    Queue()
    {first=last= nullptr;theSize=0;};

    bool isEmpty()
    {return theSize==0;}

    int size()
    {return theSize;}

    void enqueue(T x)
    {
        Node *oldlast=last;
        last=new Node(x);
        if(isEmpty())first=last;
        else oldlast->next=last;
        theSize++;
    }

    T dequeue()
    {
        T item=first->value;
        first=first->next;
        if(isEmpty())last= nullptr;
        theSize--;
        return item;
    }

    typedef Node iterator;//迭代器操作

    iterator begin()//指向最早添加链接的迭代器
    { return first;}

    iterator end()//指向最近添加链接的迭代器
    { return last;}

};