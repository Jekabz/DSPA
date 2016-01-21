//============================================================================
// Name        : dog.cpp
// Author      : Jekabz
// Version     :
// Copyright   :
// Description :
//============================================================================
#include <fstream>
#include <iostream>

#define INPUTFILENAME "suns.in" //TODO before submit, change name
#define OUTPUTFILENAME "suns.out"
#define STRINGSIZE 1000
#define STRINGSIZE2 40
#define SENTINEL  454

using namespace std;

void bubbleSortAsc(int arr[]){
	 int temp;
		for (int i = 0; i < STRINGSIZE2; i++) {
			for (int j = i; j < STRINGSIZE2; j++) {
				if (arr[i] > arr[j]) {
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
					continue;
				}
			}
		}
}


bool findValueInIntArray(int arr[], int size, int value){
	for(int t=0; t<size; t++){
		if(arr[t]==value) return true;
		if(arr[t]==SENTINEL) break;
	}
	return false;
}

class Node  // Klase Node - saraksta mezgls, suns
{
    public:
	char name  [55];
	int nameSize;
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
         nameSize=y;
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
    int hasName(char x[], int y){ //padod name arr un size
    	int returnValue=0;
    	int tempValue=0;
		if (y > current->nameSize)
			return 0;
		for (int i = 0; i < current->nameSize ; i++) {
			for (int a = 0; a < y; a++) {
				if(current->name[i+a]!=x[a]){
					break;
				}
				tempValue++;
				if(tempValue==y){
					returnValue++;
					tempValue=0;
				}
			}
		}
	//	cout<<"hasName returns "<<returnValue<<" for "<<x<<endl;
    	return returnValue;
    }
    int nameFinder(char x[], int y, int b[STRINGSIZE2]){
    	int count=0;
    	int z=0;
    	for(start(); !end(); next(), z++){
    		count+=this->hasName(x, y);
			if (this->hasName(x, y) > 0) {
				b[z] = this->current->id;
				//cout<<"fun "<<this->current->id;
			}
    	}
    	return count;
    }
};

int main() {
//	for (int i=0;i<STRINGSIZE2; i++){
//		idArr[i]=SENTINEL;
//	}



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

		cout << "PRINT MEMORY:" << endl;
		for (int a = 0; a < j; a++) {
			cout << memo[a];
		}
		cout<<endl;
		cout << "PRINT MEMORY FINISHED:" << endl;

		//Algoritms uzdevuma izpildei:
		//TODO make memory:
//		char dogMemo[STRINGSIZE];
//		for (int i = 0; i < STRINGSIZE; i++) { dogMemo[i]='*'; }
		ofstream outFile(OUTPUTFILENAME);
		//R command history array:
		int history[STRINGSIZE/10]={SENTINEL};
		int i=0;
		List dogs;

		do{
			if(memo[i] == 'R' and memo[i+1] == '_'){
				if(findValueInIntArray(history, STRINGSIZE/100, memo[i+2])){
					outFile<<"no"<<endl;
				}else{
					i+=2;
					int iD=((int)memo[i]-48); //fixme only smaller values than 10 allowed;
					i+=2;
					char temp[500];
					int tempCounter=0;
					do{
						temp[tempCounter]=memo[i];
						tempCounter++;
						i++;
					}while(memo[i]!='/');
					dogs.add_element(temp, tempCounter, iD);
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
						if(memo[e]=='_'){
						outFile<<' ';
						}else outFile<<memo[e];
						e++;
					}while(memo[e]!='/');
					outFile<<"\""<<endl;
				}else{
					outFile<<"no"<<endl;
				}
			}
			if(memo[i] == 'F' and memo[i+1] == '_'){
				//what to find?
				i+=2;
				int counter=0;
				char findThis[50] = {'*'};
				while(true){
					findThis[counter]=memo[i];
					i++;
					counter++;
					if(memo[i]=='/')break;
				}
				//now find it?
				int b[STRINGSIZE2];
				for(int i=0; i<STRINGSIZE2; i++){
					b[i]=88;
				}
				int d = dogs.nameFinder(findThis, counter, b);
				cout<<"Found "<<d<<" occurances of "<<findThis<<endl;
				//sort arr asc:
				cout << "bubbleSort started" << endl;
				bubbleSortAsc(b);
				cout << "bubbleSort finished" << endl;
				outFile << d << " ";
				int r=0;
				do{
					outFile<<b[r]<<" ";
					r++;
				}while(b[r]!=88);
				outFile<<endl;

			}
			i++;
		}while (memo[i] != 'Q');
		outFile<<"quit"<<endl;
		outFile.close();
		//end of Algoritms
		cout<<"Quit program";
	} else
		cout << "No file\n";
	return 0;
}
