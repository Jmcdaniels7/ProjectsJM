#ifndef STACK_H
#define STACK_H
#include "stackADT.h"
#include <stdexcept>
#include <cassert>

template <class type>
struct nodeType
{
    type *info;
    nodeType<type> *link;
};

template <class type>
class stackType: public stackADT<type>
{
    public:
        const stackType<type>& operator=(const stackType<type>&);
        bool isEmptyStack() const;
        bool isFullStack() const;
        void initializeStack();
        void push(const type& newItem);
        type top() const;
        void pop();

        //default constructor
        stackType();

        //copy constructor
        stackType(const stackType<type>& otherStack);

        //destructor
        ~stackType();
    private:
        //pointer to the stack
        nodeType<type> *stackTop;

        //to make a copy of otherStack
        void copyStack(const stackType<type>& otherStack);
};

template <class type>
stackType<type>::stackType()
{
    stackTop = nullptr;
}

template <class type>
bool stackType<type>::isEmptyStack() const
{
    return (stackTop == nullptr);
}

template <class type>
bool stackType<type>::isFullStack() const
{
    return false;
}

template <class type>
void stackType<type>::initializeStack()
{
    //pointer to delete the node
    nodeType<type> *temp;

    // loop for clearing the stack
    while (stackTop != nullptr)
    {
        temp = stackTop;

        stackTop = stackTop->link;

        delete temp;
    }
}

template <class type>
void stackType<type>::push(const type& newElement)
{
    nodeType<type> *newNode;

    newNode = new nodeType<type>;
    newNode->info = new type(newElement);
    newNode->link = stackTop;
    
    stackTop = newNode;
}

template <class type>
type stackType<type>::top() const
{
    assert(stackTop != nullptr);

    return *(stackTop->info);
}

template <class type>
void stackType<type>::pop()
{
    nodeType<type> *temp;

    if(stackTop != nullptr)
    {
        temp = stackTop;

        stackTop = stackTop->link;

        delete temp;
    }
    else
    {
        std::cout << "Cannot remove from an empty stack!" << std::endl;
    }
}

template <class type>
void stackType<type>::copyStack(const stackType<type>& otherStack)
{
    nodeType<type> * newNode;
    nodeType<type> * current;
    nodeType<type> * last;

    if(stackTop != nullptr)
    {
        initializeStack();
    }

    if(otherStack.stackTop == nullptr)
    {
        stackTop == nullptr;
    }
    else
    {
        current = otherStack.stackTop;

        stackTop = new nodeType<type>;

        stackTop->info = current->info;
        stackTop->link = nullptr;

        last = stackTop;
        current = current->link;

        while(current != nullptr)
        {
            newNode = new nodeType<type>;

            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

template <class type>
stackType<type>::stackType(const stackType<type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}

template <class type>
stackType<type>::~stackType()
{
    initializeStack();
}

template <class type>
const stackType<type>& stackType<type>::operator=(const stackType<type>& otherStack)
{
    if (this != &otherStack)
    {
        copyStack(otherStack);
    }

    return *this;
}

#endif