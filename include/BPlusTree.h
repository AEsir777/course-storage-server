#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include<vector>
#include <bits/stdc++.h>

template <typename T>
class BPlusTreeNode {
    BPlusTreeNode * parent;
    std::vector<BPlusTreeNode *> children;
    std::vector<std::string> keys;
    std::vector<std::tuple<T>> values;
    bool isLeaf;

    ~BPlusTreeNode() {
        if ( ! isLeaf ) {
            for ( auto child: children )
                delete child;
            }
    };

    friend class BPlusTree;
};


template <typename T>
class BPlusTree {
public:
    // Root of tree stored here;
    BPlusTreeNode<T> * root;
    BPlusTreeNode<T> * firstLeaf;
    int b;

    BPlusTree(int b): b {b} 
    {}
    
    ~BPlusTree() {
        delete root;
    }

    BPlusTreeNode * search(std::string key, int & k, int & child_pos) {
        if ( ! root ) return nullptr;

        BPlusTreeNode * current = root;
        while ( ! current->isLeaf ) {
            for ( size_t i = 0; i < children.size() - 1 ; i++ ) {
                if ( key < current->keys[i] ) {
                    current = current->children[i];
                    child_pos = i;
                    break;
                }
            }
        }

        // find Leaf
        for ( size_t i = 0; i < current->keys.size(); i++ ) {
            if ( current->keys[i] == key ) {
                k = i;
                return this;
            }
        }

        return k;
    }

    void delete(std::string key) {
        BPlusTreeNode<T>* curNode = this->root;

        // search the node
        int idx = 0;
        int child_pos = 0;
        curNode = search(key, idx, child_pos);

        // if not found
        if ( ! curNode ) return;

        // if found, delete the tuple
        curNode->keys.erase(curNode->keys.begin() + idx);

        // if curNode is root
        if ( curNode == this->root && ! curNode->keys.size() ){
            clear(this->root);
            this->root = nullptr;
            this->firstLeaf = nullptr;
            return;
        }

        if ( curNode == this->root ){
            return;
        }

        // check if causing underflow
        if ( curNode->keys.size() < b/2 ) {
            // left_sibiling exists
            if ( child_pos - 1 >= 0 ){
                BPlusTreeNode<T> * leftSibling= curNode->parent->children[child_pos - 1];

                // if leftSibling have enough keys
                if ( leftSibling->keys.size() > b/2 ) { 
                    // borrow the right most tuple to insert into curNode

                    //copy item
                    /* for(int i=0; i<curNode->size; i++){
                        temp[i]=curNode->item[i];
                    }

                    //insert and rearrange
                    item_insert(temp,leftsibling->item[leftsibling->size -1],curNode->size);
                    for(int i=0; i<curNode->size+1; i++){
                        curNode->item[i] = temp[i];
                    }
                    curNode->size++;

                    //pointer edit
                    curNode->children[curNode->keys.size] = curNode->children[curNode->size-1];
                    curNode->children[curNode->size-1] = nullptr;

                    //sibling property edit
                    leftsibling->item[leftsibling->size-1] = 0;
                    leftsibling->size--;
                    leftsibling->children[leftsibling->size] = leftsibling->children[leftsibling->size+1]; //curNode
                    leftsibling->children[leftsibling->size+1]= nullptr;

                    //parent property edit
                    curNode->parent->item[left] = curNode->item[0];

                    return;
                }
            }
            if(right <= curNode->parent->size){// right_sibiling exists
                Node<T>* rightsibling = curNode->parent->children[right];

                if(rightsibling->size >degree/2){//if data number is enough to use this node
                    T* temp = new T[curNode->size+1];

                    //copy item
                    for(int i=0; i<curNode->size; i++){
                        temp[i]=curNode->item[i];
                    }
                    //insert and rearrange
                    item_insert(temp,rightsibling->item[0],curNode->size);
                    for(int i=0; i<curNode->size+1; i++){
                        curNode->item[i] = temp[i];
                    }
                    curNode->size++;
                    delete[] temp;

                    //pointer edit
                    curNode->children[curNode->size] = curNode->children[curNode->size-1];
                    curNode->children[curNode->size-1] = nullptr;

                    //sibling property edit
                    for(int i=0; i<rightsibling->size-1;i++){
                        rightsibling->item[i] = rightsibling->item[i+1];
                    }
                    rightsibling->item[rightsibling->size-1] = 0;
                    rightsibling->size--;
                    rightsibling->children[rightsibling->size] = rightsibling->children[rightsibling->size+1]; //curNode
                    rightsibling->children[rightsibling->size+1]= nullptr;

                    //parent property edit
                    curNode->parent->item[right-1] = rightsibling->item[0];

                    return;
                }
            }

            //if sibling is not enought to use their data
            //we have to merge step

            if(left>=0){ // left_sibling exists
                Node<T>* leftsibling = curNode->parent->children[left];

                //merge two leaf node
                for(int i=0; i<curNode->size; i++){
                    leftsibling->item[leftsibling->size+i]=curNode->item[i];
                }
                //edit pointer
                leftsibling->children[leftsibling->size] = nullptr;
                leftsibling->size = leftsibling->size+curNode->size;
                leftsibling->children[leftsibling->size] = curNode->children[curNode->size];

                //parent property edit
                Removepar(curNode, left, curNode->parent);
                for(int i=0; i<curNode->size;i++){
                    curNode->item[i]=0;
                    curNode->children[i] = nullptr;
                }
                curNode->children[curNode->size] = nullptr;

                delete curNode;

                return;

            }
            if(right<=curNode->parent->size){ // right_sibiling exists
                Node<T>* rightsibling = curNode->parent->children[right];

                //merge two leaf node
                for(int i=0; i<rightsibling->size; i++){
                    curNode->item[i+curNode->size]=rightsibling->item[i];
                }
                //edit pointer
                curNode->children[curNode->size] = nullptr;
                curNode->size = rightsibling->size+curNode->size;
                curNode->children[curNode->size] = rightsibling->children[rightsibling->size];

                //parent property edit
                Removepar(rightsibling, right-1, curNode->parent);

                for(int i=0; i<rightsibling->size;i++){
                    rightsibling->item[i]=0;
                    rightsibling->children[i] = nullptr;
                }
                rightsibling->children[rightsibling->size] = nullptr;

                delete rightsibling;
                return;

            }
 */
        }
        else{
            return;
        }
    }


    void insert(std::string key) {

    }


    void printTree();
};

#endif