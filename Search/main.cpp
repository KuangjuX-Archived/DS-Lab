#include "Search.cpp"


int main()
{
    SSTable ST{};
    Create(ST);
    printf("%d\n",Search_Seq(ST,21));
    printf("%d\n",Search_Seq(ST,85));


    int count=0;
    printf("location:%d count:%d\n",Search_Bin(ST,21,count),count);
    printf("location:%d count:%d\n",Search_Bin(ST,85,count),count);
}