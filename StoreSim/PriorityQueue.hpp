#pragma once
#include "Customer.hpp"
#include <iostream>

template <class T> class PriorityQueue{
private:
  struct Node {
    Node *next;
    Node *previous;
    T value;
    // @next = NULL, this is a shorthand constructor to make NULL the default
    Node(T& value, Node *previous = nullptr, Node *next = nullptr) : value(value) {
      this->previous = previous;
      this->next = next;
    }
  };
  Node *head;
  Node *tail;

public:
  int size;
  PriorityQueue() {
    head = tail = nullptr;
    size = 0;
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
      head = tail = new Node(value, nullptr, nullptr);
      size++;
      return;
    }
    // Find place to insert, at tail, head, or body
    if(value < head->value) { // Insert before head
      head = new Node(value, nullptr, head);
      head->next->previous = head;
    } else if(value >= tail->value) { // Append to tail
      tail->next = new Node(value, tail, nullptr);
      tail = tail->next;
    } else { // Insert in the middle
      Node *body = head->next;
      while(body->value < value) {
        body = body->next;
      }
      body->previous = body->previous->next = new Node(value, body->previous, body);
    }
    size++;
  }
  T dequeue() {
    if (!size)
      throw("EmptyQueueException");
    // Note: not sure if tail needs to be handled on size==1 case
    // since it will be replaced on enqueue anyway
    Node *tmp = head;
    T value = head->value;
    head = head->next;
    delete(tmp);
    size--;
    return value;
  }
};
