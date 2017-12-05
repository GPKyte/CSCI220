#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class T> class BinarySearchTree
{
private:
  struct Node
  {
    string object;
    Node * rightChild;
    Node * leftChild;
    Node * parent;
    // This is the perameterized constructor for Node
    // big theta of constant
    Node(string newObject, Node* newRightChild = NULL, Node * newLeftChild = NULL, Node * newParent = NULL)
    {
      rightChild = newRightChild;
      parent = newParent;
      object = newObject;
      leftChild = newLeftChild;
    }
  };
  Node * head;
public:
  // this is the default constructor
  // big theta of constant
  BinarySearchTree()
  {
    head = NULL;
  }
  // this is the deconstrucor
  // big theta of n
  ~BinarySearchTree()
  {
      if(head)
      {
        Node * current = head;
        inOrderDelete(current);
      }
  }
  // this is a helper for the deconstructor
  // big theta of n
  void inOrderDelete(Node *current)
  {
    if(current != NULL)
    {
      inOrderDelete(current->leftChild);
      delete(current);
      inOrderDelete(current->rightChild);
    }
  }
  // perameter: object of type T
  // return: void
  // this function inserts a new Node in the proper place in the tree
  // big theta of log(n)
  void insert(string object)
  {
    Node* temp;
    Node* toCompare = head;
    bool flag = false;
    temp = new Node(object, NULL, NULL, NULL);
    if(head == NULL)
    {
      head = temp;
      flag = true;
    }
    while(!flag)
    {
      if(temp->object.compare(toCompare->object) <= 0)
      {
        if(toCompare->rightChild != NULL)
        {
          toCompare = toCompare->rightChild;
        }
        else
        {
          flag = true;
          temp->parent = toCompare;
          toCompare ->rightChild = temp;
        }
      }
      else
      {
        if(toCompare->leftChild != NULL)
        {
          toCompare = toCompare->leftChild;
        }
        else
        {
          flag = true;
          temp->parent = toCompare;
          toCompare->leftChild = temp;
        }
      }
    }
  }
  // perameter: string
  // return: string
  // this function searches an object in the tree and if it finds it, takes it out
  // big theta of log(n)
  string find(string t)
  {
    if(head == NULL)
    {
      return " ";
    }
    else if(t == head->object)
    {
      string s = takeOut(head);
      return s;
    }
    else
    {
      bool flag = false;
      Node* toCompare = head;
      while(!flag)
      {
        if(t.compare(toCompare->object) == 0)
        {
          string s = takeOut(toCompare);
          flag = true;
          return s;
        }
        else if(t.compare(toCompare->object) > 0)
        {
          if(toCompare->leftChild != NULL)
          {
            toCompare = toCompare->leftChild;
          }
          else
          {
            flag = true;
            return " ";
          }
        }
        else
        {
          if(toCompare->rightChild != NULL)
          {
            toCompare = toCompare->rightChild;
          }
          else
          {
            flag = true;
            return " ";
          }
        }
      }
    }
  }
  // perameter: Node
  // return: string
  // this function takes an object value and replaces it with another object value that keeps the tree a binary search tree
  // big theta of log(n)
  string takeOut(Node *toCompare)
  {
    if(!head)
    {
      throw(1);
    }
    Node* replacement = toCompare;
    if(replacement->rightChild != NULL)
    {
      replacement = replacement->rightChild;
      bool flag = false;
      while(!flag)
      {
        if(replacement->leftChild != NULL)
        {
          replacement = replacement->leftChild;
        }
        else
        {
          string s = toCompare->object;
          if(replacement->parent->rightChild == replacement)
          {
            replacement->parent->rightChild =NULL;
          }
          else if(replacement->parent->leftChild == replacement)
          {
            replacement->parent->leftChild = NULL;
          }
          toCompare->object = replacement->object;
          delete(replacement);
          return s;
          flag = true;
        }
      }
    }
    else if(replacement->leftChild != NULL)
    {
      replacement = replacement->leftChild;
      bool flag = false;
      while(!flag)
      {
        if(replacement->rightChild != NULL)
        {
          replacement = replacement->rightChild;
        }
        else
        {
          string s = toCompare->object;
          if(replacement->parent->rightChild == replacement)
          {
            replacement->parent->rightChild =NULL;
          }
          else if(replacement->parent->leftChild == replacement)
          {
            replacement->parent->leftChild = NULL;
          }
          toCompare->object = replacement->object;
          delete(replacement);
          return s;
          flag = true;
        }
      }
    }
    else
    {
      if(toCompare == head)
      {
        head = NULL;
      }
      string s = toCompare->object;
      if(replacement->parent->rightChild == toCompare)
      {
        replacement->parent->rightChild = NULL;
      }
      else
      {
        replacement->parent->leftChild = NULL;
      }
      delete(toCompare);
      return s;
    }
  }
  // perameter: None
  // Return: void
  // this function prints out the contents of the tree
  // big theta of n
  void print(string lista)
  {
    Node* current;
    current = head;
    cout << "The elements that are only in " << lista << " are:" << endl;
    inOrderPrint(current);
    cout << endl;
  }
  // perameter: Node
  // Return: None
  // this function helps print out the tree inorder
  // big theta of n
  void inOrderPrint(Node *current)
  {
    if(current != NULL)
    {
      inOrderPrint(current->leftChild);
      cout << current->object << endl;
      inOrderPrint(current->rightChild);
    }
  }
};
