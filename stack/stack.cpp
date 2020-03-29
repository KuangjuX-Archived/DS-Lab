/*Stack*/
//链栈
#include <iostream>
template <typename T>
class Stack{
public :

    struct Node {
        T value;
        Node *next;

        Node(T value)
        {
            this->value=value;
            this->next= nullptr;
        }
    };

    Stack(){top=bottom= nullptr;theSize=0;}

    void push(T x)
    {
        if(isEmpty())
        {
            top=new Node(x);
            bottom=top;
            top->next= nullptr;
            bottom->next=nullptr;
            theSize++;
            return;
        }
        Node *oldfirst=top;
        top=new Node(x);
        top->next=oldfirst;
        theSize++;
    }

    void pop()
    {
        T item=top->value;
        top=top->next;
        theSize--;
    }

    int size() { return theSize; }

    bool isEmpty()
    {return theSize==0;}

    void print()
    {
        for(Node *p=top;p!=bottom->next;p=p->next)
            std::cout<<p->value<<std::endl;
    }

    typedef Node iterator;
    iterator begin()//指向栈底的指针
    {return bottom;}

    iterator end()//指向栈顶的指针
    {return top;}

private:
    int theSize;//栈容量
    //Node *stack;
    Node *top;//栈顶
    Node *bottom;//栈底
};

//顺序栈
template <typename T>
class SqStack
{
private:
    SqStack(int maxsiae)
    {
        base =new T[maxsiae];
        top=base;
        stacksize=0;
    }

    bool isEmpty()
    { return stacksize==0;}

    void push(T value)
    {
        if(isEmpty())
        {
            *base=value;
            stacksize++;
            return;
        }
        *(++top)=value;
         stacksize++;
    }

    void pop()
    {
        if(isEmpty())return;
        T* old=top;
        top--;
        free(old);
        stacksize--;
    }

    void print()
    {
        for(T* p=top;p>=base;p--)
        {std::cout<<*p<<" ";}
    }

    T Top()
    { return *top;}
public:
    T* base;
    T* top;
    int stacksize;

};