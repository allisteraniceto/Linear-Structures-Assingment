#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

//use each line as an element in the list 
//using a list (vector) to easily access a line and make changes

//HOW THE VECTOR IS BEING USED:    
//read list into vector list
//then
//write list back onto the text file

//rubric:
//NEED: to use try, catch, throw (exception handling)
//commands are CASE SENSITIVE!

class TextEditor{
private:
    vector<string> lines; //store a list of strings for each line
    int lineNum; //when user prompts to edit/view line, store in here
    string fileName;
    string line;
    ifstream readFile;
    ofstream writeFile;
public:
    TextEditor(); 
    /*
    default constructor
    */
    TextEditor(string); 
    /*
    overloaded constructor
    */
    void load();
    /*
    load .txt file function;
    */
    void write(string);
    /*
    write .txt file function;
    */
    void makeVec();
    /*
    -load text file
    -insert individual line into each element of the vector list
    */
};

TextEditor::TextEditor(){
    this->lineNum=0;
    this->fileName="file.txt";
}
TextEditor::TextEditor(string fileName){
    this->fileName=fileName;
}
void TextEditor::write(string line){
    writeFile.open(fileName);
    if (!writeFile){
        cout << "ERROR! WRONG FILE!!";
    }
    if (writeFile.is_open()){
        writeFile << line << "\n";
    }
}
void TextEditor::load(){
    readFile.open(fileName);
    if (!readFile){
        cout << "ERROR! WRONG FILE!!";
    }
    getline(readFile, line);
}
void TextEditor::makeVec(){
    readFile.open(fileName); //open .txt file
}