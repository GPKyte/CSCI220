// Gavin Kyte
// Thu Nov  2 16:08:49 2017

#include <iostream>
#include <iomanip>
using namespace std;

template <class T> class ComparisonTree {
private:
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

public:
  Node* root;
  ComparisonTree() {
    root = nullptr;
  }
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
      } else if(value == nomad->value) {
        nomad->typeCounter[type]++;
        break;
      }
    }
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
};
