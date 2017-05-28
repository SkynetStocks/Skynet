#ifndef QUEUE_H
#define QUEUE_H

#include "QueueNode.h"

template <class ItemType>
class Queue  //circularly implemented buffer queue
{
private:
	QueueNode<ItemType>* Front;
	QueueNode<ItemType>* Back;
public:
	Queue();
	~Queue() { clear(); }

	bool isEmpty() { return Head; }
	void enqueue(ItemType val);
	ItemType dequeue();
	ItemType peek();
	void clear();
};

template <class ItemType>
Queue<ItemType>::Queue()
{
	Front = new QueueNode<ItemType>; //back and head are same on initialization
	Back = Front;
	Back->setNext(Front);
}

template <class ItemType>
void Queue<ItemType>::enqueue(ItemType val)
{
	QueueNode<ItemType>* NewNode = new QueueNode<ItemType>(val, Back->getNext()); //adds a new node to the back of the line
	Back->setNext(NewNode);
}

template <class ItemType>
ItemType Queue<ItemType>::dequeue()
{
	if (Front->getNext()!=Front)
	{
		QueueNode<ItemType>* Node = Front->getNext();
		Front->setNext(Node->getNext());
		ItemType Item = Node->getItem();
		delete Node;
		return Item;
	}
}

template <class ItemType>
ItemType Queue<ItemType>::peek()
{
	return Front->getNext()->getItem();
}

template <class ItemType>
void Queue<ItemType>::clear()
{
	while (Front->getNext() != Front)
	{
		dequeue();
	}
	delete Front;
}

#endif //QUEUE_H