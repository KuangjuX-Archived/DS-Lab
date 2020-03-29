#include <iostream>
#include <string>
#include "stack.cpp"
#include "queue.cpp"
#include "qis.cpp"
#include "YHtriangle.cpp"
#include "train.cpp"
#include "maze.cpp"
using namespace std;

int main()
{
    /*maze*m =new maze(10,10);
    m->printmaze();
    if(m->dfs())
    {
        m->printmaze();
        m->printpath();
    }*/

    //YHtriangle(10);

    string str;
    string n = "";
    cin >> str;
    permutation(n, str);

}
