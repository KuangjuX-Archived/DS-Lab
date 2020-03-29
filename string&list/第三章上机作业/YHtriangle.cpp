#include <iostream>
#include <queue>
//using namespace std;
void YHtriangle(int n)
{
    queue<int>q;
    for(int i=0;i<2*n-1;i++)cout<<"  ";
    cout<<1<<"  "<<endl;
    q.push(1);
    int s1,s2;
    for(int i=2;i<=n;i++)
    {
        for(int k=0;k<2*n-i;k++)
            cout<<"  ";
        s1=0;
        for(int j=1;j<=i-1;j++)
        {
            s2=q.front();
            q.pop();
            cout<<s1+s2<<"  ";
            q.push(s1+s2);
            s1=s2;
        }
        cout<<1<<endl;
        q.push(1);
    }
}
