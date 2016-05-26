#include "PSFile.h"
#include "Command.h"
#include "Line.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

PSFile::PSFile(std::string theFile) :
filename(theFile)
{
}

PSFile::~PSFile()
{
}

void PSFile::parseFile()
{
    const int notFound = -1;
	std::ifstream infile(filename.c_str());
	std::string tempString = "";
	char tempchars[1024];
	bool beginfound = false;
	bool endfound = false;

    if(!infile.good())
    {
    	std::cerr<<"ERROR: problem reading input file"<<std::endl;
    	exit(-1);
    }

	// look for BEGIN delimeter
	while(!beginfound && !infile.eof())
    {
    	infile.getline(tempchars, 1024);
    	tempString = tempchars;
    	if(tempString.compare(0,8,"%%%BEGIN") == 0)
    	{
    		beginfound = true;
    	}
    }
    if (!beginfound)
    {
    	std::cerr<<"ERROR: %%%BEGIN delimeter not found"<<std::endl; 
    	exit(-1);
    }
    
    // go ahead and read the file until END
    while(!endfound && !infile.eof())
    {
        std::vector<std::string> tokenizedstring;
    	infile.getline(tempchars, 1024);
    	if(!infile.good())
    	{
    		std::cerr<<"ERROR: problem reading input file"<<std::endl;
    	}
    	tempString = tempchars;
    	if(tempString.compare(0,6,"%%%END") == 0)
    	{
    		endfound = true;
    	}
    	else
    	{
    	   Tokenize(tempString, tokenizedstring, " ");
    	   parseline(tokenizedstring);
    	}
    }
    // Assume that if %%%END isn't there, there's
    // some kind of mistake and exit.
    if (!endfound)
    {
    	std::cerr<<"ERROR: %%%END delimeter not found"<<std::endl;
    	exit(-1);
    }
}

// Takes string str and creates series of delimited tokens
void PSFile::Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (pos != -1 || lastPos != -1)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters. 
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

// This function will parse the commands
// That lie between %%%BEGIN and %%%END.
// Also generates the internal command list
void PSFile::parseline(std::vector<std::string>& tokens)
{

	// Check for endlines, they should be ignored
	// MAKE SURE you check for both UNIX-style and Win-style endlines
	if(tokens.size() == 0) return;	
	if((tokens.size() == 1) && ((tokens[0].at(0) == '\n') || (tokens[0].at(0) == '\r')))
	  return;

    // Process Line command
	if((tokens.size() == 5) && (!tokens[4].compare(0, 4, "Line")))
	{
	   int arg1 = atoi(tokens[0].c_str());
	   int arg2 = atoi(tokens[1].c_str());
	   int arg3 = atoi(tokens[2].c_str());
	   int arg4 = atoi(tokens[3].c_str());	
       commandList.push_back(new Line(arg1, arg2, arg3, arg4));
	}
	else // syntax error, nonsense line
	{
		std::cerr << "Warning: syntax error detected! Line ignored." << std::endl;
	}
}

// The main operating loop, executes all commands that have
// been associated with a .ps file
void PSFile::executeCommands(XPMData* outfile)
{
	std::vector<Command*>::iterator itr;
	for ( itr = commandList.begin(); itr != commandList.end(); ++itr )
    {
    	(*itr)->execute(outfile);
    }
}