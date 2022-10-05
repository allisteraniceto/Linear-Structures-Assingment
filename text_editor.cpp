#include <iostream>
#include <sstream> //use sstream to extract indivual characters from line
#include <string> //to remove \n at the end of the string
#include <cstring>
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

//splits line into command
void splitString(const string &s, vector<string> &str){
    stringstream X(s);                  //put string s into string stream x
    string cw="";                          //character or word
    while (std::getline(X, cw, ' ')){        //every word that is split, put at the end of the vector
        str.push_back(cw);
    }
}

//returns string command into a string
void getCommand(vector<string> &str, char* c){
    string convert;
    convert=str[0]; //first elemetn in vector is command
    strcpy(c, convert.c_str()); //copy string into char arr (strcpy_s doesnt work BECAREFUL)
}

//concatenates strings after the first element (command) into one string
string concatenate(vector<string> &str){
    string c;
    for (int i=1; i < str.size(); i++){
        c=c+str[i]+" ";
    }
    return c;
}

int main(){
    TextEditor file; //make TextEditor object
    vector<string> comm;
    string text;
    string input;
    char command[2]; //user inputs single character command 'J','A', etc.
    int currentLine=0;

    menu(); //show command menu
    
    cout << "COMMAND: ";
    std::getline(std::cin, text);
    splitString(text, comm); //split string into words
    getCommand(comm, command);

    //use switch for different commands
    while (command[0]=='W'||command[0]=='J'||command[0]=='I'||command[0]=='A'||command[0]=='L'||command[0]=='D'){ //does not include Q to exit program
        switch(command[0]){ //switch requires integers

        case 'W':{ //write to a file
            file.makeVec(comm[1]);
            file.write();
            break;
        } 
        case 'J':{ //jump to a line
        //need to change string text to an int for a line 
        //format J <line number>
            istringstream(comm[1]) >> currentLine;
            if (currentLine == -1) { //if command line # is -1;
                file.setCurrentLine(currentLine);
            }
            else if (currentLine == 0) {//if command line # is 0;
                file.setCurrentLine(file.getLastElement()); //last element
            }
            else
                file.setCurrentLine(currentLine);
            cout << "Current Line: " << currentLine << endl;
            break;
        }
        case 'I':{ //insert text AT current line
            input=concatenate(comm); //concatenates string elements after command together
            file.insertAt(input);
            cout << "case I: "<< input << endl;
            break;
        }
        case 'A':{ //insert text AFTER current line
            input=concatenate(comm);
            file.insertAfter(input);
            break;
        }
        case 'L':{ //list contents of the buffer
            file.listBuffer(comm);
            break;
        }
        case 'D':{ //deletes one or more lines
            file.deleteLines(comm);
            break;
        }
        case 'Q':{ //quits the editor
            break;
        }
        }
        comm.clear(); //clear vector
        cout << "COMMAND: "; //redo command process
        std::getline(std::cin, text);
        splitString(text, comm);
        getCommand(comm, command);
    }
    return 0;
    //new feature branch
}
//hello
//to comment highlighted text: shift \+ alt \+ a