#include <fstream>
#include <iostream>

#define INPUTFILENAME "parcels.i2" //TODO before submit, change name
#define OUTPUTFILENAME "parcels.out"
#define IDMAX 65000 //zemes gabala max ID vērtība
#define SENTINEL -1
#define MAXLINELENGTH 300

using namespace std;



class Parcel
{
    public:
	int parcelId;
    Parcel *next;
   int vertices[21]={SENTINEL};
    Parcel(int iD, int vert[], int size){
    	this->parcelId=iD;
    	next = NULL;
    	for (int i=0; i<size; i++){
    		vertices[i] = vert[i];
    	}
    }
};

class List
{
    protected:
   Parcel *first, *last;
    public:
    Parcel *current;
    public:
    List () { first = last = current = NULL; }; //konstruktors
    void add_element (int iD, int vert[], int size)
    {
         Parcel *p = new Parcel (iD, vert, size);
         if (first == NULL) first = last = p;
         else last = last -> next = p;
         current =p;
    };
    bool is_empty () { return (first == NULL); };
    void start () { current = first; };
    bool end () { return (current == NULL); };
    void next(){if (!end())current = current -> next;};
	void print() {
		cout << "Print mem START\n";
		for (start(); !end(); next()) {
			cout << current->parcelId << " ";
			for (int i = 0; i < 21; i++) {
				if (current->vertices[i] == SENTINEL)
					break;
				cout << current->vertices[i] << " ";
			}
			cout << "\n";
		}
		cout << "Print mem FIN\n";
	}
};



int main(){
	ifstream inFile(INPUTFILENAME);
	cout << "App start\n";
	if (inFile.is_open()) {
		cout << "File " << INPUTFILENAME << endl;
		char trash;
		int counter=0;

		while (!inFile.eof()) {
			char lineContents[MAXLINELENGTH] = { SENTINEL };
			while (true) {
				inFile >> noskipws >> trash;
				if (trash == '\n')
					break;
				lineContents[counter] = trash;
				counter++;
			}
			counter = 0;
			while (lineContents[counter] != SENTINEL and lineContents[counter] != '\n') {
				//TODO implement algorithm:

				//make an int arr from char arr:
				int tempMem[MAXLINELENGTH /3]= {SENTINEL};
			   int tempMemCounter=0;
			   int charMemCounter = 0;
			   int accumulator = 0;
			   bool swich = true;
			   while(lineContents[charMemCounter] != SENTINEL){
					if (lineContents[charMemCounter] == ' ') {
						charMemCounter++;
						if (swich) { //TODO is this correct?
							tempMem[tempMemCounter] = accumulator;
							tempMemCounter++;
						}
						accumulator = 0;
						continue;  //skips whitespaces
					} else if (lineContents[charMemCounter] == 'A') {
						//TODO
						swich = false;
					} else if (lineContents[charMemCounter] == 'D') {
						//TODO
						swich = false;
					} else if (lineContents[charMemCounter] == 'P') {
						//TODO
						swich = false;
					} else if (lineContents[charMemCounter] == 'K') {
						//TODO
						swich = false;
					} else {
						accumulator += (int) lineContents[charMemCounter] - 48;
						swich = true;
					}
					charMemCounter++;
			   }

			   	   int u=0;
			   do{
				   cout<<lineContents[u]<<"_";
				   u++;
			   }while(lineContents[u]!=SENTINEL);

			   counter++;
		   }
		   counter = 0;

			cout<<endl;

		}
	}
	else cout << "No file\n";
	cout<<"App quit";
}
