//priority queue
#include <iostream>
template <typename T>
class PQ
{
private:
    T *pq;
    int theSize=0;

    bool less(int i,int j)
    {
        return (pq[i]<pq[j]);
    }

    void exch(int i,int j)
    {
        int t=pq[i];
        pq[i]=pq[j];
        pq[j]=t;
    }

    void swim(int k)
    {
        while(k>1&&less(k/2,k))
        {
            exch(k/2,k);
            k=k/2;
        }
    }

    void sink(int k)
    {
        while(2*k<=theSize)
        {
            int j=2*k;
            if(j<theSize&&less(j,j+1))j++;
            if(!less(k,j))break;
            exch(k,j);
            k=j;
        }
    }

   void sink(int k,int n)
   {
        while(2*k<=n)
        {
            int j=2*k;
            if(j<n&&less(j,j+1))j++;
            if(!less(k,j))break;
            exch(k,j);
            k=j;
        }
   }
public:
    PQ(int maxN)
    {int *pq=new int[maxN+1];};

    bool isEmpty()
    {return theSize==0;}

    int size()
    {return theSize;}

    void insert(T value)
    {
        pq[++theSize]=value;
        swim(theSize);
    }

    int delMax()
    {
        int max=pq[1];
        exch(1,theSize--);
        pq[theSize+1]=NULL;
        sink(1);
        return max;
    }

    int* sort()
    {
        int N=theSize;
        for(int k=N/2;k>=1;k--)
            sink(k,N);
        while(N>1)
        {
            exch(1,N--);
            sink(1,N);
        }
        return pq;
    }
    ~PQ(){};

};
