/*#include <vector>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
using std::swap;
using std::vector;
template <typename DataType>

class TripleTable {
private:
    struct TripleAtom
    {
        int row; //行号
        int col; //列号
        DataType ele; //存放的数据
    };

    vector<TripleTable<DataType>> data;//存储实际的矩阵数据，自包含非零元个数
    int matrixRowNum;//矩阵行数
    int matrixColNum;//矩阵列数
    int *rowFirstNoneZeroPos;//每行第一个非零元素的起始位置，方便乘法

    void CalculateFirstNoneZeroArray()//计算每行第一个非零元下标
    {
        if (rowFirstNoneZeroPos != nullptr) {
            delete [] rowFirstNoneZeroPos;
        }

        //正式给rowFirstNoneZeroPos申请空间
        rowFirstNoneZeroPos = new int[matrixRowNum];

        int *rowlNum = new int[matrixRowNum]; //每列非零元素数量


        for (int i = 0; i < matrixRowNum; i++) {
            rowlNum[i] = rowFirstNoneZeroPos[i] = 0;
        }

        for (size_t i = 0; i < data.size(); i++) {
            ++rowlNum[data[i].row - 1];
        }

        for (int i = 1; i < matrixRowNum; i++) {
            //计算每一列第一个非零元素下标
            rowFirstNoneZeroPos[i] = rowFirstNoneZeroPos[i-1] + rowlNum[i-1];
        }

        delete [] rowlNum;
    }
public:
    TripleTable(vector<vector<DataType>> &inArray):matrixRowNum(-1),matrixColNum(-1),
    rowFirstNoneZeroPos(nullptr)
    {
        if(inArray.size()>0&&inArray[0].size()>0)
        {
            matrixColNum=int(inArray[0].size());
            matrixRowNum=int(inArray.size());

            TripleTable<DataType> tmpAtom;
            for(int i=0;i<int(inArray.size());i++)
            {
                for(int j=0;j<int(inArray[i].size());j++)
                {
                    if(inArray[i][j]!=DataType(0))
                    {
                        tmpAtom.row=i+1;
                        tmpAtom.col=j+1;
                        tmpAtom.ele=inArray[i][j];
                        data.push_back(tmpAtom);//压入
                    }
                }
            }
            CalculateFirstNoneZeroArray();
        }
    }

    ~TripleTable()
    {
        delete [] rowFirstNoneZeroPos;
        rowFirstNoneZeroPos= nullptr;
        matrixRowNum=-1;
        matrixColNum=-1;
    };

    void TransposeMatrix()//常规转置思路
    {
        TripleTable<DataType> tmpAtom;
        vector<TripleAtom> newMatrix;
        for(int i=1;i<=matrixRowNum;i++)
        {
            for(size_t j=0;j<data.size();j++)
            {
                if(data[j].col==i)
                {
                    tmpAtom.row=data[j].col;
                    tmpAtom.col=data[j].row;
                    tmpAtom.ele=data[j].ele;
                    newMatrix.push_back(tmpAtom);//压入
                }
            }
        }

        data.assign(newMatrix.begin(),newMatrix.end());//转置后的矩阵
        swap(matrixRowNum,matrixColNum);
        CalculateFirstNoneZeroArray();

    }

    void FastTransposeMatrix()//快速转置
    {
        if(matrixRowNum<=0||matrixColNum<=0)
        {
            return;
        }
        int* colNum=new int[matrixColNum];
        int* colIndex=new int[matrixColNum];

        for (int i = 0; i < matrixColNum; i++) {
            colNum[i] = colIndex[0] = 0;
        }

        for (size_t i = 0; i < data.size(); i++) {
            ++colNum[data[i].col - 1];
        }

        for (int i = 1; i < matrixColNum; i++) {
            //计算每一列第一个非零元素下标
            colIndex[i] = colIndex[i-1] + colNum[i-1];
        }

        vector<TripleAtom> newMatrix(data.size());
        TripleAtom tmpAtom;
        for (size_t i = 0; i < data.size(); i++) {

            tmpAtom.row = data[i].col;
            tmpAtom.col = data[i].row;
            tmpAtom.ele = data[i].ele;

            newMatrix[colIndex[tmpAtom.row-1]] = tmpAtom;
            ++colIndex[tmpAtom.row-1]; //矩阵下标从1开始
        }

        data.assign(newMatrix.begin(), newMatrix.end()); //转置后的矩阵
        swap(matrixRowNum, matrixColNum);

        CalculateFirstNoneZeroArray();

        delete [] colNum; delete [] colIndex;
    }

    void AddMatrix(TripleTable<DataType> &otherMatrix)//一个矩阵加上另一个矩阵
    {
        if (matrixRowNum != otherMatrix.matrixRowNum || matrixColNum != otherMatrix.matrixColNum) {
            return;
        }

        vector<TripleAtom> newMatrix;
        TripleAtom tmpAtom;

        size_t i = 0, j = 0;

        while (i < data.size() && j < otherMatrix.data.size()) {
            if (data[i].row < otherMatrix.data[j].row) {
                newMatrix.push_back(data[i]); ++i;
            }
            else if (data[i].row > otherMatrix.data[j].row) {
                newMatrix.push_back(otherMatrix.data[j]); ++j;
            }
            else if (data[i].col < otherMatrix.data[j].col) {
                newMatrix.push_back(data[i]); ++i;
            }
            else if (data[i].col > otherMatrix.data[j].col) {
                newMatrix.push_back(otherMatrix.data[j]); ++j;
            }
            else {
                tmpAtom.row = data[i].row;
                tmpAtom.col = data[i].col;
                tmpAtom.ele = data[i].ele + otherMatrix.data[j].ele;
                newMatrix.push_back(tmpAtom);
                ++i; ++j;
            }
        }

        while (i < data.size()) {
            newMatrix.push_back(data[i]); ++i;
        }

        while (j < otherMatrix.data.size()) {
            newMatrix.push_back(otherMatrix.data[j]); ++j;
        }

        data.assign(newMatrix.begin(), newMatrix.end()); //相加后的矩阵

        CalculateFirstNoneZeroArray(); //重新计算
    }

    void SubMatrix(TripleTable<DataType> &otherMatrix)//一个矩阵减去另一个矩阵
    {
        if (matrixRowNum != otherMatrix.matrixRowNum || matrixColNum != otherMatrix.matrixColNum) {
            return;
        }

        vector<TripleAtom> newMatrix;
        TripleAtom tmpAtom;

        size_t i = 0, j = 0;

        while (i < data.size() && j < otherMatrix.data.size()) {
            if (data[i].row < otherMatrix.data[j].row) {
                newMatrix.push_back(data[i]); ++i;
            }
            else if (data[i].row > otherMatrix.data[j].row) {
                tmpAtom.row = otherMatrix.data[j].row;
                tmpAtom.col = otherMatrix.data[j].col;
                tmpAtom.ele = -otherMatrix.data[j].ele;
                newMatrix.push_back(tmpAtom); ++j;
            }
            else if (data[i].col < otherMatrix.data[j].col) {
                newMatrix.push_back(data[i]); ++i;
            }
            else if (data[i].col > otherMatrix.data[j].col) {
                tmpAtom.row = otherMatrix.data[j].row;
                tmpAtom.col = otherMatrix.data[j].col;
                tmpAtom.ele = -otherMatrix.data[j].ele;
                newMatrix.push_back(tmpAtom); ++j;
            }
            else {
                tmpAtom.row = data[i].row;
                tmpAtom.col = data[i].col;
                tmpAtom.ele = data[i].ele - otherMatrix.data[j].ele;
                newMatrix.push_back(tmpAtom);
                ++i; ++j;
            }
        }

        while (i < data.size()) {
            newMatrix.push_back(data[i]); ++i;
        }

        while (j < otherMatrix.data.size()) {
            tmpAtom.row = otherMatrix.data[j].row;
            tmpAtom.col = otherMatrix.data[j].col;
            tmpAtom.ele = -otherMatrix.data[j].ele;
            newMatrix.push_back(tmpAtom); ++j;
        }

        data.assign(newMatrix.begin(), newMatrix.end()); //相减后的矩阵

        CalculateFirstNoneZeroArray(); //重新计算
    }

    void MultiMatrix(TripleTable<DataType> &otherMatrix)//乘上另一个矩阵
    {
        if (matrixColNum != otherMatrix.matrixRowNum) {
            return;
        }
        if (data.size() <= 0 || otherMatrix.data.size() <= 0) {
            //如果有全零矩阵则相乘结果也是一个全零矩阵
            data.clear(); return;
        }

        DataType *tmpAccumulate = new int[otherMatrix.matrixColNum]; //记录每行各列的累加和

        vector<TripleAtom> newMatrix;
        //一行一行处理
        for (int i = 0; i < matrixRowNum; i++) {
            for (int j = 0; j < otherMatrix.matrixColNum; j++) {
                tmpAccumulate[j] = DataType(0); //清空累加器
            }

            //行开始的地方
            int rowBegin = rowFirstNoneZeroPos[i];
            //行结束的地方
            int rowEnd = i >= matrixRowNum-1 ? int(data.size()) : rowFirstNoneZeroPos[i+1];

            for (int j = rowBegin; j < rowEnd; j++) {
                //(m,n)*(n,k)矩阵的行,列对应下标相等才乘
                int middleIndex = data[j].col - 1;
                int anotherRowBegin = otherMatrix.rowFirstNoneZeroPos[middleIndex];
                int anotherRowEnd = middleIndex >= otherMatrix.matrixRowNum-1 ? int(otherMatrix.data.size()) : otherMatrix.rowFirstNoneZeroPos[middleIndex+1];
                for (int k = anotherRowBegin; k < anotherRowEnd; k++) {
                    tmpAccumulate[otherMatrix.data[k].col -1] += data[j].ele * otherMatrix.data[k].ele;
                }
            }

            //逐行压缩
            TripleAtom tmpAtom;
            for (int j = 0; j < otherMatrix.matrixColNum; j++) {
                if (tmpAccumulate[j] != DataType(0)) {
                    tmpAtom.row = i+1; //下标从1开始
                    tmpAtom.col = j+1; //下标从1开始
                    tmpAtom.ele = tmpAccumulate[j];
                    newMatrix.push_back(tmpAtom);
                }
            }
        }

        //修改列数
        matrixColNum = otherMatrix.matrixColNum;
        data.assign(newMatrix.begin(), newMatrix.end()); //相乘后的矩阵

        CalculateFirstNoneZeroArray(); //重新计算

        delete [] tmpAccumulate;
    }

    vector<vector<DataType>> TransformTo2DArray()//转换成二维数组
    {

    }

    void PrintMatrix()//打印矩阵
    {
        vector<vector<DataType>> result = TransformTo2DArray();

        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                cout << result[i][j] << ";";
            }
            cout << endl;
        }
    }


};
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#define ElemType int        //矩阵数据类型

#define OK 0                //操作成功执行
#define ERROR -1            //操作失败
#define OVERFLOW -2         //溢出
typedef int Status;

#define MAXSIZE 12000       //最大非零元数

typedef struct Triple {     //三元组
    int i, j;               //行列下标
    ElemType e;             //非零元元素值
}Triple;
typedef struct TSMatrix {       //矩阵
    Triple data[MAXSIZE + 1];   //三元组表
    int mu, nu, tu;             //矩阵的行列数、非零元个数
}TSMatrix;

TSMatrix *CreateSMatrix();                                  //1.创建
Status DestroySMatrix(TSMatrix *M);                         //2.销毁
Status PrintSMatrix(TSMatrix *M);                           //3.打印
Status CopySMatrix(TSMatrix *M, TSMatrix *T);               //4.复制
Status AddSMatrix(TSMatrix *M, TSMatrix *N, TSMatrix *Q);       //5.矩阵求和
Status SubtSMatrix(TSMatrix *M, TSMatrix *N, TSMatrix *Q);  //6.矩阵求差
Status MultSMatrix(TSMatrix *M, TSMatrix *N, TSMatrix *Q);  //7.矩阵相乘
Status TransposeSMatrix(TSMatrix *M, TSMatrix *T);          //8.矩阵转置

TSMatrix *CreateSMatrix()                                   //1.创建
{
    TSMatrix *M;
    M = (TSMatrix *)malloc(sizeof(TSMatrix));
    std::cout << "\n"
                 "Please enter the number of rows, columns, and non-zero elements of the matrix:";
    std::cin >> M->mu >> M->nu >> M->tu;
    for (int i = 0; i < M->tu; i++)
    {
        std::cout << "Please Enter the serial of number" << i + 1 << "Non-zero element row index, column index, element value:";
        std::cin >> M->data[i].i >> M->data[i].j >> M->data[i].e;
    }
    return M;
}
Status DestroySMatrix(TSMatrix *M)                          //2.销毁
{
    return OK;
}
Status PrintSMatrix(TSMatrix *M)                                //3.打印
{
    int i, j, t, flag;
    for (i = 0; i < M->mu; i++)
    {
        for (j = 0; j < M->nu; j++)
        {
            flag = 0;
            for (t = 0; t < M->tu; t++)
            {
                if (i == M->data[t].i&&j == M->data[t].j)       //非零元
                {
                    std::cout << M->data[t].e << " ";
                    t++;
                    flag = 1;
                }
            }
            if (flag == 0)std::cout << 0 << " ";
        }
        std::cout << std::endl;
    }
    return OK;
}
Status CopySMatrix(TSMatrix *M, TSMatrix *T)                    //4.复制
{
    return OK;
}
TSMatrix *AddSMatrix(TSMatrix *M, TSMatrix *N)      //5.矩阵求和
{
    TSMatrix *Q;
    Q = (TSMatrix *)malloc(sizeof(TSMatrix));
    int i, j, tm = 0, tn = 0, tq = 0;
    if (M->mu != N->mu || M->mu != N->nu)
    {
        std::cout << "The numbers of rows and columns of the two matrices are not equal and cannot be summed!";
        return NULL;
    }
    Q->mu = M->mu;
    Q->nu = M->nu;
    for (i = 0; i < M->mu; i++)
    {
        for (j = 0; j < M->nu; j++)
        {
            if ((i == M->data[tm].i&&j == M->data[tm].j) && !(i == N->data[tn].i&&j == N->data[tn].j))          //M为非零元
            {
                Q->data[tq].i = i;
                Q->data[tq].j = j;
                Q->data[tq].e = M->data[tm].e;
                tm++;
                tq++;
            }
            else if (!(i == M->data[tm].i&&j == M->data[tm].j) && (i == N->data[tn].i&&j == N->data[tn].j))     //N为非零元
            {
                Q->data[tq].i = i;
                Q->data[tq].j = j;
                Q->data[tq].e = N->data[tn].e;
                tn++;
                tq++;
            }
            else if ((i == M->data[tm].i&&j == M->data[tm].j) || (i == N->data[tn].i&&j == N->data[tn].j))      //M和N均为非零元
            {
                Q->data[tq].i = i;
                Q->data[tq].j = j;
                Q->data[tq].e = M->data[tm].e + N->data[tn].e;
                tm++;
                tn++;
                tq++;
            }
            else
            {
                ;
            }
        }
    }
    tq++;
    Q->tu = tq;
    return Q;
}
Status SubtSMatrix(TSMatrix *M, TSMatrix *N, TSMatrix *Q)       //6.矩阵求差
{
    return OK;
}
Status MultSMatrix(TSMatrix *M, TSMatrix *N, TSMatrix *Q)       //7.矩阵相乘
{
    return OK;
}
TSMatrix *TransposeSMatrix(TSMatrix *M)         //8.矩阵转置
{
    int i, j, t, t_new = 0, temp;
    TSMatrix *T;
    T = (TSMatrix *)malloc(sizeof(TSMatrix));
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;

    if (M->tu)
    {
        for (i = 0; i < M->tu; i++)
        {
            T->data[i].i = M->data[i].j;
            T->data[i].j = M->data[i].i;
            T->data[i].e = M->data[i].e;
        }
    }
    return T;
}