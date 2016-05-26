#ifndef LINE_H_
#define LINE_H_

// Class implements the Line command.
// Draws a line from (x1, y1) to (y1, y2)
// Postscript format: x1 y1 x2 y2 Line

#include "Command.h"

class XPMData;

class Line : public Command
{
public:
	Line(int, int, int, int);
	void execute(XPMData*); 
	virtual ~Line();
private:
	int x1;
	int x2;
	int y1;
	int y2;
	static bool TransformationMatrixComputed;
	static double TransformationMatrix[3][3];
	bool Clip(int, int, int, int);
	void CreateTransformationMatrix(XPMData*);
};

#endif /*LINE_H_*/
