#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename T>
class Queue
{
  public:
    Queue();
    ~Queue();
    void enqueue(T d);
    T dequeue();
    T peek();
    bool isEmpty();
    int getSize();
    void print();
  private:
    DoublyLinkedList<T>* queue;
};

template <typename T>
Queue<T>::Queue()
{
  queue = new DoublyLinkedList<T>();
}

template <typename T>
Queue<T>::~Queue()
{
  delete queue;
}

template <typename T>
void Queue<T>::enqueue(T d)
{
  queue->insertBack(d);
}

template <typename T>
T Queue<T>::dequeue()
{
  return queue->removeFront();
}

template <typename T>
T Queue<T>::peek()
{
  return queue->getFront();
}

template <typename T>
bool Queue<T>::isEmpty()
{
  return queue->isEmpty();
}

template <typename T>
int Queue<T>::getSize()
{
  return queue->getSize();
}

#endif
