#include <iostream>
#include <sstream> //use sstream to extract indivual characters from line
#include <string> //to remove \n at the end of the string
#include <string.h>
//#include <bits/stdc++.h>
#include "TextEditor.h"
using namespace std;

void menu() {
	cout << endl;
	cout << "*--------------------------------------------------------*\n";
	cout << "W [<filename>] - Writes the contents of the current \"buffer\" to a file. If no filename is given, then it uses the file name of the file that has been opened. If no file has been opened, then the editor will indicate to the user that a file name must be given.\n\n";
	cout << "J <line number> - Jump to a line in the file. -1 will jump to the end of the file, 0 will jump to the beginning of the file\n\n";
	cout << "I [<some text>] - Insert the text at the \"current\" line. If no text is given, will insert a blank line\n\n";
	cout << "A [<some text>] - Insert the text after the \"current\" line. If no text is given, will insert a blank line\n\n";
	cout << "L [<line number>] [<line number>] - Lists the contents of the buffer. If no line numbers are given, lists the contents of the entire buffer. If one line number is given, shows only that line. If 2 line numbers are given, lists all the lines between the numbers, including the lines at the start and end number.\n\n";
	cout << "D [<line number>] [<line number>] - Deletes one or more lines. If no line numbers are given, deletes the current line. If 1 line number is given, deletes that line. If 2 line numbers are given, deletes the range of lines, inclusive of the start and end line numbers. The first line number given is the start, and the second is the end. Should check to see if the line numbers are in the appropriate order.";
	cout << "Q - Quits the editor. If the buffer has been modified and not written, the close command should prompt the user and ask if they want to save changes before quitting.\n\n";
	cout << "*--------------------------------------------------------*"<<endl;
}

void splitString(const string &s, vector<string> &str){
    stringstream X(s);                  //put string s into string stream x
    string cw="";                          //character or word
    while (getline(X, cw, ' ')){        //every word that is split, put at the end of the vector
        str.push_back(cw);
    }
}

int main(){
    //char command; //user inputs single character command 'J','A', etc.
    string text, convert;

    TextEditor file; //make TextEditor object
    vector<string> comm;
    menu(); //show command menu
    
    cout << "COMMAND: ";
    getline(cin, text);
    splitString(text, comm); //split string into words
    
    convert=comm[0]; //first element in vector is the command
    char command[1]; //make char array the length of the string, user inputs single character command 'J', 'A', etc. 

    strcpy(command, convert.c_str()); //copy string into char arr (strcpy_s doesnt work BECAREFUL)

    //use switch for different commands
    while (command[0]=='W'||command[0]=='J'||command[0]=='I'||command[0]=='A'||command[0]=='L'||command[0]=='D'){ //does not include Q to exit program
        switch(command[0]){ //switch requires integers

        case 'W':{ //write to a file
            file.makeVec(text);
            file.write();
            break;
        } 
        case 'J':{ //jump to a line
        //need to change string text to an int for a line 
        //format J <line number>
            cout << "Output the text after command: " << comm[1] << comm[2] << endl;
            break;
        }
        case 'I':{ //insert text AT current line
            cout << "case I " << endl;
            break;
        }
        case 'A':{ //insert text AFTER current line

            break;
        }
        case 'L':{ //liss contents of the buffer

            break;
        }
        case 'D':{ //deletes one or more lines

            break;
        }
        case 'Q':{ //quits the editor
            break;
        }
        }
        cin >> command; //ask user to prompt another command
        getline(cin, text); 
    }
    return 0;
    //new feature branch
}
//hello
//to comment highlighted text: shift \+ alt \+ a