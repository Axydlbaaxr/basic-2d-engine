#include "XPMData.h"
#include "Color.h"
#include "CmdLine.h"
#include <iostream>

XPMData::XPMData(int w, int h, CmdLine* cmd) :
num_colors(2),
width(w),
chars_per_pixel(1),
height(h),
theCmdLine(cmd)
{
	// There are only two colors we're supporting for now,
	// black and white
	unsigned int white = 0x00FFFFFF;
	unsigned int black = 0x00000000;
	Color *blackColor = new Color("k", black);
	ColorList.push_back(new Color("-", white));
	ColorList.push_back(blackColor);
	currentColor = blackColor;		
}

XPMData::~XPMData()
{
	delete [] Pixels;
}

// Clear the pixelmap, setting all pixels to white '-'
void XPMData::Initialize()
{
	unsigned const int totalWidth = width * chars_per_pixel;
    Pixels = new char*[height];
	for (int j=0; j<height; j++)
	{
		Pixels[j] = new char[totalWidth];
	}		
	for (int i=0; i<height; i++)
	{
		for (unsigned int j=0; j<(totalWidth); j++)
		{
			Pixels[i][j] = '-';
		}
	}
}

// Plots a black point at x,y.
// Something will need to change once we start dealing with other colors.
void XPMData::plot(int x, int y)
{
	std::string colorChoice = currentColor->getchars();

	// We need to convert PS coordinates (origin lower-left)
	// to bitmap coordinates (origin upper-left)	
	y = theCmdLine->getupperY() - y + theCmdLine->getlowY();
	
	//convert pixel coordinates to array indexes within a file
	//for those cases where xmin, ymin != 0
	x = x - theCmdLine->getlowX();
	y = y - theCmdLine->getlowY();
			
	// "plot" the pixel within the XPM file
	for (int i=1; i<=chars_per_pixel; i++)
	{
		Pixels[(y*chars_per_pixel)+(i-1)][x] = colorChoice[i-1];
	}
}

// Dumps out the XPM file, which is the whole purpose of the program... 
void XPMData::stdoutDump()
{
	//write XPM header
	std::cout<<"/* XPM */"<<std::endl;
	std::cout<<"static char *bwimage[] = {"<<std::endl;
	std::cout<<"/* width height num_colors chars_per_pixel */"<<std::endl;
	std::cout<<"\""<<width<<" "<<height<<" "<<num_colors<<" "<<chars_per_pixel<<"\","<<std::endl;

    //write color list
	std::cout<<"/* colors */"<<std::endl;
	std::vector<Color*>::iterator itr;
	for ( itr = ColorList.begin(); itr != ColorList.end(); ++itr )
    {
    	(*itr)->stdoutDump();
    	std::cout<<","<<std::endl;    	
    }
    
    //write pixel list
    std::cout<<"/* pixels */"<<std::endl;
	for (int i=0; i<height; i++)
	{
		std::cout<<"\"";
		for (int j=0; j<width*chars_per_pixel; j++)
		{
    	   std::cout<<Pixels[i][j];
		}
		std::cout<<"\"";
		if (i != (height-1))
		{
			std::cout<<","<<std::endl;
		}
		else std::cout<<std::endl;
	}
	
	//finish it off
	std::cout<<"};"<<std::endl;
}