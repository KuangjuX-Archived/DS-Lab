#include <cstdio>
const int MAXVexNum=10;//最大顶点个数
typedef int VertexData;//顶点数据类型
typedef int EdgeData;//边上权值类型

/**邻接矩阵**/
struct MTGraph{
    VertexData VexList[MAXVexNum];//顶点表
    EdgeData edge[MAXVexNum][MAXVexNum];//邻接矩阵
    int n,e;//图中当前的顶点数与边数
};

void InitGraph(MTGraph &G)
{
    for(int i=0;i<MAXVexNum;i++)
        for(int j=0;j<MAXVexNum;j++)
            G.edge[i][j]=INT_MAX;
}


void CreateGraph(MTGraph &G)
{
    scanf("%d %d",&G.n,&G.e);
    for(int i=0;i<G.n;i++)
    {
        scanf("%d",&G.VexList[i]);
    }
    int tail = 0, head = 0, weight = 0;
    for(int i=0;i<G.e;i++)
    {
        scanf("%d %d %d",&head,&weight,&tail);
        G.edge[head][tail]=weight;
        //G.edge[tail][head]=INT_MAX;
    }
}

void Print(MTGraph G)
{
    int n=G.n;
    for(int i=0;i<n;i++)
    {
        EdgeData* p=G.edge[i];
        for(int j=0;j<n;j++)
        {
            if(p[j]!=INT_MAX)
            {
                printf("node:%d---->node:%d  weight:%d\n",G.VexList[i],G.VexList[j],p[j]);
            }
        }
    }
}

/**邻接表**/
//边节点
struct EdgeNode{
    int dest;//目标顶点位置
    EdgeData cost;//边的权值
    struct EdgeNode* link;//下一边链接指针
};

//顶点节点
struct VertexNode{
    VertexData  data;//顶点数据域
    EdgeNode* adj;//边链表头指针
};

//图的邻接表
struct AdjGraph{
    VertexNode VexList[MAXVexNum];//邻接表
    int n,e;//图中当前的顶点个数与边数
};

//邻接表的构造算法
void InitGraph(AdjGraph& G)
{
    for(int i=0;i<MAXVexNum;i++)
    {
        G.VexList[i]=*new VertexNode;
        G.n=0;
        G.e=0;
    }
}
void CreateGraph(AdjGraph& G)
{
    scanf("%d %d",&G.n,&G.e);//输入顶点个数和边数
    for (int i = 0; i < G.n; ++i) {
        scanf("%d",&G.VexList[i].data);
        G.VexList[i].adj=nullptr;
    }
    int tail,head,weight;
    for(int i=0;i<G.e;i++){
        scanf("%d %d %d",&head,&weight,&tail);//逐条边输入
        EdgeNode* p=new EdgeNode;
        p->dest=tail;
        p->cost=weight;
        p->link=G.VexList[head].adj;
        G.VexList[head].adj=p;
    }

}

VertexData GetValue(AdjGraph G,VertexData v)
{
    return G.VexList[v].data;
}

VertexData GetFirstNeighbor(AdjGraph G,VertexData v)
{
    return G.VexList[v].adj->dest;

}

VertexData GetNextNeighbor(AdjGraph G, VertexData v, VertexData w)
{
    EdgeNode* p=G.VexList[v].adj;
    while (p->dest!=w)
    {
        p=p->link;
    }
    p=p->link;
    return p->dest;

}

void DFS(AdjGraph G,int v,int visited[])
{
    printf("Node:%d---->",GetValue(G,v));
    visited[v]=1;
    int w=GetFirstNeighbor(G,v);
    while (w!=-1){
        if(!visited[w])
        {
            DFS(G,w,visited);
        }
        //取顶点v排在w后的下一个邻接顶点
        w=GetNextNeighbor(G,v,w);
    }
}


void Graph_Traverse(AdjGraph G)
{
    int *visited = new int[MAXVexNum];
    for(int i=0;i<G.n;i++)
        visited[i]=0;
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
            DFS(G,i,visited);
    }
    delete[] visited;
}

void Print(AdjGraph G)
{
    int n=G.n;
    int e=G.e;
    for(int i=0;i<n;i++)
    {
        printf("node:%d---->",GetValue(G,i));
        EdgeNode* p=G.VexList[i].adj;
        while (p)
        {
            printf("node:%d weight:%d  ",p->dest,p->cost);
            p=p->link;
        }
        printf("\n");
    }
}

AdjGraph TransferMTGraph(MTGraph G)
{
    AdjGraph G2;
    InitGraph(G2);
    G2.n=G.n;
    G2.e=G.e;
    for(int i=0;i<G2.n;i++)
    {
        G2.VexList[i].data=G.VexList[i];
        G2.VexList[i].adj= nullptr;
    }
    for(int i=0;i<G.n;i++)
        for(int j=0;j<G.n;j++)
        {
            if(G.edge[i][j]!=INT_MAX)
            {
                VertexData head=G.VexList[i];
                VertexData tail=G.VexList[j];
                EdgeData weight=G.edge[i][j];
                EdgeNode* p=new EdgeNode;
                p->dest=tail;
                p->cost=weight;
                p->link=G2.VexList[head].adj;
                G2.VexList[head].adj=p;
            }
        }
    return G2;
}


MTGraph TransferAdjGraph(AdjGraph G)
{
    MTGraph G2;
    InitGraph(G2);
    G2.e=G.e;
    G2.n=G.n;
    for(int i=0;i<G2.n;i++)
    {
        G2.VexList[i]=G.VexList[i].data;
    }
    for(int i=0;i<G.n;i++)
    {
        VertexData head=G.VexList[i].data;
        EdgeNode* p=G.VexList[i].adj;
        while (p)
        {
            EdgeData weight=p->cost;
            VertexData tail=p->dest;
            G2.edge[head][tail]=weight;
            p=p->link;
        }
    }
    return G2;
}