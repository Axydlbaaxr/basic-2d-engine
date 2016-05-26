#include "CmdLine.h"
#include <string>
#include <iostream>

// Default constructor
// Used when no arguments are passed in
CmdLine::CmdLine() :
inFile("hw1.ps"),
scalingfactor(1.0),
rotDegrees(0),
xTrans(0),
yTrans(0),
lowX(0),
lowY(0),
upperX(499),
upperY(499)
{
}

// This constructor reads in all the command line inputs
// and fills in defaults when necessary.
CmdLine::CmdLine(int argc, char **argv) :
inFile("hw1.ps"),
scalingfactor(1.0),
rotDegrees(0),
xTrans(0),
yTrans(0),
lowX(0),
lowY(0),
upperX(499),
upperY(499)
{
	for (int i=1; i < argc; i++)
	{
		std::string thisArg = argv[i];
		if(thisArg == "-f") // filename
		{
			inFile = argv[++i];
		}
		else if (thisArg == "-s") // scaling factor
		{
			scalingfactor = atof(argv[++i]);
		}
		else if (thisArg == "-r") // degrees to rotate CCW
		{
			rotDegrees = atoi(argv[++i]);
		}
		else if (thisArg == "-m") // pixels to translate in X direction
		{
			xTrans = atoi(argv[++i]);
		}
		else if (thisArg == "-n") // pixels to translate in Y direction
		{
			yTrans = atoi(argv[++i]);
		}
		else if (thisArg == "-a") // lower bound of X window (.ps coords)
		{
			lowX = atoi(argv[++i]);
		}
		else if (thisArg == "-b") // lower bound of Y window (.ps coords)
		{
			lowY = atoi(argv[++i]);
		}
		else if (thisArg == "-c") // upper bound of X window (XPM coords)
		{
			upperX = atoi(argv[++i]);
		}
		else if (thisArg == "-d") // upper bound of Y window (XPM coords)
		{
			upperY = atoi(argv[++i]);
		}
		else
		{
			// Processed an unknown input, this is a fatal error
			std::cerr << "Unknown switch " << thisArg << std::endl;
			std::cerr << "Valid switches are: " << std::endl;
			std::cerr << "-f <filename>: input postscript file" << std::endl;
			std::cerr << "-s <real number>: scaling factor about world origin" << std::endl;
			std::cerr << "-r <integer>: degrees to rotate, counterclockwise, around world origin" << std::endl;
			std::cerr << "-m/-n <integer>: translation in x/y dimension" << std::endl;
			std::cerr << "-a/-b <integer>: lower bound of x/y" << std::endl;
			std::cerr << "-c/-d <integer>: upper bound of x/y" << std::endl;
			exit(-1);
		}
	}
	// Check for illegal coords
	if (upperX < lowX)
	{
		upperX = lowX;
		std::cerr << "Warning: invalid X parms, adjusted them accordingly" << std::endl;
	}
	if (upperY < lowY)
	{
		upperY = lowY;
		std::cerr << "Warning: invalid Y parms, adjusted them accordingly" << std::endl;
	}
}

CmdLine::~CmdLine()
{
}
