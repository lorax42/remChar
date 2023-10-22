#include <iostream>
#include <string>

int main(int argc,char *argv[]){
	char remove=*argv[1];
	std::string str=argv[2];
	
	for(int i=str.length()-1;i>=0;i--){
		if(str.at(i)==remove){
			str.erase(i,1);
		}
	}
	std::cout<<str<<std::endl;

	return 0;
}

