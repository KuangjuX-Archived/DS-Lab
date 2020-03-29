#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <functional>
#include "string.cpp"
#include "Array.cpp"
#include "spares-matrix.cpp"
#include "CrossLinkedList.cpp"

using namespace std;
int main()
{
    /*TSMatrix *M, *N, *T, *TT;
    M = CreateSMatrix();
    N = CreateSMatrix();
    std::cout << "matrix M:" << std::endl;
    PrintSMatrix(M);
    std::cout << "matrix N:" << std::endl;
    PrintSMatrix(N);

    T = AddSMatrix(M, N);
    std::cout << "T=M+N:" << std::endl;
    PrintSMatrix(T);

    TT = TransposeSMatrix(T);
    std::cout << "Transpose of matrix T:" << std::endl;
    PrintSMatrix(TT);

    return 0;*/

    /*Array A;
    int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2; //a[3][4][2]数组
    ElemType e,*p1;
    InitArray(&A,dim,bound1,bound2,bound3); //构造3＊4＊2的3维数组A
    p=A.bounds;
    printf("A.bounds=");
    for(i=0; i<dim; i++) //顺序输出A.bounds
        printf("%d ",*(p+i));
    p=A.constants;
    printf("\nA.constants=");
    for(i=0; i<dim; i++) //顺序输出A.constants
        printf("%d ",*(p+i));
    printf("\n%d page%d row%d column The matrix elements are as follows:\n",bound1,bound2,bound3);
    for(i=0; i<bound1; i++)
    {
        for(j=0; j<bound2; j++)
        {
            for(k=0; k<bound3; k++)
            {
                Assign(&A,i*100+j*10+k,i,j,k); // 将i*100+j*10+k赋值给A[i][j][k]
                Value(&e,A,i,j,k); //将A[i][j][k]的值赋给e
                printf("A[%d][%d][%d]=%2d ",i,j,k,e); //输出A[i][j][k]
            }
            printf("\n");
        }
        printf("\n");
    }
    p1=A.base;
    printf("A.base=\n");
    for(i=0; i<bound1*bound2*bound3; i++) //顺序输出A.base
    {
        printf("%4d",*(p1+i));
        if(i%(bound2*bound3)==bound2*bound3-1)
            printf("\n");
    }
    DestroyArray(&A);
    return 0;*/

    const char* s ="abcde";
    const char* m="hpabcdef";
    MyString *str1=new MyString();
    *str1=s;
    MyString *str2=new MyString();
    *str2=m;
    //str1->get_nextval();
    cout<<"The positon of str2 matching str1:";
    cout<<str1->match(*str2,1)<<endl;
    printf("Use KMP algorithm to match:");
    str1->get_nextval();
    cout<<str1->kmp(*str2,1);
}