#include "doublylinkedlist.h"
#include "texteditor.h"
#include <iostream>

using namespace std;

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 2022. 4. 4  Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  */

int main()
{
	// 
	// 1. Test Doubly Linked List
	//
    std::cout << "1. Test Doubly Linked List" << std::endl;
	DoublyLinkedList<int> list;

	list.InsertFirst( 10 );	
	std::cout << "IF 10: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;

	list.InsertFirst( 20 );
	std::cout << "IF 20: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;
	
	list.InsertFirst( 30 );
	std::cout << "IF 30: 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;

	list.InsertFirst( 40 );
	std::cout << "IF 40: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;
	
	list.InsertLast( 50 );
	std::cout << "IL 50: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;
	
	list.InsertLast( 60 );
	std::cout << "IL 60: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;

	// assignment operator test
    std::cout << "assignment operator test" << std::endl;
	DoublyLinkedList<int> list2;
	list2 = list; 

	std::cout << "List 2 Size : " << list2.Size() << std::endl;
	list2.Print();
	std::cout << "--" << std::endl;

    list2.DeleteFirst();
    std::cout << "DF : List 2 Size : " << list2.Size() << std::endl;
    list2.Print();
    std::cout << "--" << std::endl;
	
	// copy constructor test
    std::cout << "copy constructor test" << std::endl;
	DoublyLinkedList<int> list3 = list;
	
	std::cout << "List 3 Size : " << list3.Size() << std::endl;
	list3.Print();
	std::cout << "--" << std::endl;

    // copy constructor test2
    std::cout << "copy constructor test2" << std::endl;
    DoublyLinkedList<int> list4 = list;

    list4.InsertFirst(100);
    std::cout << "IF 100: List 4 Size : " << list4.Size() << std::endl;
    list4.Print();
    std::cout << "--" << std::endl;

	
	list.DeleteFirst();
	std::cout << "DF: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;

	list.DeleteLast();
	std::cout << "DL: List 1 Size : " << list.Size() << std::endl;
	list.Print();
	std::cout << "--" << std::endl;
	
	std::cout << "List 2 Size : " << list2.Size() << std::endl;
	list2.Print();
	std::cout << "--" << std::endl;
	
	std::cout << "List 3 Size : " << list3.Size() << std::endl;
	list3.Print();
	std::cout << "--" << std::endl;
	
	// insert middle test
	DoublyLinkedList<int>::Iterator it = list3.Begin();
	std::cout << "First element of list 3 : " << *it << std::endl;
	it++;
	std::cout << "Second element of list 3 : " << *it << std::endl;
	std::cout << "70 will be inserted after " << *it << std::endl;
	it = list3.InsertNext(it, 70);
	list3.Print();
	std::cout << "65 will be inserted before 70" << std::endl;
	it = list3.InsertPrev(it, 65);
	list3.Print();
	it++;it++;it++;
	std::cout << *it << " will be deleted" << std::endl;
	list3.DeleteNode(it);
	list3.Print();
	std::cout << "--" << std::endl;

    it++;
    it--;
    std::cout << *it << std::endl;

	
	//
	// 2. Test texteditor
	//
    std::cout << "==============================" << std::endl;
    std::cout << "2. Test texteditor" << std::endl;
	TextEditor vi;

	std::cout << "Print out the current buffer:" << std::endl;
	vi.PrintAll();

    std::cout << "==============================" << std::endl;
    vi.Delete();
	
	vi.Insert("I am doing my assignment 2.");
	vi.Insert("This assignment is not so easy.");
	vi.Insert("But it is really fun.");
	vi.Insert("I hope I can make it.");
	vi.Insert("KU CSE rocks!");

    std::cout << "==============================" << std::endl;
	vi.PrintAll();

    std::cout << "==============================" << std::endl;
	vi.Print();

    std::cout << "==============================" << std::endl;
	std::cout << "Move up" << std::endl;
	vi.MoveUp();
	vi.Print();

    std::cout << "==============================" << std::endl;
	std::cout << "Move up" << std::endl;
	vi.MoveUp();
	vi.Print();

    std::cout << "==============================" << std::endl;
    vi.PrintAll();

    std::cout << "==============================" << std::endl;
	std::cout << "Delete the current line" << std::endl;
	vi.Delete();
	vi.Print();

    std::cout << "==============================" << std::endl;
	std::cout << "Print out the current buffer:" << std::endl;
	vi.PrintAll();

    std::cout << "==============================" << std::endl;
	std::cout << "Move down" << std::endl;
	vi.MoveDown();
	vi.Print();

    std::cout << "==============================" << std::endl;
	std::cout << "Insert new line" << std::endl;
	vi.Insert("Finally I made it~");

	std::cout << "Print out the current buffer:" << std::endl;
	vi.PrintAll();

    std::cout << "==============================" << std::endl;
    std::cout << "Delete the current line" << std::endl;
    vi.Delete();
    vi.Print();


    vi.PrintAll();
	
	//
	// 3. Test interactive mode
	//
	vi.Run();
	
	return 0;
}
