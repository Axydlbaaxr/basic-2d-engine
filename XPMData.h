#ifndef XPMDATA_H_
#define XPMDATA_H_

// This class stores the data that will be in a .xpm file

#include <vector>
#include "CmdLine.h"

class Color;

class XPMData
{
public:
	XPMData(int, int, CmdLine*);
	virtual ~XPMData();
	void Initialize();
	CmdLine *getCmdLine();
	void plot(int, int);
	void stdoutDump();
	
private:
	int width;
	int height;
	CmdLine *theCmdLine;
	int num_colors;
	int chars_per_pixel;
	std::vector<Color *> ColorList;
	Color *currentColor;
	char **Pixels;
};

inline CmdLine* XPMData::getCmdLine()
{
	return theCmdLine;
}

#endif /*XPMDATA_H_*/
