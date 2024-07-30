#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define DEBUG 0 // set to 1 to debug
#define TRACE(func) std::cout<<"TRACE: "<<func<<"\n\n";

#define ERROR(err) std::cerr<<"ERROR: "<<__FILE__<<":"<<__LINE__<<": "<<err<<"\n\n";

// PRINTS HELP
int help(){
    if(DEBUG){TRACE("func: help")}

	std::cout
        <<"remChar - remove a string or list characters from a string\n"
        <<"remChar chars_to_be_removed | [-s string_to_be_removed] string | [-f file] [-o file]\n"
        <<"-f file: file containing text to be modified\n"
        <<"-o file: output file\n"
        <<"-s string: string to be completely removed\n"
	    <<"MIT-License lorax 2024\n";
	return 0;
}

// READS A FILE AND ASSIGNS IT'S CONTENTS TO THE VARIABLE TEXT
int read(std::string file,std::string &text){
    if(DEBUG){TRACE("func: read")}

	std::ifstream reader;
	reader.open(file);
	std::string line;

	if(!reader){
		ERROR("trouble opening file "<<file)
		return 1;
	}

    // get lines from file
	while(getline(reader,line)){
		text.append(line);
		text.append("\n");
	}

	reader.close();
	return 0;
}

// WRITES THE EDITED TEXT TO A FILE
int write(std::string file,std::string text){
    if(DEBUG){TRACE("func: write")}

	std::ofstream writer;
	writer.open(file);

	if(!writer){
		ERROR("trouble writing to file "<<file)
		return 1;
	}

	writer<<text;

	writer.close();

	return 0;
}

// REMOVES EVERY INSTANCE OF A CHARACTER FROM A STRING TEXT
int remChar(char rem,std::string &text){
    if(DEBUG){TRACE("func: remChar")}

    // loop over text and remove chars matching rem
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
 * ^^^ Problem is in arg parsing not in this function
 *
 */

int remStr(std::string rem_str,std::string &text){
    if(DEBUG){
        TRACE("func: remStr")
        TRACE("rem_str="<<rem_str)
        TRACE("text="<<text)
    }

    // loop over chars in text
    for(size_t i=0;i<text.length()-rem_str.length();i++){
        bool equal=1;

        // compare chars in rem_str to chars in text
        for(size_t j=0;j<rem_str.length();j++){
            if(DEBUG){TRACE("loop:"<<i)}

            // unset equal if chars of rem_str and text don't match
            if(rem_str[j]!=text[i+j]){
                equal=0;
                break;
            }
        }

        if(equal==1){
            text.erase(i,rem_str.length());
        }

        if(DEBUG){TRACE("final text="<<text)}
    }
    return 0;
    //return text;
}

// DRIVER CODE
int main(int argc,char *argv[]){
	std::vector<std::string> args; // vector of command line arguments
                                   //
	std::string text=""; // the text to be edited

	std::string rem_chars=""; // the list of chars to be removed from text
	std::string rem_str=""; // the complete string to be removed from text
                            //
	std::string fileIn=""; // name of input file
    std::string fileOut=""; // name of output file

	// read command line arguments
	for(int i=0;i<argc;i++){
		args.push_back(argv[i]);
	}

	// check for minimum argument number
	if(args.size()<3){
		ERROR("not enough arguments")
		help();
		return 1;
	}

	// checks for flags in args and applies them
	for(size_t i=1;i<args.size();i++){
		// checks for input file flag
		if(args[i]=="-f"){
			// checks for file name after flag
			if(i+1>=args.size()){
				ERROR("missing file name after -f flag")
				help();
				return 1;
			}

			fileIn=std::string(args[i+1]);
            if(DEBUG){TRACE("fileIn="<<fileIn)}
            i++;
		}
		// checks for output file flag
		else if(args[i]=="-o"){
			// checks for file name after flag
			if(i+1>=args.size()){
				ERROR("missing file name after -f flag")
				help();
				return 1;
			}

			fileOut=std::string(args[i+1]);
            if(DEBUG){TRACE("fileOut="<<fileOut)}
            i++;
		}
        // checks for string to be removed flag
        else if(args[i]=="-s"){
            // checks for string after flag
            if(i+1>=args.size()){
                ERROR("missing string after -s flag")
                help();
                return 1;
            }

            rem_str=std::string(args[i+1]);
            if(DEBUG){TRACE("rem_str="<<rem_str)}
            i++;
        }
        // assign other args to rem_str or text
        else{
            // if rem_str is given but text is not, populate text
            if(rem_str!="" && text==""){
                text=std::string(args[i]);
                if(DEBUG){TRACE("text="<<text)}
            }
            // else if rem_chars isn't given, populate
            else if(rem_chars==""){
                rem_chars=std::string(args[i]);
                if(DEBUG){TRACE("rem_chars="<<rem_str)}
            }
            // else if text isn't given, populate
            else if(text==""){
                text=std::string(args[i]);
                if(DEBUG){TRACE("text="<<text)}
            }
            // else there must be too many args
            else{
                ERROR("superfluous arguments")
                help();
            }
        }
	}

	// if fileIn was specified read from it
	if(fileIn!=""){
        if(DEBUG){TRACE("if: fileIn")}

        if(text!=""){
            std::cerr<<"WARNING: both fileIn and text defined\n\n";
        }

		int x=read(fileIn,text);
		
		if(x!=0){return x;}
	}

    // check if rem_str is set (by the -s flag)
    if(rem_str!=""){
        if(DEBUG){TRACE("if: rem_str")}

        if(rem_chars!=""){
            std::cerr<<"WARNING: both rem_str and rem_chars defined\n\n";
        }

        int x=remStr(rem_str,text); // rem_chars complete string from text

        if(x!=0){return x;}
    }
    else{
        // run remove for every char in string rem_chars on text
        for(size_t i=0;i<rem_chars.size();i++){
            char rem=rem_chars[i];
            int x=remChar(rem,text);

            if(x!=0){return x;}
        }
    }
	
	// if file was specified write to it else just print text to terminal
	if(fileOut!=""){
        if(DEBUG){TRACE("if: fileOut")}

		int x=write(fileOut,text);

		if(x!=0){return x;}
	}
	else{
		std::cout<<text<<"\n";
	}

	return 0;
}

