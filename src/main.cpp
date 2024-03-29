#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// PRINTS HELP
int help(){
	std::cout
        <<"remChar - remove a string or list characters from a string\n"
        <<"remChar string | [-s string] string | [-f file] [-o file]\n"
        <<"-f file: file containing text to be modified\n"
        <<"-o file: output file\n"
        <<"-s string: string to be completely removed\n"
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

// REMOVES EVERY INSTANCE OF A COMPLETE STRING FROM A STRING TEXT
/*
 * Error:
 *
 * $ ./remChar -s hello "hello world"
 *   terminate called after throwing an instance of 'std::out_of_range'
 *   what():  basic_string::erase: __pos (which is 144) > this->size() (which is 0)
 *   Aborted
 *
 * But this works:
 *
 * $ cat test.txt
 *   hello world
 *   world hello
 *
 * $ ./remChar -s hello -f test.txt
 *    world
 *   world
 *
 */

int remStr(std::string rem,std::string &text){
    for(int i=0;i<=text.length()-rem.length();i++){
        int equal=1;
        for(int j=0;j<rem.length();j++){
            if(rem[j]!=text[i+j]){
                equal=0;
            }
        }
        if(equal==1){
            text.erase(i,rem.length());
        }
    }
    return 0;
}

// DRIVER CODE
int main(int argc,char *argv[]){
	std::vector<std::string> args; // vector of command line arguments
	std::string text; // the text to be edited
	std::string remove=""; // the list of chars or the complete string to be removed from text
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
        // checks for string to be removed flag
        else if(args[i]=="-s"){
            // checks for string after flag
            if(i+1>=args.size()){
                std::cerr<<"ERROR: missing string after -s flag\n\n";
                help();
                return 1;
            }

            remove=args[i+1];
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

    // check if remove is set to a string (by the -s flag)
    if(remove==""){
        remove=args[1]; // set the string to be removed to args[1]

        // run remove for every char in string remove
        for(int i=0;i<remove.size();i++){
            char rem=remove[i];
            int x=remChar(rem,text);

            if(x!=0){return x;}
        }
    }
    else{
        int x=remStr(remove,text); // remove complete string from text

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

