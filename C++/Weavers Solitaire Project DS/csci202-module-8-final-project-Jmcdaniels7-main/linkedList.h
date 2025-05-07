#pragma once

#include "linkedListIterator.h"
#include <iostream>

template <class Type>
class linkedList
{
public:
	const linkedList<Type> &operator=(const linkedList<Type> &);
	void initializeList();
	bool isEmptyList() const;
	void print(std::ostream &) const;
	int length() const;
	void destroyList();
	Type front() const;
	Type back() const;
	virtual bool search(const Type &searchItem) const = 0;
	virtual void inserthead(const Type &newItem) = 0;
	virtual void inserttail(const Type &newItem) = 0;
	virtual void deleteNode(const Type &deleteItem) = 0;
	linkedListIterator<Type> begin();
	linkedListIterator<Type> end();
	linkedList();
	linkedList(const linkedList<Type> &otherList);
	~linkedList();

protected:
	int count;
	node<Type> *head;
	node<Type> *tail;

private:
	void copyList(const linkedList<Type> &otherList);
};

template <class Type>
bool linkedList<Type>::isEmptyList() const
{
	return (head == nullptr);
}

template <class Type>
linkedList<Type>::linkedList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <class Type>
void linkedList<Type>::destroyList()
{
	node<Type> *temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->link;
		delete temp;
	}
	tail = nullptr;
	count = 0;
}

template <class Type>
void linkedList<Type>::initializeList()
{
	destroyList();
}

template <class Type>
void linkedList<Type>::print(std::ostream &out) const
{
	node<Type> *current;
	current = head;
	while (current != nullptr)
	{
		out << *(current->info) << std::endl;
		current = current->link;
	}
}

template <class Type>
int linkedList<Type>::length() const
{
	return count;
}

template <class Type>
Type linkedList<Type>::front() const
{
	assert(head != nullptr);
	return head->info;
}

template <class Type>
Type linkedList<Type>::back() const
{
	assert(tail != nullptr);
	return tail->info;
}

template <class Type>
linkedListIterator<Type> linkedList<Type>::begin()
{
	linkedListIterator<Type> temp(head);
	return temp;
}

template <class Type>
linkedListIterator<Type> linkedList<Type>::end()
{
	linkedListIterator<Type> temp(nullptr);
	return temp;
}

template <class Type>
void linkedList<Type>::copyList(const linkedList<Type> &otherList)
{
	node<Type> *newNode;
	node<Type> *current;
	if (head != nullptr)
		destroyList();
	if (otherList.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	else
	{
		current = otherList.head;
		count = otherList.count;

		head = new node<Type>;
		head->info = current->info;
		head->link = nullptr;

		tail = head;
		current = current->link;
		while (current != nullptr)
		{
			newNode = new node<Type>;
			newNode->info = new Type(*current->info);
			newNode->link = nullptr;
			tail->link = newNode;
			tail = newNode;
			current = current->link;
		}
	}
}

template <class Type>
linkedList<Type>::~linkedList()
{
	destroyList();
}

template <class Type>
linkedList<Type>::linkedList(const linkedList<Type> &otherList)
{
	head = nullptr;
	copyList(otherList);
}

template <class Type>
const linkedList<Type> &linkedList<Type>::operator=(const linkedList<Type> &otherList)
{
	if (this != &otherList)
	{
		copyList(otherList);
	}

	return *this;
}