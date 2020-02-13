//Red Black Tree
#include <iostream>
#include <queue>
template <typename Key,typename Value>
class RBT
{
private:
    struct Node
    {
        Key key;//键
        Value value;//值
        Node *left;Node *right;//左子树、右子树
        int N;//节点数
        bool color;//颜色
        Node(Key key,Value value,int N,bool color)//初始化
        {
            this->key=key;
            this->value=value;
            this->N=N;
            this->color=color;
            this->left= nullptr;
            this->right= nullptr;
        }
    };

    Node *root;//根节点

    const bool RED=true;//红色
    const bool BLACK= false;//黑色

    int size(Node *x)//返回节点总节点数
    {
        if(x== nullptr)return 0;
        else return x->N;
    }

    bool isRed(Node *x)//判断一个节点和它的父节点之间的链接的颜色
    {
        if(x== nullptr)return false;
        else return x->color==RED;
    }

    Node* rotateLeft(Node *h)//左旋转
    {
        Node *x=h->right;
        h->right=x->left;
        x->left=h;
        x->color=h->color;
        h->color=RED;
        x->N=h->N;
        h->N=size(h->left)+size(h->right)+1;
        return x;
    }

    Node* rotateRight(Node* h)//右旋转
    {
        Node* x=h->left;
        h->left=x->right;
        x->right=h;
        x->color=h->color;
        h->color=RED;
        x->N=h->N;
        h->N=1+size(h->left)+size(h->right);
        return x;
    }

    /*void flipColors(Node *h)//插入操作颜色转换
    {
        h->color=RED;
        h->left->color=BLACK;
        h->right->color=BLACK;
    }

    void __flipColors(Node *h)//删除操作颜色转换
    {
        h->color=BLACK;
        h->left->color=RED;
        h->right->color=RED;
    }*/

    void flipColor(Node *h)//颜色转换
    {
        h->color=!h->color;
        h->left->color=!h->left->color;
        h->right->color=!h->right->color;
    }

    Node *put(Node *h,Key key,Value value)//如果key存在以x为根节点的子树中则更新它的值，否则创建新节点
    {
        if(h== nullptr)return new Node(key,value,RED);

        if(key<h->key) h->left=put(h->left,key,value);
        else if(key>h->key) h->right=put(h->right,key,value);
        else h->value=value;

        if(isRed(h->right)&&!isRed(h->left)) h=rotateLeft(h);
        if(isRed(h->left)&&isRed(h->left->left)) h=rotateRight(h);
        if(isRed(h->left)&&isRed(h->right)) flipColors(h);

        h->N=size(h->left)+size(h->right)+1;

        return h;
    }

    Value get(Node *x,Key key)//获取给定节点的值
    {
        if(x== nullptr)return NULL;
        else
        {
            if(key<x->key)return get(x->left,key);
            else if(key>x->key)return get(x->right,key);
            else return x->value;
        }
    }

    Node* min(Node *x)//返回键最小的节点
    {
        if(x->left== nullptr)return x;
        else return min(x->left);
    }

    Node* max(Node *x)//返回键最大的节点
    {
        if(x->right== nullptr)return x;
        else return max(x->right);
    }

    Node* floor(Node *x,Key key)//返回小于给定key的最大节点
    {
        if(x== nullptr)return nullptr;
        if(x->key==key)return x;
        else if(x->key<key)return floor(x->left,key);
        Node *t=floor(x->right,key);
        if(t!= nullptr)return t;
        else return x;

    }

    Node* ceiling(Node* x,Key key)//返回大于给定key的最小节点
    {
        if(x== nullptr)return nullptr;
        if(x->key==key)return x;
        else if(x->key>key)return ceiling(x->right,key);
        Node *t=ceiling(x->left,key);
        if(t!= nullptr)return t;
        else return x;
    }

    Node* select(Node *x,int k)//返回给定排名为k的节点
    {
        if(x== nullptr)return nullptr;
        int t=size(x->left);
        if(t>k) return select(x->left,k);
        else if(t<k) return select(x->right,k-t-1);
        else return x;
    }

    int rank(Key key,Node *x)//返回给定节点的排名
    {
        if(x== nullptr)return 0;
        if(key<x->key)return rank(key,x->left);
        else if (key>x->key)return 1+size(x->left)+rank(key,x->right);
        else return size(x->left);
    }

    /*Node* moveRedLeft(Node *h)
    {
        flipColors(h);
        if(isRed(h->right->left))
        {
            h->right=rotateRight(h->right);
            h=rotateLeft(h);
        }
        return h;
    }*/

    Node* moveRedLeft(Node* h)
    {
        flipColor(h);
        if(isRed(h->right->left))
        {
            h->right=rotateRight(h->right);
            h=rotateLeft(h);
            flipColor(h);
        }
    }


    Node* balance(Node *h)
    {
        if(isRed(h->right))h=rotateRight(h);
        //if(isRed(h->right)&&!isRed(h->left)) h=rotateLeft(h);
        if(isRed(h->left)&&isRed(h->left->left)) h=rotateRight(h);
        if(isRed(h->left)&&isRed(h->right)) flipColors(h);

        h->N=size(h->left)+size(h->right)+1;
        return h;
    }

