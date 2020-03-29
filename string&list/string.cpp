//字符串
#include <iostream>
#include <cstring>
#include <stdio.h>
class MyString
{
private:
    struct HString
    {
        char* ch;
        int length;
    };

    int* nextval;

    HString s;
public:

    MyString()
    {
        s.ch=(char*)malloc(sizeof(char)*1000);
        s.length=0;
    }

    MyString&operator= (const char* another)
    {
       if(s.ch)
       {
           free(s.ch);
           s.length=0;
       }

       s.length=std::strlen(another);
       s.ch=new char[std::strlen(another)+1];
       std::strcpy(s.ch,another);
       nextval=new int[this->s.length+1];
       return *this;
    }


    int match(MyString& str,int pos)
    {
        int i=pos-1;int j=0;
        while(i<str.s.length&&j<this->s.length)
        {
            if(str.s.ch[i]==this->s.ch[j])
            {
                ++i;
                ++j;
            }
            else{i=i-j+1;j=0;}
        }
        //std::cout<<i<<" "<<j<<std::endl;
        if(j>=this->s.length-1)return i-this->s.length+1;
        else return 0;
    }

    void get_nextval()
    {
       int i=-1,j=0;
       nextval[0]=-1;
       while(j<strlen(s.ch))
       {
           if(i==-1||s.ch[i]==s.ch[j])
           {
               ++i;++j;
               if(s.ch[i]!=s.ch[j])nextval[j]=i;
               else nextval[j]=nextval[i];
           }
           else i=nextval[i];
       }

    }

    int kmp(MyString& str,int pos)
    {
        int i=pos-1;int j=-1;
        while(i<str.s.length&&j<this->s.length)
        {
            if(j==-1||str.s.ch[i]==this->s.ch[j]){++i;++j;}
            else j=nextval[j];
        }
        if(j>=s.length-1)return i-s.length+1;
        else return 0;
    }
    void print()
    {
        for(int i=0;i<s.length;i++)
          printf("%c ",s.ch[i]);
    }


    ~MyString(){};

};
