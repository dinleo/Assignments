#include "doublylinkedlist.h"
#include <iostream>
#include <math.h>

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 2022. 4. 4  Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  */

/*
 * Iterator
 */
template<class T>
typename DoublyLinkedList<T>::Iterator& 
DoublyLinkedList<T>::Iterator::operator++() 
{
    this->current = this->current->rlink;
    return *this;
}

template<class T>
typename DoublyLinkedList<T>::Iterator  
DoublyLinkedList<T>::Iterator::operator++(int) 
{
    this->current = this->current->rlink;
    return this->current->llink;
}

template<class T>
typename DoublyLinkedList<T>::Iterator& 
DoublyLinkedList<T>::Iterator::operator--() 
{
    this->current = this->current->llink;
    return *this;
}

template<class T>
typename DoublyLinkedList<T>::Iterator  
DoublyLinkedList<T>::Iterator::operator--(int) 
{
    this->current = this->current->llink;
    return this->current->rlink;
}


/*
 * Reverse Iterator
 */
template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator&
DoublyLinkedList<T>::Reverse_Iterator::operator++() 
{
    this->current = this->current->llink;
    return *this;
}

template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator
DoublyLinkedList<T>::Reverse_Iterator::operator++(int)
{
    this->current = this->current->llink;
    return this->current->rlink;
}

template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator&
DoublyLinkedList<T>::Reverse_Iterator::operator--() 
{
    this->current = this->current->rlink;
    return *this;
}

template<class T>
typename DoublyLinkedList<T>::Reverse_Iterator
DoublyLinkedList<T>::Reverse_Iterator::operator--(int)
{
    this->current = this->current->rlink;
    return this->current->llink;
}

/*
 * Doubly linked list
 */
// Default constructor
template<class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    NodeType * temp = new DoublyLinkedListNode<T> ();
	first = temp;
    first->llink = first;
    first->rlink = first;
}

// Copy constructor
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& source)
{
    NodeType * tempFirst = new DoublyLinkedListNode<T> ();
    first = tempFirst;
    DoublyLinkedList<T>::Iterator source_it = source.Begin();
    DoublyLinkedList<T>::Iterator this_it = first;
    while(source_it != source.End()){
        NodeType * temp = new DoublyLinkedListNode<T> ();
        temp->data = *source_it;
        temp->llink = this_it.GetNodePointer();
        temp->rlink = first;
        first->llink = temp;
        this_it.GetNodePointer()->rlink = temp;
        this_it++;
        source_it++;
    }
}


// Destructor
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    DoublyLinkedList<T>::Iterator it = this->Begin();
    while (it != this->End()){
        NodeType * cur = it.GetNodePointer();
        delete cur;
        it ++;
    }
}


// Assignment operator
template<class T>
DoublyLinkedList<T>& 
DoublyLinkedList<T>::operator = (const DoublyLinkedList<T>& source)
{
    DoublyLinkedList<T>::Iterator source_it = source.Begin();
    DoublyLinkedList<T>::Iterator this_it = first;
    while(source_it != source.End()){
        NodeType * temp = new DoublyLinkedListNode<T> ();
        temp->data = *source_it;
        temp->llink = this_it.GetNodePointer();
        temp->rlink = first;
        first->llink = temp;
        this_it.GetNodePointer()->rlink = temp;
        this_it++;
        source_it++;
    }
    return *this;
}



// Total number of nodes in the list
template<class T>
int 
DoublyLinkedList<T>::Size() const
{
	int size = 0;
    DoublyLinkedList<T>::Iterator it = Begin();
    while (it != End()){
        size++;
        it++;
    }
    return size;
}


// Insert a new node to the list as the first node
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator 
//typename Iterator
DoublyLinkedList<T>::InsertFirst(const T& data)
{
    NodeType * temp = new DoublyLinkedListNode<T> ();
    temp->data = data;
	temp->llink = first;
    temp->rlink = first->rlink;
    first->rlink->llink = temp;
    first->rlink = temp;
    return temp;
}


// Insert a new node to the list as the last node
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator
DoublyLinkedList<T>::InsertLast(const T & data)
{
    NodeType * temp = new DoublyLinkedListNode<T> ();
    temp->data = data;
    temp->rlink = first;
    temp->llink = first->llink;
    first->llink->rlink = temp;
    first->llink = temp;
    return temp;
}


// Insert a new node to the list after pos
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator 
DoublyLinkedList<T>::InsertNext(DoublyLinkedList<T>::Iterator pos, const T & data)
{
    NodeType * temp = new DoublyLinkedListNode<T> ();
    NodeType * cur = pos.GetNodePointer();
    temp->data = data;
    temp->llink = cur;
    temp->rlink = cur->rlink;
    cur->rlink->llink = temp;
    cur->rlink = temp;
    return temp;

}


// Insert a new node to the list before pos
// Return the pointer of new node
template<class T>
typename DoublyLinkedList<T>::Iterator 
DoublyLinkedList<T>::InsertPrev(DoublyLinkedList<T>::Iterator pos, const T & data)
{
    NodeType * temp = new DoublyLinkedListNode<T> ();
    NodeType * cur = pos.GetNodePointer();
    temp->data = data;
    temp->rlink = cur;
    temp->llink = cur->llink;
    cur->llink->rlink = temp;
    cur->llink = temp;
    return temp;
}


// Delete node at pos in the list
template<class T>
bool 
DoublyLinkedList<T>::DeleteNode(Iterator pos)
{
    NodeType * cur = pos.GetNodePointer();
    if (cur == first){
        return false;
    }
    cur->llink->rlink = cur->rlink;
    cur->rlink->llink = cur->llink;

    delete cur;
    return true;
}


// Delete first node
template<class T>
bool 
DoublyLinkedList<T>::DeleteFirst()
{
	if (Size() == 0){
        return false;
    }
    NodeType * cur = Begin().GetNodePointer();
    cur->llink->rlink = cur->rlink;
    cur->rlink->llink = cur->llink;
    delete cur;
    return true;
}


// Delete last node
template<class T>
bool 
DoublyLinkedList<T>::DeleteLast()
{
    if (Size() == 0){
        return false;
    }
    NodeType * cur = End().GetNodePointer()->llink;
    cur->llink->rlink = cur->rlink;
    cur->rlink->llink = cur->llink;
    delete cur;
    return true;
}


template<class T>
void 
DoublyLinkedList<T>::Print(bool reverse)
{
	if(reverse)
	{
		for(Reverse_Iterator rit = rBegin(); rit!=rEnd(); rit++)
		{	
			std::cout << *rit << ", ";
		}
	}
	else 
	{		
		for(Iterator it = Begin(); it!=End(); it++)
		{	
			std::cout << *it << ", ";
		}		
	}
	
	std::cout << std::endl;
}

