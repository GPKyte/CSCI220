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
    size++;
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
