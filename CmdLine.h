#ifndef CMDLINE_H_
#define CMDLINE_H_

// Class that represents, stores, parses command line inputs

#include <string>

class CmdLine
{
public:
	CmdLine();
	CmdLine(int argc, char **argv);
	virtual ~CmdLine();
	
	std::string getinFile();
	double getscalingfactor();
	int getrotDegrees();
	int getxTrans();
	int getyTrans();
	int getlowX();
	int getlowY();
	int getupperX();
	int getupperY();
	
private:
	std::string inFile;
	double scalingfactor;
	int rotDegrees;
	int xTrans;
	int yTrans;
	int lowX;
	int lowY;
	int upperX;
	int upperY;
};

inline std::string CmdLine::getinFile() { return inFile;}
inline double CmdLine::getscalingfactor() { return scalingfactor;}
inline int CmdLine::getrotDegrees() {return rotDegrees;}
inline int CmdLine::getxTrans() {return xTrans;}
inline int CmdLine::getyTrans() {return yTrans;}
inline int CmdLine::getlowX() {return lowX;}
inline int CmdLine::getlowY() {return lowY;}
inline int CmdLine::getupperX() {return upperX;}
inline int CmdLine::getupperY() {return upperY;}


#endif /*CMDLINE_H_*/
