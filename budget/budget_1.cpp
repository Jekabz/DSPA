#include <iostream>
#include <fstream>
//#include <sys/stat.h>
#define INPUTFILENAME "budget.in"
#define OUTPUTFILENAME "budget.out"
#define MEMORYSIZE 10000
//#define ERRORMEMORYSIZE 100

//long GetFileSize(std::string filename)
//{
//    struct stat stat_buf;
//    int rc = stat(filename.c_str(), &stat_buf);
//    return rc == 0 ? stat_buf.st_size : -1;
//}

bool file_exists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void Error_1_Check(){} // ministrijai ir tikai viens bērns
void Error_2_Check(){} // node has no parent
void Error_3_Check(){} //
void Error_4_Check( int arr[][3]){ // sums dont mach
	int difference=0;
	int i=0;
	while(arr[i][0]!=0 and i< MEMORYSIZE){
		std::cout<<"Test"<<std::endl;
		i++;
	}
}

int main() {
	std::cout << "Starting" << std::endl;
		if (file_exists(INPUTFILENAME)) {
//		long Size = GetFileSize(INPUTFILENAME);
//		std::cout <<"File size is "<< Size <<" bytes"<<std::endl; //by default filesize is 3bytes, adding one simbol or newline adds one byte
		std::ifstream inFile(INPUTFILENAME);
		int tempmemory[MEMORYSIZE][3]={0};
		if (inFile.is_open()) {
			int headerRows; 	//Count of header rows
			inFile >> headerRows;
			int inFileRows=0;
			int tmp1=NULL, tmp2=NULL, tmp3=NULL;
			while(true){
				inFile >> tmp1;
				if(!tmp1) break;
				if(inFileRows>=headerRows) inFile >> tmp2;
				else tmp2 = -1;
				inFile >> tmp3;

				bool foundDuplicates = false;
				for (int i = 0; i < inFileRows; i++) {
					if (tmp1 == tempmemory[i][0] and tmp2 == tempmemory[i][1] and tmp3 == tempmemory[i][2]) {
						foundDuplicates = true;
						break;
					}
				}

				if (!foundDuplicates) {
					tempmemory[inFileRows][0] = tmp1;
					tempmemory[inFileRows][1] = tmp2;
					tempmemory[inFileRows][2] = tmp3;
					inFileRows++;
				}
				tmp1 = tmp2 = tmp3 = NULL;
			}
			inFileRows++; //quick and dirty workaround, sorry
			std::cout<<"File has "<<inFileRows<<" rows"<<std::endl;
			inFile.close();
			std::cout<<"======================="<<std::endl;
			std::cout<<" tempmemory"<<std::endl;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 3; j++) {
					std::cout << tempmemory[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout<<"======================="<<std::endl;

//			int memory[inFileRows][3]; //TODO dynamic array declaration
			int ** memory = new int*[inFileRows];
			for(int i=0; i<inFileRows-1; i++){ //-1, jo infilerows iekļauj ministriju skaitu
				memory[i] = new int[3];
				for(int j=0; j<3; j++){
					memory[i][j]=tempmemory[i][j];
				}
			}
			std::cout<<"======================="<<std::endl;
			std::cout<<" memory"<<std::endl;
			for (int i = 0; i < inFileRows-1; i++) {
				for (int j = 0; j < 3; j++) {
					std::cout << memory[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout<<"======================="<<std::endl;
			std::cout<<"deleting tempmemory"<<std::endl;
			// delete tempmemory
					for(int i=0; i<MEMORYSIZE; i++)delete [] tempmemory[i] ;
					delete[]  tempmemory ;
			std::cout<<"======================="<<std::endl;
			std::cout<<"tempmemory deleted"<<std::endl;

//			Error_4_Check(tempmemory);
		}
	}else{
		std::cout << " No file";
	}
	std::cout << "Finishing" << std::endl;
	return 0;
}
