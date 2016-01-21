//============================================================================
// Name        : dog.cpp
// Author      : Jekabz
// Version     :
// Copyright   :
// Description :
//============================================================================
#include <fstream>
#include <iostream>
#define INPUTFILENAME "32.i1" //TODO before submit, change name
#define OUTPUTFILENAME "suns.out"
#define STRINGSIZE 10000
#define SENTINEL  -1
using namespace std;


class Node  // Klase Node - saraksta mezgls, suns
{
    public:
	char name  [55];
	bool alive;
	int id;
    Node *next;

    Node(char x[], int y, int id) {
         for(int i = 0;i<y; ++i) {
            name[i] = x[i];
         }
         next = NULL;
         this->id=id;
         alive=true;
    }
};

class List
{
    protected:
    Node *first, *last;
    public:
    Node *current;
    public:
    List () { first = last = current = NULL; }; //konstruktors
    void add_element (char x[], int y, int id)
    {
         Node *p = new Node (x, y, id);
         if (first == NULL) first = last = p;
         else last = last -> next = p;
         current =p;
    };
    bool is_empty () { return (first == NULL); };
    void start () { current = first; };
    bool end () { return (current == NULL); };
    void next(){if (!end())current = current -> next;};
};



int main() {
	ifstream inFile(INPUTFILENAME);
	cout << "App start\n";
	if (inFile.is_open()) {
		cout << "File " << INPUTFILENAME << endl;
		char trash;
		char memo[STRINGSIZE];
		for (int i = 0; i < STRINGSIZE; i++) {
			memo[i] = '*'; //This is sentinel value, sorry
		}
		int j = 0;
		while (!inFile.eof()) {
			inFile >> noskipws >> trash; //avoids skipping spaces
			if (trash == '"')
				continue;
			else if (trash == ' ')
				memo[j] = '_';
			else if (trash == '\n')
				memo[j] = '/';
			else
				memo[j] = trash;
			j++;
		}
		inFile.close();

		List dogs;

		//Algoritms uzdevuma izpildei:
		//TODO make memory:
//		char dogMemo[STRINGSIZE];
//		for (int i = 0; i < STRINGSIZE; i++) { dogMemo[i]='*'; }
		ofstream outFile(OUTPUTFILENAME);
		//R command history array:
		int history[STRINGSIZE/100]={SENTINEL};
		int i=0;
		do{
			if(memo[i] == 'R' and memo[i+1] == '_'){
				if(findValueInIntArray(history, STRINGSIZE/100, memo[i+2])){
					outFile<<"no"<<endl;
				}else{
					char name[50];
					int counter=2;
					int id=0;
					do {
						name[counter - 2] = memo[i + counter];
						counter++;
					} while (memo[i + counter] != '/');
					do {
						name[counter-2]=memo[i+counter];
						counter++;
					}while(memo[i+counter] !='/');
					dogs.add_element(name, counter-2, );
					outFile<<"ok"<<endl;
				}
			}
			if(memo[i] == 'I' and memo[i+1] == '_'){
				int e=0;
				do{
					e++;
					if(memo[i+2] == memo[e]) break;
				}while( memo[e] !='Q');
				if(memo[e] != 'Q'){
					//found it
					e+=2;
					outFile<<"\"";
					do{
						outFile<<memo[e];
						e++;
					}while(memo[e]!='/');
					outFile<<"\""<<endl;
				}else{
					outFile<<"no"<<endl;
				}
			}
			if(memo[i] == 'F' and memo[i+1] == '_'){

			}
			i++;
		}while (memo[i] != 'Q');
		outFile<<"quit"<<endl;
		outFile.close();
		//end of Algoritms
	} else
		cout << "No file\n";
	return 0;
}
