#include <iostream>
#include <fstream>

#define INPUTFILENAME "budget3.in"
#define OUTPUTFILENAME "budget.out"
#define ERRMEMSIZE 20

bool file_exists(const char *fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}

void Error_1_Check() {
} // ministrijai ir tikai viens bērns
void Error_2_Check() {
} // node has no parent
void Error_3_Check() {
} //
//void Error_4_Check( int arr[][3]){ // sums dont mach
//	int difference=0;
//	int i=0;
//	while(arr[i][0]!=0 and i< MEMORYSIZE){
//		std::cout<<"Test"<<std::endl;
//		i++;
//	}
//}

bool memoryIsAllChecked(int memorySize, bool ignoreList[], int headerRows) {
	for (int j = headerRows; j < memorySize + headerRows; j++) {
		if (ignoreList[j] == false)
			return false;
	}
	return true;
}

void Error_4_Check(long long int memory[][3], int memorySize, int headerRows) { //cheks for 4th error type
	//First, we need memory for our findings
	//FIXME ERRMEMSIZE works, but is wasteful
	long long int resultMemory[ERRMEMSIZE][2];
	for (int i = 0; i < ERRMEMSIZE; i++) {
		for (int j = 0; j < 2; j++) {
			resultMemory[i][j] = 0;
		}
	}
	int nextPosition=0;

	//TODO make bool arr so we can ignore memory lines
	bool ignoreList[memorySize];
	for(int i=0; i<memorySize; i++){
		ignoreList[i]=false;
	}

	//TODO start checking for inconsistencies:
	// find the largest parent position
	//sum of value for these nodes must be gathered
	//ignore those lines
	long long int max = memory[0][headerRows + 1];

	do {
		max=0; //reset
		for (int j = headerRows; j < memorySize + headerRows; j++) {
			if (max < memory[j][0] and ignoreList[j] == false) {
				max = memory[j][0];
			}
		}
		long long int sum = 0;
		for (int j = headerRows; j < memorySize + headerRows; j++) {
			if (memory[j][0] == max) {
				sum += memory[j][2];
				ignoreList[j] = true;
			}
		}
		for (int j = 0; j < memorySize + headerRows; j++) {
			//This is for header rows:
			if (ignoreList[j] == false and memory[j][0] == max) {
				long long int diff1=memory[j][2] - sum;
				if (diff1 > 0) {
					if(diff1> 4000000000){diff1=4000000001;}
					resultMemory[nextPosition][0] = diff1;
					resultMemory[nextPosition][1] = max;
					nextPosition++;
				}
			}
			//This is for the rest of memory:
			if (memory[j][1] == max) {
				long long int diff1=memory[j][2] - sum;
				if (diff1 > 0) {
					if(diff1> 4000000000){diff1=4000000001;}
					resultMemory[nextPosition][0] = diff1;
					resultMemory[nextPosition][1] = max;
					nextPosition++;
				}
			}
		}
	} while (memoryIsAllChecked(memorySize, ignoreList, headerRows)==false );

	//Checks for parent-child relationship, ads summs, if found:

	for (int i = 0; i < ERRMEMSIZE; i++) {
		if( resultMemory[i][1] == 0 and  resultMemory[i][1] == 0 ) break; //Resultmemory ended
		for (int j = headerRows; j < memorySize + headerRows; j++) {
			if (memory[j][1] == resultMemory[i][1]) {
				for(int x=0; x<ERRMEMSIZE-i; x++){
					if( resultMemory[x][1] == 0 and  resultMemory[x][1] == 0 ) break; //Resultmemory ended
					if(memory[j][0]==resultMemory[x][1]){
						resultMemory[x][0]+=resultMemory[i][0];
						break;
					}
				}
			}
		}
	}

//TODO memory has all the proper info, but its fucked up
	//count lines
	int linecount=0;
	for (int i = 0; i < ERRMEMSIZE; i++) {
		if( resultMemory[i][1] == 0 and  resultMemory[i][1] == 0 ) break; //Resultmemory ended
		else linecount++;
	}
	long long int fixedResultMem[linecount][2];

	//inverts that shit and copies it to new arr
//	for (int i = linecount; i >0 ; i--) {
//		fixedResultMem[linecount-i][0]=resultMemory[i-1][0];
//		fixedResultMem[linecount-i][1]=resultMemory[i-1][1];
//	}

	std::cout << "start memo is" << std::endl;
	std::cout << "=======================" << std::endl;
	for(int i=0; i< ERRMEMSIZE; i++){
		std::cout<< resultMemory[i][0]<<" "<< resultMemory[i][1]<<std::endl;
	}
	std::cout << "=======================" << std::endl;
//TODO search for biggest value
	long long int maxVal = resultMemory[0][0];
	int dummy=0;
	for (int a= 0;  a < linecount; a++) {
		for (int i = 0; i < linecount; i++) {
			if (maxVal < resultMemory[i][0]) {
				maxVal = resultMemory[i][0];
				std::cout << "max is"<<maxVal << std::endl;
				dummy = resultMemory[i][1];
				resultMemory[i][0] = -1;
			}
		}
		fixedResultMem[a][0]=maxVal;
		fixedResultMem[a][1]=dummy;
	}

	//biggest value found, time to put it in fixed arr:
//	fixedResultMem[][]

	std::cout << "fixed memo is" << std::endl;
	std::cout << "=======================" << std::endl;
	for(int i=0; i<linecount; i++){
		std::cout<<fixedResultMem[i][0]<<" "<<fixedResultMem[i][1]<<std::endl;
	}

}

