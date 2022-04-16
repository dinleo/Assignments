#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 2022. 4. 4  Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  */

#include "doublylinkedlist.h"
#include <string>

typedef DoublyLinkedList<std::string> BufferType;


/* Very simple line text editor */
class TextEditor
{
public:
	// Default constructor
	TextEditor();

	// Destructor
	~TextEditor();

	// Insert a new line after the current position
	void Insert(const char* s);
	
	// Delete the current line
	void Delete();
	
	// Move one line up
	void MoveUp();
	
	// Move one line down
	void MoveDown();
	
	// Print the current line with the line number
	void Print();

	// Print all with the line number
	void PrintAll();
	
	// Run interactive mode
	void Run();
		
private:
	// Data
	BufferType buffer;
	
	BufferType::Iterator pos;
	
	int currLine;
};

#endif