#include "texteditor.h"
#include <iostream>
using namespace std;

/** 
  * Assignment 2 for COSE213 Data Structures
  *
  * 2022. 4. 4  Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  */


// Default constructor 
TextEditor::TextEditor()
{
    pos = buffer.Begin();
    currLine = 0;
}

TextEditor::~TextEditor()
{
    BufferType::Iterator it = pos;
    while (it != buffer.End()){
        DoublyLinkedListNode<string> * cur = it.GetNodePointer();
        delete cur;
        it ++;
    }
}

// Insert a new line after the current position
void TextEditor::Insert(const char* s)
{
    buffer.InsertNext(pos, s);
    pos++;
    currLine++;
}

// Delete the current line
void TextEditor::Delete()
{
    if (buffer.Size() == 0){
        cout<<"Cannot Delete: Buffer is empty"<<endl;
        return;
    }
	buffer.DeleteNode(pos);
    pos++;
    if(pos==buffer.End()){
        pos--;
        currLine--;
    }

}

// Move one line up
void TextEditor::MoveUp()
{
	if(pos==buffer.Begin()){
        cout<<"Beginning of the buffer"<<endl;
        return;
    }
    pos--;
    currLine--;
}

// Move one line down
void TextEditor::MoveDown()
{
	pos++;
    currLine++;
    if(pos==buffer.End()){
        cout<<"End of the buffer"<<endl;
        pos--;
        currLine--;
    }
}

//
// Interactive mode
//
void TextEditor::Run()
{
	while(1)
	{
        string inp;
		cout << flush << "> ";
		getline(cin, inp);

		// ToDo	- implement other functions
		if(inp == "u") MoveUp();
        else if(inp == "d") MoveDown();
        else if(inp == "p") {
            Print();
        }
        else if(inp == "pa") {
            PrintAll();
        }
        else if(inp == "r") Delete();
        else if(inp == "i"){
            string bfr;
            cout << "(Insert) > ";
            getline(cin, bfr);
            const char *t_bfr = bfr.data();
            Insert(t_bfr);
        }
		else if(inp == "x") exit(0);
		else
		{
			cout << "No such command. Available commands are u(up), d(down), p(print), pa(print all), r (delete), i(insert), and x(exit)" << endl;
		}

	}
}


// ----------------------

// Print the current line with the line number
void TextEditor::Print()
{
	if(buffer.Size() < 1) {
		std::cout << "Buffer is empty" << std::endl;
	}
	else {
		std::cout << "Current(L" << currLine << ") : " << *pos << std::endl;
	}
}

// Print all with the line number
void TextEditor::PrintAll()
{
	int i=1;
	for(BufferType::Iterator it=buffer.Begin(); it != buffer.End(); it++)
	{
		cout << "L" << i++ << " :";
		if(i == (currLine+1)) cout << "*";
		else cout << " ";
		cout << *it << endl;		
	}
}
