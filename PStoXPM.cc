#include "CmdLine.h"
#include "XPMData.h"
#include "PSFile.h"

int main(int argc, char **argv)
{
    //Parse the command line arguments.
    //If there are no command line arguments, no parsing is necessary...
    //so use the defaults.
	CmdLine *theCmdLine;
	if (argc == 1)
	{
		theCmdLine = new CmdLine;
	}
	else
	{
		theCmdLine = new CmdLine(argc, argv);	
	}	

    //Create the XPM file that will be output
    int XPMwidth = theCmdLine->getupperX()-theCmdLine->getlowX()+1;
    int XPMheight = theCmdLine->getupperY()-theCmdLine->getlowY()+1;
	XPMData *outXPM = new XPMData(XPMwidth, XPMheight, theCmdLine);
	outXPM->Initialize();

    //Read the input PostScript file
	PSFile *inputFile = new PSFile(theCmdLine->getinFile());
	inputFile->parseFile();
	
	//Operate on the XPM file using the commands given in the PostScript file
	inputFile->executeCommands(outXPM);
	
	//Spit out the XPM file
	outXPM->stdoutDump();
	
}