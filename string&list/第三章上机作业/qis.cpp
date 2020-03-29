//使用两个链栈模拟队列算法

#include <stack>
template <typename T>
class MockQueue
{
public:
    MockQueue();
    void push(T value)
    {
        p.push(value);
    }
    void print()
    {
        while (p.size())
        {
            q.push(p.top());
            p.pop();
        }
        while(q.size())
        {
            std::cout<<q.top()<<" ";
            q.pop();
        }
    }

private:
    stack<T> p;
    stack<T> q;

};

