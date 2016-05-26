#ifndef COLOR_H_
#define COLOR_H_

// This class holds information for a color to be represented
// within the XPM file.

#include <string>

// Context isn't really used right now, since I'm only supporting
// color. It's here for completeness.
enum Context
{
	Monovisual,
	Symbolic,
	Grayscale4,
	Grayscale,
	AColor
}; 

class Color
{
public:
	Color(std::string, unsigned int);
	virtual ~Color();
	std::string getchars();
	unsigned int getcolor();
	void stdoutDump();
private:
	std::string chars;
	Context c;
	unsigned int color;
};

inline std::string Color::getchars()
{
	return chars;
}

inline unsigned int Color::getcolor()
{
	return color;
}
#endif /*COLOR_H_*/
