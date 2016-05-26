#include "Color.h"
#include <string>
#include <iostream>

Color::Color(std::string name, unsigned int value) : 
c(AColor),
chars(name),
color(value)
{
}

Color::~Color()
{
}

// Dump a color information to stdout, in the format
// expected as per the XPM spec.
void Color::stdoutDump()
{
	std::cout<<"\""<<chars<<" ";

    //output the color context. There's only one possible value for this right now
	switch(c)
	{
		case AColor:	
		default:
			std::cout<<"c ";
			break;
	}
	
	//output the color RGB value
	std::cout<<"#";
	char outhex[6];
	unsigned int tempcolor = color << 8;
	tempcolor = tempcolor >> 8; // remove first eight bits
	sprintf(outhex, "%06x", color);
	std::cout<<outhex;
	std::cout<<"\"";
}	
