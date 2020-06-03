#include <cstdio>
#define MAXSIZE 20
typedef int KeyType;

struct RcdType{
    KeyType key;//关键字
};

struct SqList{
    RcdType r[MAXSIZE+1];
    int length;
};

void InitSqList(SqList& L){
    int length,key;
    scanf("%d",&length);
    L.length=length;
    for(int i=1;i<=length;i++){
        scanf("%d",&key);
        L.r[i].key=key;
    }
}

void PrintSqList(SqList L){
    for(int i=1;i<=L.length;i++){
        printf("%d ",L.r[i].key);
    }
    printf("\n");
}

void InsertSort(SqList& L){
    int i,j;
    for(i=2;i<=L.length;++i){
        if(L.r[i].key<L.r[i-1].key){
            L.r[0]=L.r[i];//哨兵
            for(j=i-1;L.r[0].key<L.r[j].key;j--)
                L.r[j+1]=L.r[j];
            L.r[j+1]=L.r[0];
        }
    }
}

void BinaryInsertSort(SqList& L){
    int i,j;
    for(i=2;i<=L.length;++i){
        L.r[0]=L.r[i];
        int low=1,high=i-1;
        while (low<=high){
            int m=(low+high)/2;
            if(L.r[0].key<L.r[m].key){
                high=m-1;
            } else{
                low=m+1;
            }
        }
        for(j=i-1;j>=low;--j){
            L.r[j+1]=L.r[j];
            L.r[low]=L.r[0];
        }
    }
}

int Partition(SqList& L,int low,int high){
    L.r[0]=L.r[low];
    KeyType PivotKey=L.r[low].key;
    while (low<high){
        while (low<high&&L.r[high].key>=PivotKey)--high;
        L.r[low]=L.r[high];
        while (low<high&&L.r[low].key<=PivotKey)++low;
        L.r[high]=L.r[low];
    }
    L.r[low]=L.r[0];
    return low;
}

void Qsort(SqList& L,int low,int high){
    PrintSqList(L);
    if(low<high){
        int PivotLoc=Partition(L,low,high);
        Qsort(L,low,PivotLoc-1);
        Qsort(L,PivotLoc+1,high);
    }
}

void QuickSort(SqList& L){
    Qsort(L,1,L.length);
}