    Node* deleteMin(Node *h)
    {
        if(h->left== nullptr)return nullptr;
        if(!isRed(h->left)&&!isRed(h->left->left))
            h=moveRedLeft(h);
        h->left=deleteMin(h->left);
        return balance(h);
    }

    /*Node* moveRedRight(Node *h)
    {
        flipColors(h);
        if(!isRed(h->left->left))
            h=rotateRight(h);
        return h;
    }*/

    Node* moveRedRight(Node* h)
    {
        flipColor(h);
        if(isRed(h->left->left))
        {
            h=rotateRight(h);
            flipColor(h);
        }
        return h;
    }

    Node* deleteMax(Node *h)
    {
        if(isRed(h->left))
            h=rotateRight(h);
        if(h->right== nullptr)
            return nullptr;
        if(!isRed(h->right)&&!isRed(h->right->left))
            h=moveRedLeft(h);
        h->right=deleteMin(h->right);
        return balance(h);
    }

    Node* Delete(Node* h,Key key)
    {
        if(key<h->key<0)
        {
            if(!isRed(h->left)&&!isRed(h->left->left))
                h=moveRedLeft(h);
            h->left=Delete(h->left,key);

        }
        else
        {
            if(isRed(h->left))
                h=rotateRight(h);
            if(key==h->key&&(h->right== nullptr))
                return nullptr;
            if(!isRed(h->right)&&!isRed(h->right->left))
                h=moveRedRight(h);
            if(key==h->key)
            {
                h->value=get(h->right,min(h->right)->key);
                h->key=min(h->right)->key;
                h->right=deleteMin(h->right);
            }
            else h->right=Delete(h->right,key);
        }
        return balance(h);
    }

    void print(Node *x)//按顺序打印二叉查找树的所有键
    {
        using namespace std;
        if(x== nullptr)return;
        print(x->left);
        cout<<x->key;
        print(x->right);
    }

    void keys(Node*x,std::queue<Key> queue,Key lo,Key hi)
    {
        if(x==nullptr)return;
        if(lo<x->key)keys(x->left,queue,lo,hi);
        if(lo<=x->key&&hi>=x->key)queue.push(x->key);
        if(hi>x->key)keys(x->right,queue,lo,hi);
    }

    void PreOrder(Node *x)//先序遍历
    {
        using namespace std;
        //Node *t=root;
        if(x== nullptr)return;
        cout<<x->key<<"-->"<<x->value<<endl;
        PreOrder(x->left);
        PreOrder(x->right);
    }

    void InOrder(Node *x)//中序遍历
    {
        using namespace std;
        if(x== nullptr)return;;
        InOrder(x->left);
        cout<<x->key<<"-->"<<x->value<<endl;
        InOrder(x->right);
    }

    void PostOrder(Node *x)//后序遍历
    {
        using namespace std;
        if(x== nullptr)return;
        PreOrder(x->left);
        PreOrder(x->right);
        cout<<x->key<<"--->"<<x->value<<endl;
    }

public:
    RBT(){root= nullptr;};//构造函数

    int size()
    {return size(root);}

    bool isEmpty()
    { return root->N==0;}

    void put(Key key,Value value)
    {
        root=put(root,key,value);
        root->color=BLACK;
    }

    Value get(Key key)
    { return get(root,key);}

    Key min()
    {
        return min(root)->key;
    }

    Key max()
    {
        return max(root)->key;
    }

    Key floor(Key key)
    {
        Node *x=floor(root,key);
        if(x== nullptr) return NULL;
        return x->key;
    }

    Key ceiling(Key key)
    {
        Node *x=ceiling(root,key);
        if(x== nullptr)return NULL;
        return x->key;
    }

    Key select(int k)
    {return select(root,k)->key;}

    int rank(Key key)
    {return rank(key,root);}

    void deleteMin()
    {
        if(!isRed(root->left)&&!isRed(root->right))
            root->color=RED;
        root=deleteMin(root);
        if(!isEmpty())root->color=BLACK;
    }


    void deleteMax()
    {
        if(!isRed(root->left)&&!isRed(root->right))
            root->color=RED;
        root=deleteMax(root);
        if(!isEmpty())root->color=BLACK;
    }

    void Delete(Key key)
    {
        if(!isRed(root->left)&&!isRed(root->right))
            root->color=RED;
        root=Delete(root,key);
        if(!isEmpty())root->color=BLACK;
    }

    void PreOrder()
    {PreOrder(root);}

    void InOrder()
    {InOrder(root);}

    void PostOrder()
    {PreOrder(root);}

    void print()
    {print(root);}

    typedef std::queue<Key> iterator;

    iterator keys()
    { return keys(min(),max());}

    iterator keys(Key lo,Key hi)//返回在节点序号为lo,hi之间queue
    {
        std::queue<Key> queue=new std::queue<Key>();
        keys(root,queue,lo,hi);
        return queue;
    }

    ~RBT(){};//析构函数
};
