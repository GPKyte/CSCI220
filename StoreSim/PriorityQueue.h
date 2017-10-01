#pragma once
#include "Customer.h"

template <class T> class PriorityQueue{
private:
  struct Node {
    Node *next;
    Node *previous;
    Customer value;
    // @next = NULL, this is a shorthand constructor to make NULL the default
    Node(Customer value, Node *previous = nullptr, Node *next = nullptr) {
      this->previous = previous;
      this->value = value;
      this->next = next;
    }
  };
  Node *head;
  Node *tail;

public:
  int size;
  PriorityQueue() {
    head, tail = nullptr;
  }
  ~PriorityQueue() {
    while(head) {
      Node *next = head->next;
      delete(head);
      head = next;
    }
  }
  void enqueue(T value) {
    if(!size) {
      head, tail = new Node(value);
      return;
    }
    // Find place to insert, at tail, head, or body
    if(value < head->value) { // At head
      head = new Node(value, nullptr, head->next);
      head->next->previous = head;
    } else if(value >= tail->value) { // At tail
      tail = new Node(value, tail->previous, nullptr);
      tail->previous->next = tail;
    } else {
      Node *body = head->next;
      while(value >= body->value) {
        body = body->next;
      }
      body->previous, body->previous->next = new Node(value, body->previous, body);
    }
    size++;
  }
  T dequeue() {
    T value = head->value;
    head = head->next;
    delete(head->previous);
    head->previous = nullptr;
    size--;
    return value;
  }
};
