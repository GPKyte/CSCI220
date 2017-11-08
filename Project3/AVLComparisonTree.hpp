// Gavin Kyte
// Thu Nov  2 16:08:49 2017

#include <iostream>
#include <iomanip>
using namespace std;

template <class T> class ComparisonTree {
public:
  struct Node {
    Node* parent;
    Node* left;
    Node* right;
    T value;
    int height;
    static const int numTypes = 2;
    int typeCounter[2];

    Node(T value, Node* parent) {
      this->value = value;
      this->parent = parent;
      left = nullptr;
      right = nullptr;
      height = 0;
      typeCounter[0] = 0;
      typeCounter[1] = 0;
    }
  };
  Node* root;
  int size;
  ComparisonTree() {
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
    while(nomad->parent) {
      nomad->height++;
      Node* sibling = nomad->sibling();
      // balance calculated after nomad height is increased,
      // and the initial difference can't be more than 1,
      // thus the nomad is always +0, +1, or +2 relative to sibling
      int balance = diff(nomad, sibling);
      if(balance == 0) { // No change in parent's height factor
        break;
      } else if(balance == 1) { // Change parent's height
        nomad = nomad->parent;
      } else { // balance == 2
        rotate(nomad->parent);
        break;
      }
    }
    size++;
  }

  /**
   * Help method to calculate absolute value of height difference
   * requires child to be non-null Node ptr, but sibling can be null
   * returns +value which is likely 0, 1, or 2 if used correctly.
   */
  int diff(Node* child, Node* sibling) {
    int cHeight = child->height;
    int sHeight = 0;
    if(sibling) {
      sHeight = sibling->height;
    }
    int difference = cHeight - sHeight;
    if(difference < 0) { // Is this ever going to happen?
      difference = -1 * difference;
    }
    return difference;
  }

  void rotate(Node* parent) {
    // Determine rotation type
    int lHeight = parent->left->height;
    int rHeight = parent->right->height;
    Node* child;
    if(parent->left->height > parent->right->height) {
      child = parent->left;
      if(child->left->height > child->right->height)
        llRotation(parent);
      else
        lrRotation(parent);
    } else {
      child = parent->right;
      if(child->left->height > child->right->height)
        rlRotation(parent);
      else
        rrRotation(parent);
    }
  }

  void llRotation(Node* parent) {
    Node* tmp = parent->left;
    tmp->parent = parent->parent;
    parent->left = tmp->right;
    tmp->right = parent;
    parent->height--;
  }
  void lrRotation(Node* parent) {

  }
  void rlRotation(Node* parent) {

  }
  void rrRotation(Node* parent) {
    Node* tmp = parent->right;
    tmp->parent = parent->parent;
    parent->right = tmp->left;
    tmp->left = parent;
    parent->height--;
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
      cout<<ptr->value<<"("<<ptr->typeCounter[0]<<","<<ptr->typeCounter[1]<<")";
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
