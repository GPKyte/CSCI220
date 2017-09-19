// Gavin Kyte
// Tue Sep 19 13:03:52 2017

#pragma once // Only include this file once when requested multiple times
#include <iostream>
using namespace std;

template <classs T> class LinkedList {
private:
  struct Node {
    Node * next;
    T value;
    // @next = NULL, this is a shorthand constructor to make NULL the default
    Node(T value, Node * next = NULL) {
      this -> next = next;
      this -> value = value;
    }
  };
  Node * head;
public:
  LinkedList() {
    head = NULL;
  }
  ~LinkedList() {
    if (head) {
      Node *lead = head -> next;
      Node *follow = head;
      while(lead) {
        delete(follow);
        follow = lead;
        lead = lead -> next;
      }
      delete(follow);
    }
  }
  void push(T v) {
    head = new Node(v, head);
  }
  T pop() {
    T item = head -> value;
    Node * temp = head;
    head = head -> next;
    delete(temp);
    return item;
  }
  void pop(T item) { // Remove this value from list
    if (!head) return;
    if (head->value == item) {
      T item = pop();
      return;
    }
    Node *lead = head->next;
    Node *follow = head;
    while (lead) {
      if (lead->value == item){
        follow->next = lead->next;
        delete lead; // Prevent mem leak
        return;
      }
      lead = lead->next;
      follow = follow->next;
    }
  }

  T get(int index) {

  }

}
