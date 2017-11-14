// Gavin Kyte
// Thu Nov  2 16:08:49 2017

#include <iostream>
#include <iomanip>
using namespace std;

template <class T> class AVLComparisonTree {
public:
  struct Node {
    Node* parent;
    Node* left;
    Node* right;
    T value;
    int height;
    int typeCounter[2];

    Node* sibling() {
      Node* sib = nullptr;
      if(this->parent) {
        if(this->parent->value >= this->value) {
          sib = this->parent->right;
        } else {
          sib = this->parent->left;
        }
      }
      return sib;
    }
    Node(T value, Node* parent) {
      this->value = value;
      this->parent = parent;
      left = nullptr;
      right = nullptr;
      height = 1;
      typeCounter[0] = 0;
      typeCounter[1] = 0;
    }
  };
  Node* root;
  int size;
  AVLComparisonTree() {
    root = nullptr;
    size = 0;
  }

  /**
   * Take a type-specified value and insert it into tree. All values
   * represented once, and counted via type.
   * O(log(n)) where n = #nodes in tree
   */
  void insert(T value, int type) {
    if(!root) {
      root = new Node(value, nullptr);
    }
    Node* nomad = root;
    while(1) {
      if(value < nomad->value && nomad->left){
        nomad = nomad->left;
      } else if(value < nomad->value && !nomad->left){
        nomad->left = new Node(value, nomad);
      } else if(value > nomad->value && nomad->right){
        nomad = nomad->right;
      } else if(value > nomad->value && !nomad->right){
        nomad->right = new Node(value, nomad);
      } else if(value == nomad->value) { // Always last case
        nomad->typeCounter[type]++;
        break;
      }
    }
    balance(nomad);
    size++;
  }

  /**
   * Takes a newly inserted node and iterates up tree until height
   * is done changing. Rotates as needed for balance.
   * O(log(n)) worst case
   * O(1) best case
   */
  void balance(Node* nomad) {
    while(nomad) {
      int balance = diff(nomad->left, nomad->right);
      if(balance == 0) {
        updateHeight(nomad);
      } else if(balance == 1) {
        updateHeight(nomad);
      } else { // balance == 2
        rotate(nomad);
        break;
      }
      nomad = nomad->parent;
    }
  }

  /**
   * Handle nullptr exception for height calc
   * return 0 if Node doesn't exist
   * O(1) run time
   */
  int height(Node* n) {
    int heightValue = 0;
    if(n)
      heightValue = n->height;
    return heightValue;
  }

  /**
   * Height of Node will become that of its tallest child + 1
   * O(1) run time
   */
  void updateHeight(Node* parent) {
    int leftHeight = height(parent->left);
    int rightHeight = height(parent->right);
    if(leftHeight >= rightHeight) {
      parent->height = leftHeight + 1;
    } else {
      parent->height = rightHeight + 1;
    }
  }

  /**
   * Helper method to calculate absolute value of height difference
   * requires child to be non-null Node ptr, but sibling can be null
   * returns +value which is likely 0, 1, or 2 if used correctly.
   * O(1) run time
   */
  int diff(Node* child, Node* sibling) {
    int cHeight = 0;
    int sHeight = 0;
    if(child)
      cHeight = child->height;
    if(sibling)
      sHeight = sibling->height;
    int difference = cHeight - sHeight;
    if(difference < 0) {
      difference *= -1;
    }
    return difference;
  }

  /**
   * Takes a Node parent, A, such that there exists a B and C
   * that A -> B -> C as in a RR, LL, RL, or LR path
   * Runs in O(1) time
   */
  void rotate(Node* parent) {
    if(!parent) throw(1);
    Node* child;
    Node* newParent;
    if(height(parent->left) > height(parent->right)) {
      child = parent->left;
      if(height(child->left) > height(child->right))
        newParent = llRotation(parent);
      else
        newParent = lrRotation(parent);
    } else {
      child = parent->right;
      if(height(child->left) > height(child->right))
        newParent = rlRotation(parent);
      else
        newParent = rrRotation(parent);
    }
    if(parent == root)
      root = newParent;
  }

  /**
   * Takes a node and reassigns the pointers related to it's
   * parent and left child. Returns the new parent of initial node.
   * O(1) run time
   */
  Node* llRotation(Node* A) {
    Node* B = A->left;
    B->parent = A->parent;
    if(B->parent && B->value < B->parent->value) {
      B->parent->left = B;
    } else if(B->parent) {
      B->parent->right = B;
    }
    A->left = B->right;
    if(A->left)
      A->left->parent = A;
    B->right = A;
    A->parent = B;
    A->height--;
    return B;
  }
  /**
   * Takes a node and reassigns the pointers related to it's
   * parent, left child, and that childs right child.
   * Returns the new parent of initial node.
   * O(1) run time
   */
  Node* lrRotation(Node* parent) {
    rrRotation(parent->left)->height++;
    return llRotation(parent);
  }
  /**
   * Takes a node and reassigns the pointers related to it's
   * parent, right child, and that childs left child.
   * Returns the new parent of initial node.
   * O(1) run time
   */
  Node* rlRotation(Node* parent) {
    llRotation(parent->right)->height++;
    return rrRotation(parent);
  }
  /**
   * Takes a node and reassigns the pointers related to it's
   * parent, right child. Returns the new parent of initial node.
   * O(1) run time
   */
  Node* rrRotation(Node* A) {
    Node* B = A->right;
    B->parent = A->parent;
    if(B->parent && B->value < B->parent->value) {
      B->parent->left = B;
    } else if(B->parent) {
      B->parent->right = B;
    }
    A->right = B->left;
    if(A->right)
      A->right->parent = A;
    B->left = A;
    A->parent = B;
    A->height--;
    return B;
  }

  /**
   * Display tree
   * This is a recursive, visual traversal that prints from right
   * to left, with terminal-focused-"up" being tree-"right" and down being left
   * O(n) always where n = #nodes
   */
  void display(Node *ptr, int level) {
    int i;
    if(ptr!=NULL) {
      display(ptr->right, level + 1);
      printf("\n");
      if (ptr == root)
      cout<<"Root -> ";
      for (i = 0; i < level && ptr != root; i++)
      cout<<"        ";
      cout<<ptr->value<<"("<<ptr->typeCounter[0]<<","<<ptr->typeCounter[1]<<")-h:"<<ptr->height;
      display(ptr->left, level + 1);
    }
  }

  /**
   * Print all elements of type A that aren't type B
   * O(n) always where n = #nodes
   */
  void showANotB(Node* parent) {
    if(!parent)
      return;
    if(parent->left) showANotB(parent->left);
    for (int count = parent->typeCounter[0] - parent->typeCounter[1]; count > 0; count--) {
      cout<<parent->value<<endl;
    }
    if(parent->right) showANotB(parent->right);
  }
  /**
   * Print all elements of type b that aren't type A
   * O(n) always where n = #nodes
   */
  void showBNotA(Node* parent) {
    if(!parent)
      return;
    if(parent->left) showBNotA(parent->left);
    for (int count = parent->typeCounter[1] - parent->typeCounter[0]; count > 0; count--) {
      cout<<parent->value<<endl;
    }
    if(parent->right) showBNotA(parent->right);
  }
  /**
   * Print all elements of type A that are also type B
   * O(n) always where n = #nodes
   */
  void showAAndB(Node* parent) {
    if(!parent)
      return;
    if(parent->left) showAAndB(parent->left);
    for (int count = 0; count < parent->typeCounter[0] && count < parent->typeCounter[1]; count++) {
      cout<<parent->value<<endl;
    }
    if(parent->right) showAAndB(parent->right);
  }
};
