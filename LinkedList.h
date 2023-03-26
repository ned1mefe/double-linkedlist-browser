#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.




private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    size = 0;
    head = NULL;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    size = obj.size;
    /* if empty */
    if (!obj.size) return;

    /* if it has only 1 node */
    head = new Node<T>(obj.head->data);
    head->next = head;
    head->prev = head;

    /* else */
    int repeat;
    repeat = size;
    
    Node<T> *curr = head;
    Node<T> *currobj = obj.head;

    while(--repeat > 0)
    {
        curr->next = new Node<T>(currobj->next->data ,curr ,head);

        curr = curr->next;
        currobj = currobj->next;
    }
    head->prev = curr;
    
}

template<class T>
LinkedList<T>::~LinkedList()
{
    if (head == NULL){
        size = 0;
        return;
    }
    /*if it has only 1 node */
    if (size == 1){
        delete head;
    }

    /* else */
    if (size > 1){
        Node<T> *curr = head;
        Node<T> *prev = head->prev;

        for(int i = 0; i < size; i++){
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    
    size = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if (!(this != &rhs)) return *this;
    /*if it has only 1 node */
    if (size == 1){
        delete head;
    }

    /* else */
    if (size > 1){
        Node<T> *curr = head;
        Node<T> *prev = head->prev;

        for(int i = 0; i < size; i++){
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    
    /* may give an error */
    size = rhs.size;


    /* if empty */
    if (rhs.head == NULL){
        head = NULL;
        return *this;
    }

    /* if it has only 1 node */
    head = new Node<T>(rhs.head->data);
    head->next = head;
    head->prev = head;

    /* else */
    int repeat;
    repeat = size;
    
    Node<T> *curr = head;
    Node<T> *currobj = rhs.head;

    while(--repeat > 0)
    {
        curr->next = new Node<T>(currobj->next->data ,curr ,head);

        curr = curr->next;
        currobj = currobj->next;
    }
    return *this;


}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if (size == 0) return true;
    return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    if (isEmpty()) return false;

    Node<T> *curr = head;

    for(int i=0;i<size;i++){
        if (curr == node) return true;
        curr = curr->next;
    }
    return false;   
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if (isEmpty()) return NULL;

    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (isEmpty()) return NULL;

    return head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    if (isEmpty()) return NULL;
    Node<T> *curr = head;

    for (int i = 0;i<size;i++)
    {
        if (curr->data == data) return curr;
        curr = curr->next;   
    }

    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    if ((index >= size) || (index<0)) return NULL;
    
    Node<T> *curr = head;
    while (index--)
    {
        curr = curr->next;
    }

    return curr;

}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if(isEmpty())
    {
        head = new Node<T>(data);
        head->prev = head;
        head->next = head;
        size++;
        return;
    }

    Node<T> *first = head;
    Node<T> *last = head->prev;

    last->next = new Node<T>(data,last,first);
    first->prev = last->next;
    size++;
    
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    
    if(isEmpty())
    {
        head = new Node<T>(data);
        head->prev = head;
        head->next = head;
        size++;
        return;
    }

    Node<T> *first = head;
    Node<T> *last = head->prev;

    last->next = new Node<T>(data,last,first);
    first->prev = last->next;
    head = last->next;
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (!containsNode(node)) return;

    /* else */

    Node<T> *nextone = node->next;

    node->next = new Node<T>(data,node,nextone);
    nextone->prev = node->next;
    size++;

}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if (index > size) return;
    
    if (index == size){
        append(data);
        return;
    }
    
    Node<T> *curr = getNodeAtIndex(index);
    Node<T> *prevone = curr->prev;


    curr->prev = new Node<T>(data,prevone,curr);
    prevone->next = curr->prev;

    if (index == 0) head = curr->prev; 
    size++;

}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    if (isEmpty()) return -1;

    Node<T> *curr = head;

    for(int i=0;i<size;i++){
        if ((curr->data == node->data) && (curr->next == node->next) && (curr->prev == node->prev))
        {
            return i;
        }
        curr = curr->next;

    }
    return -1;   
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex > size-1) return;

    if (size == 1) return;
    
    if (newIndex > size-1) newIndex = size - 1;

    if (currentIndex == newIndex) return;

    Node<T> *cinode = getNodeAtIndex(currentIndex);
    Node<T> *ninode = getNodeAtIndex(newIndex);
    
    if (newIndex == 0) head = cinode;
    if (currentIndex == 0) head = cinode->next;
    /* deletion */
    cinode->prev->next = cinode->next;
    cinode->next->prev = cinode->prev;

    /* insertion */
    if(currentIndex > newIndex)
    {
        ninode->prev->next = cinode;
        cinode->prev = ninode->prev;

        ninode->prev = cinode;
        cinode->next = ninode;
    }

    if (currentIndex < newIndex)
    {
        ninode->next->prev = cinode;
        cinode->next = ninode->next;

        cinode->prev = ninode;
        ninode->next = cinode;
    }

}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if (!node) return;
    if (!containsNode(node)) return;

    if (size == 1) {
        delete head;
        size--;
        return;
    }

    if (node == head) head = head->next;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
    size--;
    
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    while( getNode(data) ) removeNode(getNode(data));
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (index < size) removeNode(getNodeAtIndex(index));
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
   {
    /*if it has only 1 node */
    if (size == 1){
        delete head;
    }

    /* else */
    if (size > 1){
        Node<T> *curr = head;
        Node<T> *prev = head->prev;

        for(int i = 0; i < size; i++){
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    
    size = 0;
}
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H
