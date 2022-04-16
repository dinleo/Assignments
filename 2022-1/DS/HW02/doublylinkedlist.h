#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H

#include <iostream>

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 2022. 4. 4  Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  */
  
template<class T>
class DoublyLinkedList;


// List Node class
template<class T>
class DoublyLinkedListNode{
	friend class DoublyLinkedList<T>;
	friend class DoublyLinkedList<T>::Iterator_Base;
	friend class DoublyLinkedList<T>::Iterator;
	friend class DoublyLinkedList<T>::Reverse_Iterator;
private:
	T data;         // data
	DoublyLinkedListNode<T> * llink;    // left link
	DoublyLinkedListNode<T> * rlink;    // right link
};


// List class
template<class T>
class DoublyLinkedList
{
public:
	typedef DoublyLinkedListNode<T> NodeType;
		
	// iterator
	class Iterator_Base {
	public:
		Iterator_Base(NodeType * startNode = 0) { current = startNode; }
		~Iterator_Base() {}
		
		Iterator_Base(const Iterator_Base& source) { current = source.current; }
		
		// dereferencing operators
		T& operator*() const { return current->data; }
		T* operator->() const { return &current->data;}
		
		// get the node pointer directly
		NodeType* GetNodePointer() { return current; }
		
		// equality testing
		bool operator!=(const Iterator_Base it) const
			{ return current != it.current; }
		bool operator==(const Iterator_Base it) const
			{ return current == it.current; }
		
	protected:
		NodeType * current;
	};
		
	class Iterator : public Iterator_Base {
	public:
		Iterator(NodeType * startNode = 0) : Iterator_Base(startNode) {}
		Iterator& operator++();    // ToDo
		Iterator  operator++(int); // ToDo
		Iterator& operator--();    // ToDo
		Iterator  operator--(int); // ToDo
	};
		
	class Reverse_Iterator : public Iterator_Base {
	public:
		Reverse_Iterator(NodeType * startNode = 0) : Iterator_Base(startNode) {}
		Reverse_Iterator& operator++();    // ToDo
		Reverse_Iterator  operator++(int); // ToDo
		Reverse_Iterator& operator--();    // ToDo
		Reverse_Iterator  operator--(int); // ToDo

	};
	
	// Default constructor - ToDo
	DoublyLinkedList();
	
	// Copy constructor - ToDo
	DoublyLinkedList(const DoublyLinkedList& source);

	// Destructor - ToDo
	~DoublyLinkedList();

	// Assignment operator - ToDo
	DoublyLinkedList& operator = (const DoublyLinkedList& source);

	// Get leftmost node iterator
	Iterator Begin() const { Iterator it(first); return ++it; };
		
	// Get end iterator
	Iterator End() const {  Iterator it(first); return it; }
	
	// Get rightmost iterator
	Reverse_Iterator rBegin() const { Reverse_Iterator it(first); return ++it; };
	
	// Get end iterator
	Reverse_Iterator rEnd() const {  Reverse_Iterator it(first); return it; }
	
	// Insert a new node to the list as the first node
	// Return the pointer of new node - ToDo
	Iterator InsertFirst(const T & data);

	// Insert a new node to the list as the last node
	// Return the pointer of new node - ToDo
	Iterator InsertLast(const T & data);

	// Insert a new node to the list after pos
	// Return the pointer of new node - ToDo
	Iterator InsertNext(Iterator pos, const T & data);
	
	// Insert a new node to the list before pos
	// Return the pointer of new node - ToDo
	Iterator InsertPrev(Iterator pos, const T & data);
	
	// Total number of nodes in the list - ToDo
	int Size() const;				
		
	// Delete node at pos in the list - ToDo
	bool DeleteNode(Iterator pos);
	
	// Delete first node - ToDo
	bool DeleteFirst();
	
	// Delete last node - ToDo
	bool DeleteLast();

	// Print list
	void Print(bool reverse=false);
		
private:
	// first pointer of the list
	NodeType * first;
};

#ifndef DoublyLinkedList_TXX
#define DoublyLinkedList_TXX
#include "doublylinkedlist.txx"
#endif

#endif
