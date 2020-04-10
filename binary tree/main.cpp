#include <iostream>
#include "BST.cpp"
int main() {
  BST<int,char>* tree=new BST<int,char>;
  int a[5]={1,2,3,4,5};
  char b[5]={'a','b','c','d','e'};
  tree->PrePut(a,b,0,5);
  //printf("\n");
  tree->print();
  printf("\n");
  tree->PreOrder();//先序遍历
  printf("\n");
  tree->InOrder();//中序遍历
  printf("\n");
  tree->PostOrder();//后序遍历
  printf("\n");
  printf("The depth of tree is: %d",tree->depth());//求二叉树的深度
  printf("\n");
  printf("The number of leafs is: %d",tree->LeafNum());
}