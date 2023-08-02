#include "../include/AVLNode.h"

AVLNode::AVLNode(int key, int value): 
    key {key}, value{value} 
{}

void AVLNode::updateHeight() {
    height = std::max(left->height, right->height) + 1;
}

// Rotate right
AVLNode * AVLNode::rightRotate() {
    AVLNode * l = left;
    AVLNode * r2 = l->right;

    // rotate
    l->right = this;
    left = r2;

    // update height
    updateHeight();
    l->updateHeight();

    return l;
}

// Rotate left
AVLNode * AVLNode::leftRotate() {
    AVLNode * r = right;
    AVLNode * l2 = r->left;

    r->left = this;
    right = l2;
    
    updateHeight();
    r->updateHeight();

    return r;
}

// Get the balance factor of each node
int AVLNode::getBalanceFactor() {
  return left->height - right->height;
}

// Insert a node
AVLNode *insertNode(AVLNode * root, int key, int value) {
  // Find the correct postion and insert the node
  if (root == NULL)
    return (new AVLNode(key, value));
  if (key < root->key)
    root->left = insertNode(root->left, key, value);
  else if (key > root->key)
    root->right = insertNode(root->right, key, value);
  else
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->updateHeight();
  int balanceFactor = root->getBalanceFactor();
  if (balanceFactor > 1) {
    if (key < root->left->key) {
      root->rightRotate();
      return root;
    } else if (key > root->left->key) {
      root->left = root->left->leftRotate();
      return root->rightRotate();
    }
  }
  if (balanceFactor < -1) {
    if (key > root->right->key) {
      return root->leftRotate();
    } else if (key < root->right->key) {
      root->right = root->right->rightRotate();
      return root->leftRotate();
    }
  }
  return root;
}

// Node with minimum value
AVLNode * AVLNode::findMin() {
  if (left != NULL)
    return left->findMin();
  return this;
}

// Delete a node
AVLNode * deleteNode(AVLNode *root, int key) {
  // Find the node and delete it
  if ( ! root )
    return root;
  if ( key < root->key )
    root->left = deleteNode(root->left, key);
  else if ( key > root->key )
    root->right = deleteNode(root->right, key);
  else {
    if ( ! root->left || ! root->right ) {
        AVLNode *temp = root->left ? root->left : root->right;
        if (temp == NULL) {
            temp = root;
            root = NULL;
        } else {
            *root = *temp;
        }
        
        delete temp;
    } else {
        AVLNode *temp = root->right->findMin();
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
  }

  if ( ! root )
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->updateHeight();
  int balanceFactor = root->getBalanceFactor();
  if ( balanceFactor > 1 ) {
    if ( root->left->getBalanceFactor() >= 0 ) {
      return root->rightRotate();
    } else {
      root->left = root->left->leftRotate();
      return root->rightRotate();
    }
  }
  if ( balanceFactor < -1 ) {
    if ( root->right->getBalanceFactor() <= 0) {
      return root->leftRotate();
    } else {
      root->right = root->right->rightRotate();
      return root->leftRotate();
    }
  }
  return root;
}

// Print the tree
void AVLNode::printTree() {
    std::cout << this->key << this->value << std::endl;
    if ( left )
      left->printTree();
    if ( right )
      right->printTree();
}

int AVLNode::find(int target) {
  if (target < key && left)
    left->find(target);
  else if (target > key && right)
    right->find(target);
  else 
    return value;
  return INT32_MIN;
}

int AVLNode::update(int target, int val) {


    if (target < key && left)
        left->find(target);
    else if (target > key && right)
        right->find(target);
    else {
        value = val;
        return 1;
    }

    return 0;
}
