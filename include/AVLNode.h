#ifndef AVLTree_H
#define AVLTree_H
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#endif

class AVLNode {
   public:
      int key;
      int value;
      int height;

      AVLNode *left;
      AVLNode *right;

      AVLNode(int key, int value);
      void updateHeight();

      AVLNode * rightRotate();
      AVLNode * leftRotate();

      int getBalanceFactor();
      AVLNode * findMin();

      void printTree();
      
      int find(int target);
      int update(int target, int val);
};

AVLNode * deleteNode(AVLNode *root, int key);
AVLNode *insertNode(AVLNode * root, int key, int value);


