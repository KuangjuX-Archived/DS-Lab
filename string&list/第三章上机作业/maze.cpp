/*
 * 基于栈的迷宫求解问题
 * 迷宫以字符串形式填充
 * 这里起点以@表示,终点以*表示
 * 通路以.表示，障碍以#表示
 * */
#include <stack>
#include <cstdio>
struct Node
{
    int x;
    int y;
};
class maze
{
private:
    char tile[100][100]={
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    stack<Node> s;
    int m,n;
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,1,0,-1};

    Node start={1,1};
    Node end={8,8};

    struct SelemType
    {
        Node seat;
        int direction;
    };

public:
    maze(int m,int n)
    {
        this->m=m;
        this->n=n;

    }

    void footPrint(Node curpos)
    {
        tile[curpos.x][curpos.y]='*';
    }

    void markPrint(Node curpos)
    {tile[curpos.x][curpos.y]='@';}

    Node nextPos(Node curpos,int direction)
    {
        switch (direction)
        {
            case 1:curpos.y++;break;
            case 2:curpos.x++;break;
            case 3:curpos.y--;break;
            case 4:curpos.x--;break;
        }
        return curpos;
    }

    bool pass(Node curpos)
    {
        if(tile[curpos.x][curpos.y]==' ')
            return true;
        return false;
    }

    void add()
    {
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
            {cin>>tile[i][j];}
    }

    bool dfs()
    {
        stack<SelemType> s;
        Node curpos=start;

        do{
            if(pass(curpos))
            {
                footPrint(curpos);
                SelemType e;
                e.seat=curpos;
                e.direction=1;
                s.push(e);
                if(curpos.x==end.x&&curpos.y==end.y)return true;
                curpos=nextPos(curpos,1);
            }

            else
            {
                SelemType e=s.top();
                s.pop();
                while(e.direction==4&&!s.empty())
                {
                    markPrint(e.seat);
                    e=s.top();
                    s.pop();
                }
                if(e.direction<4)
                {
                    e.direction++;
                    s.push(e);
                    curpos=nextPos(e.seat,e.direction);
                }
            }
        }while(!s.empty());
        return false;
    }

    void printmaze()
    {
        for(int i=0;i<m;i++) {
            for (int j = 0; j < n; j++)
                printf("%c ", tile[i][j]);
            printf("\n");
        }
        printf("\n");


    }

    void printpath()
    {
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++) {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1 || tile[i][j] == '*')
                    printf("%c ", tile[i][j]);
                printf(" ");
            }
        printf("\n");
        }
        printf("\n");
    }


};
