#pragma once
#include "Customer.hpp"

class RegisterQueue{
private:
  struct Node {
    Node *next; // After previous sequentially
    Node *previous; // First in line
    Customer value;
    // @next = NULL, this is a shorthand constructor to make NULL the default
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
  int maxLineLength;
  double minToPay;
  double minPerItem;
  RegisterQueue(double minToPay, double minPerItem) {
    front = rear = nullptr;
    maxLineLength = 8;
    numberOfCustomers = 0;
    this->minToPay = minToPay;
    this->minPerItem = minPerItem;
  }
  ~RegisterQueue() {
    while (front) {
      Node *next = front->next;
      delete(front);
      front = next;
    }
  }
  void enqueue(Customer cust) {
    if(numberOfCustomers >= maxLineLength)
      throw("FullLineException");

    if(!numberOfCustomers) {// Starting list scenario
      front = rear = new Node(cust, nullptr);
    } else {
      Node *next = new Node(cust, rear);
      rear->next = next;
      rear = next;
    }
    numberOfCustomers++;
  }
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
  Customer seeNext() {
    return front->value;
  }
};
