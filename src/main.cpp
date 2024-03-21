#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// PRINTS HELP
int help(){
	std::cout
        <<"remChar <character> <string|-f <file> [<-o file>]\n"
        <<"-f\tinput file\n"
        <<"-o\toutput file\n"
		<<"MIT-License Lloyd Bush 2024\n";
	return 0;
}

// READS A FILE AND ASSIGNS IT'S CONTENTS TO THE VARIABLE TEXT
int read(std::string file,std::string &text){
	std::ifstream reader;
	reader.open(file);
	std::string line;

	if(!reader){
		std::cerr<<"ERROR: trouble opening file "<<file<<"\n";
		return 1;
	}

	while(getline(reader,line)){
		text.append(line);
		text.append("\n");
	}

	reader.close();
	return 0;
}

// WRITES THE EDITED TEXT TO A FILE
int write(std::string file,std::string text){
	std::ofstream writer;
	writer.open(file);

	if(!writer){
		std::cerr<<"ERROR: trouble writing to file "<<file<<"\n";
		return 1;
	}

	writer<<text;

	writer.close();

	return 0;
}

// REMOVES EVERY INSTANCE OF A CHARACTER FROM A STRING TEXT
int remChar(char rem,std::string &text){
	for(int i=text.length()-1;i>=0;i--){
		if(text[i]==rem){
			text.erase(i,1);
		}
	}

	return 0;
}

// DRIVER CODE
int main(int argc,char *argv[]){
	std::vector<std::string> args; // vector of command line arguments
	std::string text; // the text to be edited
	std::string remove; // the list of chars to be removed from text
	std::string fileIn="",fileOut=""; // names of input and output files

	// read command line arguments
	for(int i=0;i<argc;i++){
		args.push_back(argv[i]);
	}

	// check for minimum argument number
	if(args.size()<3){
		std::cerr<<"ERROR: not enough arguments\n\n";
		help();
		return 1;
	}

	// checks for flags in args and applies them
	for(int i=0;i<args.size();i++){
		// checks for input file flag
		if(args[i]=="-f"){
			// checks for file name after flag
			if(i+1>=args.size()){
				std::cerr<<"ERROR: missing file name after -f flag\n\n";
				help();
				return 1;
			}

			fileIn=args[i+1];
		}
		// checks for output file flag
		else if(args[i]=="-o"){
			// checks for file name after flag
			if(i+1>=args.size()){
				std::cerr<<"ERROR: missing file name after -f flag\n\n";
				help();
				return 1;
			}

			fileOut=args[i+1];
		}
	}

	// if file was specified read from it else read from args[2]
	if(fileIn!=""){
		int x=read(fileIn,text);
		
		if(x!=0){return x;}
	}
	else{
		text=args[2];
	}

	remove=args[1]; // set the string to be removed to args[1]

	// run remove for every char in string remove
	for(int i=0;i<remove.size();i++){
		char rem=remove[i];
		int x=remChar(rem,text);

		if(x!=0){return x;}
	}
	
	// if file was specified write to it else just print text to terminal
	if(fileOut!=""){
		int x=write(fileOut,text);

		if(x!=0){return x;}
	}
	else{
		std::cout<<text<<"\n";
	}

	return 0;
}

