#pragma once
#include "Customer.hpp"

class RegisterQueue{
private:
  struct Node {
    Node *next; // After previous sequentially
    Node *previous; // First in line
    Customer value;
    Node(Customer value, Node *previous = nullptr) {
      this->previous = previous;
      this->value = value;
      this->next = nullptr;
    }
  };
  Node *front;
  Node *rear;

public:
  int numberOfCustomers;
  int totalCount;
  int maxLineLength;
  double minToPay;
  double minPerItem;
  RegisterQueue(double minToPay, double minPerItem) {
    front = rear = nullptr;
    maxLineLength = numberOfCustomers = totalCount = 0;
    this->minToPay = minToPay;
    this->minPerItem = minPerItem;
  }
  // O(n) where n = # of nodes at time of deletion
  ~RegisterQueue() {
    while (front) {
      Node *next = front->next;
      delete(front);
      front = next;
    }
  }
  // O(1) since rear is updated, no searching for place to insert
  void enqueue(Customer cust) {
    totalCount++;
    if(!numberOfCustomers) { // Starting list scenario
      front = rear = new Node(cust, nullptr);
    } else {
      Node *next = new Node(cust, rear);
      rear->next = next;
      rear = next;
    }
    numberOfCustomers++;
    if(numberOfCustomers > maxLineLength)
      maxLineLength = numberOfCustomers;
  }
  // O(1) always popping off head if it exists
  Customer dequeue() {
    if (!numberOfCustomers)
      throw("QueueEmptyException");

    Node *tmp = front;
    Customer c = front->value;
    front = front->next;
    delete(tmp);
    numberOfCustomers--;
    return c;
  }
  // O(1) always
  Customer seeNext() {
    return front->value;
  }
};
