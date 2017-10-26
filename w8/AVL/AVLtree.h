//C++ program to Implement AVL Tree
// Editted from http://www.sanfoundry.com/cpp-program-implement-avl-trees/

#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

/*
* Node Declaration
*/
struct avl_node
{
  int data;
  struct avl_node *left;
  struct avl_node *right;
}*root;

/*
* Class Declaration
*/
class avlTree
{
public:

  avlTree()
  {
    root = NULL;
  }


  /*
  * Height of AVL Tree
  */
  int height(avl_node *temp)
  {
    int h = 0;
    if (temp != NULL)
    {
      int l_height = height (temp->left);
      int r_height = height (temp->right);
      int max_height = max (l_height, r_height);
      h = max_height + 1;
    }
    return h;
  }

  /*
  * Height Difference
  */
  int diff(avl_node *temp)
  {
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
  }

  /*
  * Right- Right Rotation
  */
  avl_node* rr_rotation(avl_node *parent)
  {
    avl_node* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
  }
  /*
  * Left- Left Rotation
  */
  avl_node* ll_rotation(avl_node *parent)
  {
    avl_node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
  }

  /*
  * Left - Right Rotation
  */
  avl_node* lr_rotation(avl_node *parent)
  {
    avl_node* temp = parent->left;
    parent->left = rr_rotation(temp);
    parent = ll_rotation(parent);
    return parent;
  }

  /*
  * Right- Left Rotation
  */
  avl_node* rl_rotation(avl_node *parent)
  {
    avl_node* temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
  }

  /*
  * Balancing AVL Tree
  */
  avl_node* balance(avl_node *temp)
  {
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
      if (diff (temp->left) > 0)
      temp = ll_rotation (temp);
      else
      temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
      if (diff (temp->right) > 0)
      temp = rl_rotation (temp);
      else
      temp = rr_rotation (temp);
    }
    return temp;
  }

  /*
  * Insert Element into the tree
  */
  avl_node* insert(avl_node *root, int value)
  {
    if (root == NULL)
    {
      root = new avl_node;
      root->data = value;
      root->left = NULL;
      root->right = NULL;
      return root;
    }
    else if (value < root->data)
    {
      root->left = insert(root->left, value);
      root = balance (root);
    }
    else if (value >= root->data)
    {
      root->right = insert(root->right, value);
      root = balance (root);
    }
    return root;
  }

  /*
  * Display AVL Tree
  */
  void display(avl_node *ptr, int level)
  {
    int i;
    if (ptr!=NULL)
    {
      display(ptr->right, level + 1);
      printf("\n");
      if (ptr == root)
      cout<<"Root -> ";
      for (i = 0; i < level && ptr != root; i++)
      cout<<"        ";
      cout<<ptr->data;
      display(ptr->left, level + 1);
    }
  }

};
