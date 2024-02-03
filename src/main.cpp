#include <iostream>
#include <string>
#include <fstream>

int main(int argc,char *argv[]){
	if(argc<2){
		std::cout<<"ERROR: not enough arguments\nreturn error code 1\n";
		return 1;
	}

	else{
		char remove=*argv[1];
		std::string text;

		if(std::string(argv[2])=="-f"){ // FIX: RETURNS FALSE EVEN IF -f IS GIVEN!!!
			std::ifstream reader;
			reader.open(argv[3]);

			if(!reader){
				std::cout<<"ERROR: couldn't open file\nreturn error code 1\n";
				return 1;
			}

			std::string line;

			while(getline(reader,line)){
				text.append(line);
				text.append("\n");
			}

			reader.close();
		}

		else{
			text=argv[2];
		}

		for(int i=text.length()-1;i>=0;i--){
			if(text.at(i)==remove){
				text.erase(i,1);
			}
		}

		std::cout<<text<<std::endl;
	}

	return 0;
}

