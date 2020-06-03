#include "Sort.cpp"
int main(){
    SqList L{};
    InitSqList(L);
    InsertSort(L);
    PrintSqList(L);

    SqList L1{};
    InitSqList(L1);
    BinaryInsertSort(L1);
    PrintSqList(L);

    SqList L2{};
    InitSqList(L);
    QuickSort(L);
    PrintSqList(L);

}