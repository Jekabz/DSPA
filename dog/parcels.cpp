/*
 * parcels.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: jekabz
 */
#include <iostream>
#include <fstream>
#define INPUTFILENAME "parcels.i5"
#define OUTPUTFILENAME "parcels.out"
#define MAXCOORDINATECOUNT 10 //FIXME this can be counted from file ?
#define  A 10
#define  D 11
#define  P 12
#define  K 13
#define  SENTINEL 	200200204
/*
 * SENTINEL, A, D, P, K is used as
 *any value between 0 and 4294967295,
 *Program will have unpredictable behavior
 * if input has any of these values
 */
using namespace std;

int findBiggestValueInIntArray(int arr[], int size){
	int biggest=arr[0];
	for(int t=0; t<size; t++){
		if(arr[t]>biggest) biggest = arr[t];
	}
	return biggest;
}

int main() {
	ifstream inFile(INPUTFILENAME);
	int totalInFileLineCount = 0;
	if (inFile.is_open()) {
		// count lines in file:
		char trash = NULL;
		int longestRowValue=0;
		int currentRowValue=0;
		bool commandA= false;
		int coordinateCount=0;
		int commandACount=0;
		//counts lines in file:
		while (inFile.get(trash)) {
			if(trash == '\n' and inFile.peek() ==  '\n'){
				totalInFileLineCount += 1;
				break;
			}
			else if (trash == '\n') totalInFileLineCount += 1; //counts lines in file
		}
		inFile.clear();
		inFile.seekg(0, inFile.beg); //goes to the beginning of file
		while (inFile.get(trash)) {
			if (trash =='A') commandACount += 1; //Counts A commands
		}
		int coordinateCountArray[commandACount ];
		for(int i=0; i<commandACount; i++){
			coordinateCountArray[i]=0;
		}
		inFile.clear();
		inFile.seekg(0, inFile.beg); //goes to the beginning of file
		int i=0;
		while (inFile.get(trash)) {

					if (trash == 'A') commandA = true;
					if (commandA){
//						cout<<"A command found!"<<endl;
						//skips parcel num:
						inFile.get(trash); //skips 'A'
						inFile.get(trash); //skips ' '
						do{
//							cout<<"skipping simbol ["<<trash<<"]"<<endl;
							if(trash == ' ') break;
						}while(inFile.get(trash));
						//retrieves coordinate count:
//						cout<<"got to count"<<endl;
						while (inFile.get(trash)) {
							if (trash == ' '){
								i++;
								break;
							}
							coordinateCountArray[i]*=10;
							coordinateCountArray[i]+=((int)trash-'0');
						}
						commandA=false;
					}
				}
		inFile.clear();
		inFile.seekg(0, inFile.beg); //goes to the beginning of file

		int largestCoordinateCount = findBiggestValueInIntArray(coordinateCountArray, commandACount);
		cout<<"Biggest coordinate count is: "<<largestCoordinateCount<<endl;

		int memoyWith=4+largestCoordinateCount;
		unsigned long int memory[totalInFileLineCount][memoyWith] ;
		for(int i=0; i<totalInFileLineCount; i++){
			for( int j=0 ; j<memoyWith; j++){
				memory[i][j]=SENTINEL;
			}
		}

		for(int s=0; s< totalInFileLineCount; s++){ //take a look at every file line
			//TODO read from file:
			char command=NULL;
			memory[s][0]=0;
			int t=0;
			while(inFile.get(command)){

				cout<<"current char is: "<<command<<endl;
				memory[s][0]*=10;
				memory[s][0]+=((int)command-'0');
				inFile >> command;
				t++;
			}
//			inFile >> memory[s][0];
			inFile >> command;
			if (command == 'A') memory[s][1] = A;
			else if (command == 'D') memory[s][1] = D;
			else if (command == 'P') memory[s][1] = P;
			else if (command == 'K') memory[s][1] = K;

		}


		inFile.close();
		cout << "Print memory:\n";
		for (int i = 0; i < totalInFileLineCount; i++) {
			for (int j = 0; j < memoyWith; j++) {
				cout << memory[i][j] << " ";
			}
			cout << endl;
		}
		cout << "End of memory\n";
	} /*if (inFile.is_open()) */
	else
		cerr << "Cannot open file\n";
		cout << "Return exit code 0:\n";

} /* main */