int main() {
	std::cout << "=======================" << std::endl;
	std::cout << "Starting" << std::endl;
	std::cout << "=======================" << std::endl;
	if (file_exists(INPUTFILENAME)) {
		std::ifstream inFile(INPUTFILENAME);
		int lineCount = 0;
		if (inFile.is_open()) {
			// count lines in file:
			char trash = NULL;
			while (inFile.get(trash)) {
				if (trash == '\n')
					lineCount += 1;
			}
			std::cout << "lineCount  " << lineCount << std::endl;
			inFile.clear();
			inFile.seekg(0, inFile.beg);

			int headerRows = 0; 	//Count of header rows
			inFile >> headerRows;
			int headerRowsProper = headerRows;
			std::cout << "headerRows  " << headerRows << std::endl;
			int memorysize = lineCount - headerRows - 1;
			std::cout << "memorysize  " << memorysize << std::endl;

			long long int memory[memorysize][3];

			int inFileRows = 0;
			int tmp1 = NULL, tmp2 = NULL, tmp3 = NULL;
			while (true) {
				inFile >> tmp1;
//				if (!tmp1)
//					break;
				if (inFileRows >= headerRows)
					inFile >> tmp2;
				else
					tmp2 = -1;
				inFile >> tmp3;
				if(!tmp1 and !tmp2 and !tmp3) break;
//				std::cout<<" - "<<tmp1<<" "<<tmp2<<" "<<tmp3<<std::endl;

				bool foundDuplicates = false;
				for (int i = 0; i < inFileRows; i++) {
					if (tmp1 == memory[i][0] and tmp2 == memory[i][1] and tmp3 == memory[i][2]) {
						foundDuplicates = true;
						break;
					}
				}

				if (!foundDuplicates) {
					memory[inFileRows][0] = tmp1;
					memory[inFileRows][1] = tmp2;
					memory[inFileRows][2] = tmp3;
					inFileRows++;
					std::cout<<" - "<<tmp1<<" "<<tmp2<<" "<<tmp3<<std::endl;
				}
				tmp1 = tmp2 = tmp3 = NULL;
			}
			inFileRows++; //quick and dirty workaround, sorry
			std::cout << "File has " << inFileRows << " rows" << std::endl;
			inFile.close();

			std::cout << "=======================" << std::endl;
			std::cout << "printing memory" << std::endl;
			std::cout << "=======================" << std::endl;
			for (int i = 0; i < headerRows+memorysize; i++) {
				for (int j = 0; j < 3; j++) {
					std::cout << memory[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "=======================" << std::endl;
			std::cout << "printing memory finished" << std::endl;
			std::cout << "=======================" << std::endl;
			std::cout << "starting Error_4_Check" << std::endl;
			std::cout << "=======================" << std::endl;
			Error_4_Check ( memory,  memorysize,  headerRowsProper);
			std::cout << "=======================" << std::endl;
			std::cout << "Error_4_Check finished" << std::endl;
			std::cout << "=======================" << std::endl;
		}

	} else {
		std::cout << " No file";
	}
	std::cout << "Finishing" << std::endl;
	std::cout << "=======================" << std::endl;
	return 0;
}
