#include <iostream>
#include <fstream>
using namespace std;

#define INPUTFILENAME "5budget.in"
#define OUTPUTFILENAME "budget.out"
/*
 * SENTINEL is used as
 *any value between 0 and 4294967295,
 *Program will have unpredictable behavior
 * if input has this value
 */
#define SENTINEL 	4440444
#define ERRMEMSIZE  100

//
//bool memoryIsAllChecked(int memorySize, bool ignoreList[], int headerRows) {
//	for (int j = headerRows; j < memorySize + headerRows; j++) {
//		if (ignoreList[j] == false)
//			return false;
//	}
//	return true;
//}
//
//void Error_4_Check(unsigned long int memory[][3], int memorySize, int headerRows) { //cheks for 4th error type
//	//First, we need memory for our findings
//	//FIXME ERRMEMSIZE works, but is wasteful
//	long long int resultMemory[ERRMEMSIZE][2];
//	for (int i = 0; i < ERRMEMSIZE; i++) {
//		for (int j = 0; j < 2; j++) {
//			resultMemory[i][j] = 0;
//		}
//	}
//	int nextPosition=0;
//
//	//TODO make bool arr so we can ignore memory lines
//	bool ignoreList[memorySize];
//	for(int i=0; i<memorySize; i++){
//		ignoreList[i]=false;
//	}
//
//	//TODO start checking for inconsistencies:
//	// find the largest parent position
//	//sum of value for these nodes must be gathered
//	//ignore those lines
//	long long int max = memory[0][headerRows + 1];
//
//	do {
//		max=0; //reset
//		for (int j = headerRows; j < memorySize + headerRows; j++) {
//			if (max < memory[j][0] and ignoreList[j] == false) {
//				max = memory[j][0];
//			}
//		}
//		long long int sum = 0;
//		for (int j = headerRows; j < memorySize + headerRows; j++) {
//			if (memory[j][0] == max) {
//				sum += memory[j][2];
//				ignoreList[j] = true;
//			}
//		}
//		for (int j = 0; j < memorySize + headerRows; j++) {
//			//This is for header rows:
//			if (ignoreList[j] == false and memory[j][0] == max) {
//				long long int diff1=memory[j][2] - sum;
//				if (diff1 > 0) {
//					if(diff1> 4000000000){diff1=4000000001;}
//					resultMemory[nextPosition][0] = diff1;
//					resultMemory[nextPosition][1] = max;
//					nextPosition++;
//				}
//			}
//			//This is for the rest of memory:
//			if (memory[j][1] == max) {
//				long long int diff1=memory[j][2] - sum;
//				if (diff1 > 0) {
//					if(diff1> 4000000000){diff1=4000000001;}
//					resultMemory[nextPosition][0] = diff1;
//					resultMemory[nextPosition][1] = max;
//					nextPosition++;
//				}
//			}
//		}
//	} while (memoryIsAllChecked(memorySize, ignoreList, headerRows)==false );
//
//	//Checks for parent-child relationship, ads summs, if found:
//
//	for (int i = 0; i < ERRMEMSIZE; i++) {
//		if( resultMemory[i][1] == 0 and  resultMemory[i][1] == 0 ) break; //Resultmemory ended
//		for (int j = headerRows; j < memorySize + headerRows; j++) {
//			if (memory[j][1] == resultMemory[i][1]) {
//				for(int x=0; x<ERRMEMSIZE-i; x++){
//					if( resultMemory[x][1] == 0 and  resultMemory[x][1] == 0 ) break; //Resultmemory ended
//					if(memory[j][0]==resultMemory[x][1]){
//						resultMemory[x][0]+=resultMemory[i][0];
//						break;
//					}
//				}
//			}
//		}
//	}
//
////TODO memory has all the proper info, but its fucked up
//	//count lines
//	int linecount=0;
//	for (int i = 0; i < ERRMEMSIZE; i++) {
//		if( resultMemory[i][1] == 0 and  resultMemory[i][1] == 0 ) break; //Resultmemory ended
//		else linecount++;
//	}
//	long long int fixedResultMem[linecount][2];
//
//	//inverts that shit and copies it to new arr
////	for (int i = linecount; i >0 ; i--) {
////		fixedResultMem[linecount-i][0]=resultMemory[i-1][0];
////		fixedResultMem[linecount-i][1]=resultMemory[i-1][1];
////	}
//
//	std::cout << "start memo is" << std::endl;
//	std::cout << "=======================" << std::endl;
//	for(int i=0; i< ERRMEMSIZE; i++){
//		std::cout<< resultMemory[i][0]<<" "<< resultMemory[i][1]<<std::endl;
//	}
//	std::cout << "=======================" << std::endl;
////TODO search for biggest value
//	long long int maxVal = resultMemory[0][0];
//	int dummy=0;
//	for (int a= 0;  a < linecount; a++) {
//		for (int i = 0; i < linecount; i++) {
//			if (maxVal < resultMemory[i][0]) {
//				maxVal = resultMemory[i][0];
//				std::cout << "max is"<<maxVal << std::endl;
//				dummy = resultMemory[i][1];
//				resultMemory[i][0] = -1;
//			}
//		}
//		fixedResultMem[a][0]=maxVal;
//		fixedResultMem[a][1]=dummy;
//	}
//
//	//biggest value found, time to put it in fixed arr:
////	fixedResultMem[][]
//
//	std::cout << "fixed memo is" << std::endl;
//	std::cout << "=======================" << std::endl;
//	for(int i=0; i<linecount; i++){
//		std::cout<<fixedResultMem[i][0]<<" "<<fixedResultMem[i][1]<<std::endl;
//	}
//
//}
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

int main(){
	cout << "=======================" << endl;
	cout << "Starting..." << endl;
	cout << "=======================" << endl;

	ifstream inFile(INPUTFILENAME);
	int totalInFileLineCount = 0;
	if (inFile.is_open()) {
		// count lines in file:
		char trash = NULL;
		while (inFile.get(trash)) {
			if (trash == '\n')
				totalInFileLineCount+= 1;
		}
		cout << "totalInFileLineCount =   " << totalInFileLineCount << endl;
		inFile.clear();
		inFile.seekg(0, inFile.beg); //goes to the beginning of file

		int headerRows = 0;
		inFile >> headerRows;
		cout <<"headerRows = " << headerRows <<endl;
		int memorySize = totalInFileLineCount - headerRows -1;
		cout << "memorySize = "<< memorySize<<endl;
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
		cout << "=======================" << endl;
		cout << "printing memory" << endl;
		cout << "=======================" << endl;
		for (int i = 0; i < memoryArraySize; i++) {
					for (int j = 0; j < 3; j++) {
						cout << memory[i][j] << " ";
					}
					cout << std::endl;
				}
		cout << "=======================" << endl;
		cout << "printing memory finished" << endl;
		cout << "=======================" << endl;

		ofstream myfile;   myfile.open ("budget.out");  //make ut file

		if(!Error_1( memory,  memorySize, headerRows, myfile)){
			myfile << "Correct budget\nNo any common position";
		}
	}
	cout << "=======================" << endl;
	cout << "Finished" << endl;
	cout << "=======================" << endl;
}
