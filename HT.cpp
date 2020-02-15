//Hash Table
#include <vector>
#include <list>
#include <iostream>
#include <adoctint.h>
using namespace std;
template <typename HashedObj>//泛型
/*class HashTable//分离链接法
{
private:
    template <typename Key>
    class hash
    {
    public:
        std::size_t operator() (const Key & key) const//哈希函数
        {
            std::size_t hashVal=0;
            for(char ch:key)
                hashVal=37*hashVal+ch;
            return hashVal;
        }
    };
    std::vector<std::list<HashedObj> > theLists;//链表的数组
    int currentSize;

    void rehash()//再散列
    {
        vector<list<HashedObj> >oldLists=theLists;

        //创建两倍大的空表
        theLists.resize(nextPrime(2*theLists.size()));
        for(auto & thisLists:thisLists)
            thisLists.clear();

        //复制整个表
        currentSize=0;
        for(auto & thisList:oldLists)
            for(auto & x:thisList)
                insert(std::move(x));
    }
    std::size_t myHash(const HashedObj & x) const//散列
    {
        static hash<HashedObj> hf;
        return hf(x)%theLists.size();
    }
public:
HashTable()//初始化
{int size=101;};

bool contains(const HashedObj & x) const//查看哈希表中是否存在该对象
{
    auto & whichList=theLists[myHash(x)];//查找对应的链表
    return find(begin(whichList),end(whichList),x)!=end(whichList);
}

void makeEmpty()
{
    for(auto & thisLists:theLists)
    {
        this->clear();
    }
}

bool insert(const HashedObj & x)
{

    auto & whichList=theLists[myHash(x)];
    if(find(begin(whichList),end(whichList),x)!=end(whichList))
        return false;

    whichList.push_back(x);

    if(++currentSize>theLists.size())
        rehash();

    return true;
}
bool insert(HashedObj && x)
{}
bool remove(const HashedObj & x)
{

    auto whichList=theLists[myHash(x)];
    auto itr=find(begin(whichList),end(whichList),x);

    if(itr==end(whichList))
        return false;

    whichList.erase(itr);
    --currentSize;
    return true;
}


};*/

template <typename HashedObj>
class HashTable
{
private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj & e=HashedObj{},EntreType i=EMPTY)
        :element{e},info{i}{}
        HashEntry(HashedObj &&e,HashEntry i=EMPTY)
        :element{std::move(e)},info{i}{}
    };

    vector<HashEntry>array;

    int currentSize;

    template <typename Key>
    class hash
    {
    public:
        std::size_t operator() (const Key & key) const//散列函数
        {
            std::size_t hashVal=0;
            for(char ch:key)
                hashVal=37*hashVal+ch;
            return hashVal;
        }
    };

    bool isActive(int currentPos) const;//判断此位置是否处于ACTIVE状态
    {
        return array[currentPos].info==ACTIVE;
    };

    int findPos(const HashedObj & x) const//探测
    {
        int offest=1;
        int currentPos=myhash(x);

        while(array[currentPos].info!=EMPTY&&array[currentPos].element!=x)
        {
            currentPos+=offest;//计算第一次探测
            offest+=2;
            if(currentPos>=array.size())
                currentPos-=array.size();
        }
        return currentPos;
    };

    void rehash()//再散列
    {
        vector<HashEntry> oldArray=array;

        //创建两倍大小的空表
        array.resize(nextPrime(2*oldArray.size()));
        for(auto & entry:array)
            entry.info=EMPTY;

        //复制整个表
        currentSize=0;
        for(auto & entry:oldArray)
            if(entry.info==ACTIVE)
                insert(std::move(entry.element));
    };

    size_t myhash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x)%theLists.size();
    };

public:
    explicit HashTable{int size=101}:array(nextPrime(size))
    {makeEmpty();};

    bool contains(const HashedObj & x) const
    {
        return isActive(findPos(x));
    };

    void makeEmpty()
    {
        currentSize=0;
        for(auto & entry:array)
            entry.info=EMPTY;
    };

    bool insert(const HashedObj & x)
    {
        //将x作为active插入
        int currentPos=findPos(x);
        if(isActive(currentPos))
            return false;

        array[currentPos].element=x;
        array[currentPos].info=ACTIVE;

        //再散列
        if(++currentSize>array.size()/2)
            rehash();

        return true;
    };

    bool remove(const HashedObj & x)
    {
        int currentPos=findPos(x);
        if(!isActive(currentPos))
            return false;

        array[currentPos].info=DELETE;
        return true;
    };

    enum EntryType{ACTIVE,EMPTY,DELETE};//枚举状态


};