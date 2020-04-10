#include <queue>
#include <algorithm>
#include <iostream>
template <typename Key,typename Value>
class BST
{
private:
    struct Node
    {
        Key key;//键
        Value value;//值
        Node *left;Node *right;//左子树、右子树
        int N;//节点数
        Node(Key key,Value value,int N)//初始化
        {
            this->key=key;
            this->value=value;
            this->N=N;
            this->left= nullptr;
            this->right= nullptr;
        }
    };

    Node *root;//根节点

    int size(Node *x)//返回节点总节点数
    {
        if(x== nullptr)return 0;
        else return x->N;
    }

    void PrePut(Node*& x,Key* key,Value* value,int i,int size)//输入二叉树的先序序列，生成二叉树的二叉链表
    {
        if(i==size)return;
        if(x== nullptr)x=new Node(key[i],value[i],1);
        //printf("%c ",'h');
        //i++;
        //PrePut(x->left,key,value,i,size);
        //PrePut(x->right,key,value,i,size);
        if(x->left== nullptr)
        {PrePut(x->left,key,value,++i,size);}
        else{
            PrePut(x->right,key,value,++i,size);
        }
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

    Node* put(Node *x,Key key,Value value)
    {
        //如果key存在以x为根节点的子树中则更新它的值，否则创建新节点
        if(x== nullptr)return new Node(key,value,1);
        if(key<x->key)x->left=put(x->left,key,value);
        else if(key>x->key)x->right=put(x->right,key,value);
        else x->value=value;
        x->N=size(x->left)+size(x->right)+1;
        return x;
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

    Node* deleteMin(Node* x)//删除最小节点
    {
        if(x->left== nullptr)return x->right;
        x->left=deleteMin(x->left);
        x->N=size(x->left)+size(x->right)+1;
        return x;
    }

    Node* deleteMax(Node* x)//删除最大节点
    {
        if(x->right== nullptr)return x->left;
        x->right=deleteMin(x->right);
        x->N=size(x->left)+size(x->right)+1;
        return x;
    }

    Node* Delete(Node *x,Key key)//删除给定节点
    {
        if(x== nullptr)return nullptr;
        if(key<x->key)x->left=Delete(x->left,key);
        else if(key>x->key)x->right=Delete(x->right,key);
        else
        {
            if(x->right== nullptr)return x->left;
            if(x->left== nullptr)return x->right;
            Node *t=x;
            x=min(t->right);
            x->right=deleteMin(t->right);
            x->left=t->left;
        }

        x->N=size(x->left)+size(x->right)+1;
        return x;

    }

    void print(Node *x)//按顺序打印二叉查找树的所有键
    {
        using namespace std;
        if(x== nullptr)return;
        cout<<x->key<<" ";
        print(x->left);
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

    int depth(Node *x)//求树的深度
    {
        if(x== nullptr)return 0;

        int LeftDepth=depth(x->left);
        int RightDepth=depth(x->right);
        return (((LeftDepth>RightDepth)?LeftDepth:RightDepth)+1);

    }


    int LeafNum(Node* x)
    {
        int num1,num2;
        if(x== nullptr)return 0;
        else if(x->left== nullptr&&x->right== nullptr)return 1;
        else{
            num1=LeafNum(x->left);
            num2=LeafNum(x->right);
            return (num1+num2);
        }
    }

public:
    BST(){root= nullptr;};//构造函数

    int size()
    {return size(root);}

    void PrePut(Key* key,Value* value,int i,int size)
    {
       PrePut(root,key,value,i,size);
    }

    Value get(Key key)
    { return get(root,key);}

    void put(Key key,Value value)
    {
        root=put(root,key,value);
    }

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
    {root=deleteMin(root);}

    void deleteMax()
    {root=deleteMax(root);}

    void Delete(Key key)
    {root=Delete(root,key);}



    void PreOrder()
    {PreOrder(root);}

    void InOrder()
    {InOrder(root);}

    void PostOrder()
    {PreOrder(root);}

    void print()
    {print(root);}

    int depth()
    {
        return depth(root);
    }

    int LeafNum()
    {
        return LeafNum(root);
    }

    typedef std::queue<Key> iterator;

    iterator keys()
    { return keys(min(),max());}

    iterator keys(Key lo,Key hi)//返回在节点序号为lo,hi之间queue
    {
        std::queue<Key> queue=new std::queue<Key>();
        keys(root,queue,lo,hi);
        return queue;
    }

    ~BST(){};//析构函数
};
