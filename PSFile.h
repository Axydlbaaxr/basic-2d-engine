#ifndef PSFILE_H_
#define PSFILE_H_

// Class represents a .ps file and the commands contained therein

#include <string>
#include "Command.h"
#include "XPMData.h"
#include <vector>

class PSFile
{
public:
	PSFile(std::string);
	virtual ~PSFile();
	void parseFile();
	void executeCommands(XPMData*);
private:
	std::string filename;
	std::vector<Command*> commandList;
	void Tokenize(const std::string&, std::vector<std::string>&, const std::string&);
	void parseline(std::vector<std::string>&);
};

#endif /*PSFILE_H_*/
