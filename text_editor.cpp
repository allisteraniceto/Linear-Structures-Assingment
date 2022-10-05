#include <iostream>
#include <sstream> //use sstream to extract indivual characters from line
#include <string> //to remove \n at the end of the string
#include <cstring>
#include <string.h>
#include <stdlib.h> //used to exit
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
    
    bool keepAlive=true;

    //exception handling, if not one of the commands, prompt user to reenter command
    while(keepAlive){
        try{
            int x = 0;
            cout << "COMMAND: ";
            std::getline(std::cin, text);
            splitString(text, comm); //split string into words
            getCommand(comm, command);
            if (!(command[0]=='W'||command[0]=='J'||command[0]=='I'||command[0]=='A'||command[0]=='L'||command[0]=='D'||command[0]=='Q')){
                throw (x);
            }
            keepAlive=false;
        }
        catch(int x){
            cout << "SYNTAX ERROR IN COMMAND ENTER AGAIN!!" << endl; 
        }
    }

    //use switch for different commands
    while (command[0]=='W'||command[0]=='J'||command[0]=='I'||command[0]=='A'||command[0]=='L'||command[0]=='D'||command[0]=='Q') { //does not include Q to exit program
        try{
            int t=0;
            switch(command[0]){ //switch requires integers or char

            case 'W':{ //write to a file
                file.setFileName(comm[0]);
                file.write();
                break;
            } 
            case 'J':{ //jump to a line
            //need to change string text to an int for a line 
            //format J <line number>
                if (comm.size()==1 || comm.size()>2){//if command is only J or more than J <line #>, throw exception.
                    throw (t);
                }
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
                int l1=0, l2=0;
                if (comm.size() == 2) {//outputs current line if 1 line is given
                istringstream(comm[1]) >> l1;
                }
                else if (comm.size() == 3) {
                istringstream(comm[1]) >> l1;
                istringstream(comm[2]) >> l2;
                    if (l1 > l2) { //if line 1 is bigger than line 2
                        cout << "LINE #1 CANNOT BE GREATER THAN LINE #2" << endl;
                        throw (t);
                    }
                }
                else if (comm.size()>3){//if command is more than J <line #> <line#>, throw exception.
                    cout << "TOO MANY COMMANDS!" << endl;
                    throw (t);
                }
                        
                file.listBuffer(comm);
                break;
            }
            case 'D':{ //deletes one or more lines
                int l1=0, l2=0;
                if (comm.size() == 2) {//outputs current line if 1 line is given
                    istringstream(comm[1]) >> l1;

                }
                else if (comm.size() == 3) {
                    istringstream(comm[1]) >> l1;
                    istringstream(comm[2]) >> l2;
                    if (l1 > l2) {
                        cout << "LINE #1 CANNOT BE GREATER THAN LINE #2" << endl;
                        throw (t);
                    }
                }
                else if (comm.size()>3){//if command is more than J <line #> <line#>, throw exception.
                    cout << "TOO MANY COMMANDS!" << endl;
                    throw (t);
                }                                   
                file.deleteLines(comm);
                break;
            }
            case 'Q':{ //quits the editor
                cout << "Terminating the program...";
                exit(0); //terminate program 
                
                break;
            }
            } //END SWITCH
        } //END TRY
        catch(int j){
            cout << "SYNTAX ERROR!!"<< endl;
        }

        comm.clear(); //clear vector
        
        keepAlive=true;
        while(keepAlive){
            try{
                int x = 0;
                cout << "COMMAND: ";
                std::getline(std::cin, text);
                splitString(text, comm); //split string into words
                getCommand(comm, command);
                if (!(command[0]=='W'||command[0]=='J'||command[0]=='I'||command[0]=='A'||command[0]=='L'||command[0]=='D'||command[0]=='Q')) {
                    throw (x);
                }
                keepAlive=false;
            }
            catch(int x){
                cout << "SYNTAX ERROR IN COMMAND ENTER AGAIN!!" << endl; 
            }
        }
    } //END COMMAND LOOP
    return 0;
    //new feature branch
}
//hello
//to comment highlighted text: shift \+ alt \+ a

/*
OUPUT:

COMMAND: I hello world
case I: hello world
COMMAND: J 2
Current Line: 2
COMMAND: I delete this line
case I: delete this line
COMMAND: L
1| hello world
2| delete this line
COMMAND: D
COMMAND: L
1| hello world
COMMAND: J 1
Current Line: 1
COMMAND: A insert after
COMMAND: L
1| hello world
2| insert after
COMMAND: W hello.txt
COMMAND: Q
Terminating the program...
*/