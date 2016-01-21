#include <iostream>
#include <fstream>
#define INPUTFILENAME "budget.in"
#define OUTPUTFILENAME "budget.out"

bool file_exists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}


int main() {
	std::cout << "Starting" << std::endl;
	if (file_exists(INPUTFILENAME)) {
		std::ifstream ievadesFails(INPUTFILENAME);
		if (ievadesFails.is_open()) {

			int countFromFile;
			int dump;
			ievadesFails >> countFromFile;
			int ministrijas[countFromFile - 1][2]; //array indexing starts from zero
			for (int i = 0; i < countFromFile * 2; i++) {
				if (i % 2 == 1) {
					ievadesFails >> ministrijas[i/2][1];
					std::cout << ministrijas[i/2] [1]<< std::endl;
				} else {
					ievadesFails >> ministrijas[i/2][0];
					std::cout << ministrijas[i/2] [0]<<" ";

				}
			}
			int izdevumi[1000][2]={0}; //FIXME maximum is 10 000

			int i=0;  //izdevumi count
			int temp1 = NULL;
			int temp2 = NULL;
			int temp3 = NULL;
			while (true){
				ievadesFails >> temp1;
				if(!temp1) break;
				ievadesFails >> temp2;
				ievadesFails >> temp3;
//				std::cout << "expected: "<<temp1 <<" "<<temp2<<" "<<temp3<<std::endl;
				izdevumi[i][0] = temp1;
				izdevumi[i][1] = temp2;
				izdevumi[i][2] = temp3;
				std::cout <<izdevumi[i][0]  <<" "<<izdevumi[i][1]<<" "<<izdevumi[i][2]<<std::endl;
				i++;
				temp1 = NULL;
				temp2 = NULL;
				temp3 = NULL;
			}
			ievadesFails.close();
			//TODO implement solution
			//Check sums:
			for(int j=0; j<i; j++){
				if(izdevumi[j][0]==ministrijas[j][0])ministrijas[0][1]+=izdevumi[j][2];
			}
		}
	} else {
		std::cout << " No file";
	}
	std::cout << "Finishing" << std::endl;
	return 0;

}
