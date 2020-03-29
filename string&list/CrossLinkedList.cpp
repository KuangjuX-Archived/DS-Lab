#include <cstdio>
#include <cstdlib>
#define maxSize 100
/*
 * Created by HarvestWu on 2018/6/1.
 */

typedef struct OLNode
{
    int row,col;                //行号和列号
    struct OLNode *right,*down; //指向右边和下边结点的指针
    float val;                  //值
}OLNode;

typedef struct CrossList
{
    OLNode *rhead,*chead;    //指向两头结点数组的指针
    int m,n,k;              //矩阵行数、列数、非零结点数
}CrossList;

int createCrossListMat(float A[][maxSize],int m,int n,int k,CrossList &M)
{
    if(M.rhead)
        free(M.rhead);
    if(M.chead)
        free(M.chead);
    M.m=m;
    M.n=n;
    M.k=k;
    if(!(M.rhead=(OLNode*)malloc(sizeof(OLNode)*m)))
        return 0;
    if(!(M.chead=(OLNode*)malloc(sizeof(OLNode)*n)))
        return 0;
    /*
     * 头结点结构体数组指针置空
     */
    for (int i = 0; i < m; ++i)
    {
        M.rhead[i].right= nullptr;
        M.rhead[i].down= nullptr;
    }
    for (int i = 0; i < n; ++i)
    {
        M.chead[i].right= nullptr;
        M.chead[i].down= nullptr;
    }
    OLNode *temp_r[maxSize];
    for (int j = 0; j < n; ++j)
    {
        temp_r[j] = &(M.chead[j]);
    }
    for (int i = 0; i < m; ++i)
    {
        OLNode *c = &(M.rhead[i]);
        for (int j = 0; j < n; ++j)
        {
            if(A[i][j]!=0)
            {
                OLNode *p = (OLNode*)malloc(sizeof(OLNode));
                p->row = i;
                p->col = j;
                p->val = A[i][j];
                p->down = nullptr;
                p->right = nullptr;
                c->right = p;
                c = p;
                temp_r[j]->down = p;
                temp_r[j]=p;
            }

        }
    }
    return 1;
}

