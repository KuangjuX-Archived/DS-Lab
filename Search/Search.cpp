#include <cstdio>
typedef int KeyType;
struct ElemType{
    KeyType key;
};

struct SSTable{
    ElemType* elem;//数据元素存储空间基址，0号单元留空
    int length;//表的长度
};


void Create(SSTable& ST)//创建有序表
{
   int length,key;
   scanf("%d",&length);
   ST.length=length;
   ST.elem=new ElemType[length+1];
   for(int i=1;i<=length;i++)
   {
       scanf("%d",&key);
       ST.elem[i].key=key;
   }

}


int Search_Seq(SSTable ST,KeyType key)
{
    ST.elem[0].key=key;
    int i;
    for(i=ST.length;ST.elem[i].key!=key;i--);
    return i;
}

int Search_Bin(SSTable ST,KeyType key,int& count)
{
    //int count=0;
    count=0;
    int low=1;int high=ST.length;
    while (low<=high)
    {
        count++;
        int mid=(low+high)/2;
        if(key==ST.elem[mid].key)
        {
            return mid;
        }else if(key<ST.elem[mid].key)
        {
            high=mid-1;
        } else{
            low=mid+1;
        }

    }
    return 0;
}