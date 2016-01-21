//============================================================================
// Name        : dog.cpp
// Author      : Jekabz
// Version     :
// Copyright   : 
// Description :
//============================================================================
#include <fstream>
#include <iostream>
#define INPUTFILENAME "32.i8" //TODO before submit, change name
#define OUTPUTFILENAME "suns.out"
#define STRINGSIZE 50
using namespace std;

class Node  // Klase Node - saraksta mezgls
{
    public:
	char content  [STRINGSIZE];
	int length;
    Node *next;
//    Node (int n) { num = n; next = NULL; }; //konstruktors
    Node(char x[], int y) {
         for(int i = 0;i<y; ++i) {
             content[i] = x[i];
         }
         length = y;
         next = NULL;
    }
};

class List  // Klase List - saistīts vienvirziena saraksts
{
    protected:
    Node *first, *last;
    public:
    Node *current;
    public:
    List () { first = last = current = NULL; }; //konstruktors
    void add_element (char x[], int y); // pievieno beigās
    void delete_element (); // izmet no sākuma
    bool is_empty () { return (first == NULL); };
    void start () { current = first; };
    bool end () { return (current == NULL); };
    void next(){if (!end())current = current -> next;};

    // Metodes, kas pievienotas uzdevuma izpildei:
    void sarakstsBackwards();
    void print();

};

void List::add_element (char x[], int y)
{
     Node *p = new Node (x, y);
     if (first == NULL) first = last = p;
     else last = last -> next = p;
     current =p;
};

void List::delete_element ()
{
     Node *p = first;
     if(!is_empty())
     {
         if (current == first) current = first-> next;
         first = first -> next;
         delete p;
         if(is_empty())last = NULL;
     }
};

void List::print() {
	for (start(); !end(); next()) {
//		cout << current->num << endl;
		   for(int i = 0;i<current->length; ++i) {
		             cout<<current->content[i];
		         }
	}
	cout << endl;
};

int main() {
	ifstream inFile(INPUTFILENAME);
	cout << "App start\n";
	if (inFile.is_open()) {
		cout << "File "<< INPUTFILENAME<<endl;
		// count lines in file:
		char trash = NULL;
		int totalInFileLineCount = 0;
		int maxFileRowLenght = 0;
		int currentFileRowLenght = 0;
		int units=1;
		bool flag;
		//counts lines in file:
		while (inFile.get(trash)) {
					if (trash == '\n' and inFile.peek() == '\n') {
						totalInFileLineCount += 1;
						break; // goes out of while loop
					} else if (trash == '\n') {
						totalInFileLineCount += 1; //counts lines in file
					}
		}
		inFile.clear();
		inFile.seekg(0, inFile.beg); //goes to the beginning of file
		while (inFile.get(trash)) {
			if (trash == '\n' and inFile.peek() == '\n') {
				totalInFileLineCount += 1;
				break; // goes out of while loop
			} else if (trash == '\n') {
				totalInFileLineCount += 1; //counts lines in file
				if (currentFileRowLenght >= maxFileRowLenght) {
					maxFileRowLenght = currentFileRowLenght;
				}
				cout<<currentFileRowLenght<<"\t"<<units<<endl;
				currentFileRowLenght = 0;
				flag = false;
				units=1;
			}
			else if(trash ==' ') units++;
			else if( trash !=  ' ' and trash !='"'){
				currentFileRowLenght++;
			}
		}
			inFile.clear();
			inFile.seekg(0, inFile.beg); //goes to the beginning of file
			//TODO 1d array with pointers to efin lists
			List *array[totalInFileLineCount];
			//TODO go through arr and file and read from file, put lists in arr
		int counter = 0;
		while (inFile.get(trash)) {
			if (trash == '\n' or counter == 0) {
				array[counter] = new List;
				counter++;
			} else {
				char dadummts[STRINGSIZE];
				int z = 0;
				while (trash != ' ' and trash != '\n' and trash != '"') {
					inFile >> dadummts[z];
					z++;
				}
				array[counter]->add_element(dadummts, z);
			}
		}
		inFile.close();
		cout << "file gots " << totalInFileLineCount << " lines" << endl;
		cout << "file gots " << maxFileRowLenght << " max line chars" << endl;
		cout <<"PRINT MEMORY:"<<endl;
		for(int r=0; r<totalInFileLineCount; r++){
			array[r]->print();
			cout<<endl;
		}
	}
	else cout<<"No file\n";
	return 0;
}
