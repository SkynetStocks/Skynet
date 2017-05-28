#ifndef QUEUENODE_H
#define QUEUENODE_H

template <class ItemType>
class QueueNode{
public:
	QueueNode():Next(nullptr) {};
	QueueNode(ItemType val, QueueNode* NextNode):Item(val), Next(NextNode) {};

	inline ItemType getItem() const { return Item; }
	inline QueueNode<ItemType>* getNext() const { return Next; }

	inline void setItem(ItemType val) { Item = val; }
	inline void setNext(QueueNode<ItemType>* NewNext) { Next = NewNext; }

private:
	ItemType Item;
	QueueNode<ItemType>* Next;
};

#endif //QUEUENODE_H