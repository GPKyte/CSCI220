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

  // Takes value and type number for future comparison
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

  // Handle nullptr exception for height calc
  int height(Node* n) {
    int heightValue = 0;
    if(n)
      heightValue = n->height;
    return heightValue;
  }

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
   */
  int diff(Node* child, Node* sibling) {
    int cHeight = 0;
    if(child)
      cHeight = child->height;

    int sHeight = 0;
    if(sibling)
      sHeight = sibling->height;

    int difference = cHeight - sHeight;
    if(difference < 0) { // Is this ever going to happen?
      difference = -1 * difference;
    }
    return difference;
  }

  void rotate(Node* parent) {
    // Determine rotation type
    Node* child;
    Node* newParent;
    if(!parent) throw(1);
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
  Node* lrRotation(Node* parent) {
    rrRotation(parent->left)->height++;
    return llRotation(parent);
  }
  Node* rlRotation(Node* parent) {
    llRotation(parent->right)->height++;
    return rrRotation(parent);
  }
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

  void showANotB(Node* parent) {
    if(!parent)
      return;
    if(parent->left) showANotB(parent->left);
    for (int count = parent->typeCounter[0] - parent->typeCounter[1]; count > 0; count--) {
      cout<<parent->value<<endl;
    }
    if(parent->right) showANotB(parent->right);
  }
  void showBNotA(Node* parent) {
    if(!parent)
      return;
    if(parent->left) showBNotA(parent->left);
    for (int count = parent->typeCounter[1] - parent->typeCounter[0]; count > 0; count--) {
      cout<<parent->value<<endl;
    }
    if(parent->right) showBNotA(parent->right);
  }
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
