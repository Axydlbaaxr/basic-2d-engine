#ifndef COMMAND_H_
#define COMMAND_H_

//Command class
//This is derived from the standard Command design pattern,
//the difference being that execute needs an XPMData object
//to operate on. This is common across all commands.

class XPMData;

class Command
{
public:
	virtual ~Command();
	virtual void execute(XPMData*) = 0;
protected:
	void MatrixMultiply(double[3][3], double[3][3], double[3][3]);
	void MatrixVector(double[3], double[3][3], double[3]);
};

#endif /*COMMAND_H_*/
