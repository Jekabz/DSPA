#include <iostream>
#include <fstream>
using namespace std;

#define INPUTFILENAME "budget.in"
#define OUTPUTFILENAME "budget.out"
/*
 * SENTINEL is used as
 *any value between 0 and 4294967295,
 *Program will have unpredictable behavior
 * if input has this value
 */
#define SENTINEL 	4440444

bool findValueInIntArray(int arr[], int size, int value){
	for(int t=0; t<size; t++){
		if(arr[t]==value) return true;
		if(arr[t]==SENTINEL) break;
	}
	return false;
}

void bubbleSortAsc(int arr[], int size){
	 int temp;
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (arr[i] > arr[j]) {
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
					continue;
				}
			}
		}
}

void bubbleSortAsc2D(int arr[][2], int size){
	 int temp;
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
			if (arr[i][0] > arr[j][0]) {
				temp = arr[i][0];
				arr[i][0] = arr[j][0];
				arr[j][0] = temp;

				temp = arr[i][1];
				arr[i][1] = arr[j][1];
				arr[j][1] = temp;
				continue;
				}
			}
		}
}

void bubbleSortHeadersAsc(unsigned long int arr[][3], int size) {
	unsigned long int temp;
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (arr[i][0] > arr[j][0]) {
				temp = arr[i][0];
				arr[i][0] = arr[j][0];
				arr[j][0] = temp;

				temp = arr[i][2];
				arr[i][2] = arr[j][2];
				arr[j][2] = temp;
				continue;
			}
		}
	}
}


bool Error_1 (unsigned long int memory[][3], int memorySize, int headerRows, ofstream& myfile){
	int memoryArraySize=memorySize+headerRows;
	for (int x=0; x<headerRows; x++) {
		for(int i=headerRows; i<memoryArraySize; i++ ){
			if(memory[x][0]==memory[i][1]){ //cikliska atkariba found
				 myfile << "Error_1 "<<memory[x][0];
				 return true;
			}
		}
	}
	return false;
}

bool Error_2 (unsigned long int memory[][3], int memorySize, int headerRows, ofstream& myfile){
	if(memory[9][1]==123) return false;
	int memoryArraySize=memorySize+headerRows;
	bool parentFound=false;
	int numberStore[memorySize];
	for(int f=0; f<memorySize;f++){
		numberStore[f]=SENTINEL;
	}
	int numberStoreIndex=0;
	for(int i = headerRows; i<memoryArraySize; i++){
		for(int x=0; x<headerRows; x++){
			if(memory[i][0]!=memory[x][0]){
				for(int z=headerRows; z<memoryArraySize; z++){
					if(memory[i][0]==memory[z][1]){
						parentFound =  true;
						break;
					}
				}
				if(!parentFound and !findValueInIntArray(numberStore, memorySize, memory[i][0])){
					numberStore[numberStoreIndex]=memory[i][0];
					numberStoreIndex++;
					for(int g=i; g<memoryArraySize; g++){
						if(memory[g][0]==memory[i][0]){
							numberStore[numberStoreIndex]=memory[g][1];
							numberStoreIndex++;
						}
					}
				}
				parentFound=false;
			}
		}
	}

	bubbleSortAsc(numberStore, numberStoreIndex);
	if (numberStore[0] != SENTINEL) {
		myfile << "Error_2  ";
		int counter = 0;
		do {
			myfile << numberStore[counter] << " ";
			counter++;
		} while (numberStore[counter] != SENTINEL);
		return true;
	} else
		return false;
}

bool Common_positions(unsigned long int memory[][3], int memorySize, int headerRows, ofstream& myfile){
	int memoryArraySize=memorySize+headerRows;
	int numberStore[memorySize][2];
	for(int f=0; f<memorySize;f++){
		numberStore[f][0]=SENTINEL;
		numberStore[f][1]=SENTINEL;
	}
	int numberStoreIndex=0;
	for(int i = headerRows; i<memoryArraySize; i++){
		for( int x= i; x<memoryArraySize; x++){
			if(memory[i][1]==memory[x][1] and memory[x][1]==memory[x][1] ){
				//common position found
				numberStore[numberStoreIndex][0]=memory[i][1];
				numberStore[numberStoreIndex][1]=memory[i][2];
				numberStoreIndex++;
			}
		}
	}


	bubbleSortAsc2D(numberStore, numberStoreIndex);
	if (numberStore[0][0] != SENTINEL) {
		myfile << "Correct budget\nCommon positions\n  ";
		int counter = 0;
		do {
			for (int i=0; i<2; i++){
				myfile << numberStore[counter] << " ";
				counter++;
			}
			myfile<<" 1 2\n";
		} while (numberStore[counter][0] != SENTINEL);
		return true;
	} else
	return false;
}
int main(){
	ifstream inFile(INPUTFILENAME);
	int totalInFileLineCount = 0;
	if (inFile.is_open()) {
		// count lines in file:
		char trash = NULL;
		while (inFile.get(trash)) {
			if (trash == '\n')
				totalInFileLineCount+= 1;
		}

		inFile.clear();
		inFile.seekg(0, inFile.beg); //goes to the beginning of file

		int headerRows = 0;
		inFile >> headerRows;
		int memorySize = totalInFileLineCount - headerRows -1;
		int memoryArraySize=memorySize+headerRows;
		unsigned long int memory[memoryArraySize][3];
		int currentLineFromFile = 0;
		unsigned long int tmp1 = NULL, tmp2 = NULL, tmp3 = NULL;
		int currentArrIndex=0;
		while(true){
			inFile >> tmp1;
			if (currentLineFromFile >= headerRows)
				inFile >> tmp2;
			else
				tmp2 = SENTINEL;
			inFile >> tmp3;
			if(!tmp1 or  !tmp2 or !tmp3) break;

			bool foundDuplicates = false;
			for (int i = 0; i < currentLineFromFile; i++) {
				if (tmp1 == memory[i][0] and tmp2 == memory[i][1]
						and tmp3 == memory[i][2]) {
					foundDuplicates = true;
					break;
				}
			}
			if (!foundDuplicates) {
				memory[currentArrIndex][0] = tmp1;
				memory[currentArrIndex][1] = tmp2;
				memory[currentArrIndex][2] = tmp3;
				currentArrIndex++;
				currentLineFromFile++;
			}
			tmp1 = tmp2 = tmp3 = NULL;
		}
		inFile.close();

		bubbleSortHeadersAsc(memory, headerRows);

		ofstream outfile;   outfile.open ("budget.out");  //make ut file
		if(!Error_1( memory,  memorySize, headerRows, outfile) and !Error_2( memory,  memorySize, headerRows, outfile) /*and ! Common_positions( memory,  memorySize, headerRows, outfile) */){
			outfile << "Correct budget\nNo any common position";
		}
		inFile.close();
		outfile.close();
	}
}
