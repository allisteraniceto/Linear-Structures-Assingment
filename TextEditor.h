#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

//use each line as an element in the list 
//using a list (vector) to easily access a line and make changes

//HOW THE VECTOR IS BEING USED:
//create a vector   
//read file into vector list
//if no file, create a vector
//then 
//write list back onto the text file

//rubric:
//NEED: to use try, catch, throw (exception handling)
//commands are CASE SENSITIVE!

class TextEditor{
private:
    vector<string> vec; //store a list of strings for each line
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
    void write();
    /*
    write .txt file function;
    */
    void makeVec(string);
    /*
    -load text file
    -insert individual line into each element of the vector list
    */
    void writeVec();
    /*
    -
    */
};

TextEditor::TextEditor(){
    this->lineNum=0;
}
TextEditor::TextEditor(string fileName){
    this->fileName=fileName;
}
void TextEditor::write(){
    writeFile.open(fileName); //open the file
    /* if (!writeFile){ 
        cout << "ERROR! WRONG FILE!!";
    } */
    if (writeFile.is_open()){
        ostream_iterator<string> out_iterator(writeFile, "\n"); //iterator to go through vector
        copy(vec.begin(), vec.end(), out_iterator); 
    }
    writeFile.close(); //remember to close the file after
}
void TextEditor::load(){
    readFile.open(fileName); //remove \n at the end of string
    if (!readFile){
        cout << "ERROR! WRONG FILE!!";
    }
    getline(readFile, line);
    readFile.close();
}
void TextEditor::makeVec(string file){
    this->fileName=file;
    readFile.open(fileName); //open .txt file
    while (readFile>>line){
        vec.push_back(line);
    }
}