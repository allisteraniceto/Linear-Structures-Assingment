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
    int currentLine; //when user prompts to edit/view line, store in here
    string fileName;
    string line;
    ifstream readFile;
    ofstream writeFile;
public:
    TextEditor(); 
    //
    //default constructor
    //
    TextEditor(string); 
    //
    //overloaded constructor
    //
    void setCurrentLine(int);
    //
    //initializes current line
    //
    void load();
    //
    //load .txt file function;
    //
    void write();
    //
    //write .txt file function;
    //
    void makeVec(string);
    //
    //-load text file
    //-insert individual line into each element of the vector list
    //
    int getLastElement();
    //
    //- gets last element of the vector
    //
    void insertAt(string);
    //
    //-insert text AT currentline
    //
    void insertAfter(string);
    //
    //-insert text AFTER currentline
    //
    void listBuffer(vector<string>&);
    //
    //-lists contents of buffer by iterating through vector
    //
    void deleteLines(vector<string>&);
    //-if no number is given, delete current line
    //-if 1 number is given, delete line given
    //-if 2 numbers are given, delete range of lines given
};

TextEditor::TextEditor(){
    this->currentLine=0;
}
TextEditor::TextEditor(string fileName){
    this->fileName=fileName;
}
void TextEditor::makeVec(string file){
    this->fileName=file;
    readFile.open(fileName, ios::in); //open .txt file to read
    while (std::getline(readFile, line)){
        vec.push_back(line);
    }
    readFile.close();
}
void TextEditor::write(){
    writeFile.open(fileName); //open the file
    if (!writeFile){ 
        cout << "ERROR! WRONG FILE!!";
    }
    if (writeFile.is_open()){
        if (vec.size()>1){ //if vector is not empty, write contents to .txt file
            ostream_iterator<string> out_iterator(writeFile, "\n"); //iterator to go through vector
            copy(vec.begin(), vec.end(), out_iterator);
        }
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
int TextEditor::getLastElement(){
    return vec.size()-1;
}
void TextEditor::setCurrentLine(int l){
    this->currentLine=l;
}
void TextEditor::insertAt(string w){
    auto position = vec.begin() + currentLine-1; //iterator (use auto in c++11, instead of vector<int>::iterator)
    vec.insert(position,vec.size(), w); //-1 because of element position
}
void TextEditor::insertAfter(string w){
    auto position = vec.begin() + currentLine;
    vec.insert(position,vec.size(), w);
}
void TextEditor::listBuffer(vector<string> &str){
    int lineNum1;
    int lineNum2;
    if (str.size()==1){ //outputs entire buffer is no lines are given
        for (auto i = vec.begin(); i != vec.end(); i++){
            cout << *i << endl; //* derefrence to output whatever i is pointing at
        } 
    }
    else if (str.size()==2){//outputs current line if 1 line is given
        istringstream(str[1]) >> lineNum1;
        cout << vec[lineNum1-1] << endl;
    }
    else if (str.size()==3){
        istringstream(str[1]) >> lineNum1;
        istringstream(str[2]) >> lineNum2;
        for (auto i=vec.begin()+lineNum1-1; i != vec.begin()+lineNum2-1; i++){
            cout << *i << endl;
        }
    }
    
}
void TextEditor::deleteLines(vector<string> &str){
    int lineNum1;
    int lineNum2;
    if (str.size()==1){ //if no lines are given
        vec.erase(vec.begin()+currentLine); //delete first line
    }
    else if(str.size()==2){
        istringstream(str[1]) >> lineNum1;
        vec.erase(vec.begin()+lineNum1-1);
    }
    else if(str.size()==3){
        istringstream(str[1]) >> lineNum1; //second element is line1
        istringstream(str[2]) >> lineNum2; //third element is line2
        vec.erase(vec.begin()+lineNum1-1, vec.begin()+lineNum2-1);//erase from line1 to line2
    }
}