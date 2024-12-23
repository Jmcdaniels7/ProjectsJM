#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class t>
class unorderedLinkedList : public linkedList<t>
{
public:
    enum directionType
    {
        FORWARD,
        BACKWARD
    };
    unorderedLinkedList(directionType = FORWARD);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;

private:
    directionType direction;
    void insertFirst(const t &newInfo);
    void insertLast(const t &newInfo);
};
#endif

template <class t>
void unorderedLinkedList<t>::insert(const t &newInfo)
{
    if (direction == FORWARD)
    {
        insertLast(newInfo);
    }
    else
    {
        insertFirst(newInfo);
    }
}

template <class t>
void unorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from empty list");
    }
    else
    {
        if (*(this->head->data) == deleteItem)
        {
            current = this->head;
            this->head = this->head->link;
            this->count--;
            if (this->head == nullptr)
            {
                this->tail = nullptr;
            }
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->link;
            while (current != nullptr && !found)
            {
                if (*(current->data) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                {
                    found = true;
                }
            }
            if (found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->tail == current)
                {
                    this->tail = trailCurrent;
                }
                delete current;
            }
            else
            {
                throw std::out_of_range("Item not found in list. Cannot delete");
            }
        }
    }
}

template <class t>
bool unorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

template <class t>
void unorderedLinkedList<t>::insertFirst(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->link = this->head;
        this->head = newNode;
    }
    this->count++;
}

template <class t>
void unorderedLinkedList<t>::insertLast(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
    }
    this->count++;
}