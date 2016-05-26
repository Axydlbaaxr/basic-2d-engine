#include "Line.h"
#include "XPMData.h"
#include "Command.h"
#include <iostream>
#include <cmath>

bool Line::TransformationMatrixComputed = false;
double Line::TransformationMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

// A line command has four parameters, consisting of two (x,y) endpoints.
Line::Line(int a, int b, int c, int d) :
x1(a),
y1(b),
x2(c),
y2(d)
{
}

Line::~Line()
{
}

//Draw the line to the XPM file.
//This applies the 2D transformations specified in the command-line inputs
//and applies Cohen-Sutherland to clip the lines to the world window.
//This includes an implementation of Bresenham's line-drawing algorithm.
void Line::execute(XPMData *thefile)
{
		
	//Create the composite transformation matrix
	//from the command-line inputs.
	CreateTransformationMatrix(thefile);
	
	// With the matrix, we can transform both endpoints of the line
	double VectorToTransform[3];
	double TransformedVector1[3];
	double TransformedVector2[3];
	VectorToTransform[0] = x1;
	VectorToTransform[1] = y1;
	VectorToTransform[2] = 1;
	MatrixVector(TransformedVector1, TransformationMatrix, VectorToTransform);
	x1 = TransformedVector1[0];
	y1 = TransformedVector1[1];
	VectorToTransform[0] = x2;
	VectorToTransform[1] = y2;
	VectorToTransform[2] = 1;
	MatrixVector(TransformedVector2, TransformationMatrix, VectorToTransform);
	x2 = TransformedVector2[0];
	y2 = TransformedVector2[1];

    // Clip to world window, do not draw anything if length = 0
    if (!Clip(thefile->getCmdLine()->getlowX(), thefile->getCmdLine()->getupperX(), 
          thefile->getCmdLine()->getlowY(), thefile->getCmdLine()->getupperY())) 
       return;

    // Now everything is clipped and transformed. Let's draw the line.
    // First, we need to handle vertical lines (they have an undefined slope)
    if ((x2-x1) == 0)
    {
    	if (y2 > y1)
    	{
    		for(int y = y1; y <= y2; y++)
    		{
    			thefile->plot(x1, y);
    		}
    	}
    	else 
    	{
    		for(int y = y2; y <= y1; y++)
    		{
    			thefile->plot(x1, y);
    		}
    	}
    return;
    }
    
    // Bresnehan's algorithm should handle everything else.
    double slope = fabs(y2 - y1) / fabs(x2-x1);
    if (slope > 1)
    {
    	//for steep lines, we can reflect to get a lesser slope
    	int temp = x1;
    	x1 = y1;
    	y1 = temp;
    	temp = x2;
    	x2 = y2;
    	y2 = temp;
    }
    if (x1 > x2)
    {
    	// we can swap the points and still get the same line
    	// this is done to help generalize the algorithm
    	int temp = x1;
    	x1 = x2;
    	x2 = temp;
    	temp = y1;
    	y1 = y2;
    	y2 = temp;
    }
    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int D = dx/2;
    int y = y1;
    for (int x = x1; x <= x2; x++)
    {
    	if (slope > 1)
    	{
    		thefile->plot(y, x);
    	}
    	else thefile->plot(x, y);
    	D = D - dy;
    	if (D < 0)
    	{
    		if (y1 < y2) y++;
    		else y--;
    		D += dx;
    	}
    }
    
}

// Clips the internal line to window.
// Implements Cohen-Sutherland algorithm.
// Returns false if line is totally outside view window, true otherwise
bool Line::Clip(int xmin, int xmax, int ymin, int ymax)
{
    // Generate Cohen-Sutherland bitcode for both points.
	unsigned char code1 = 0, code2 = 0;
	const unsigned char tooHigh = 0x8;
	const unsigned char tooLow = 0x4;
	const unsigned char tooLeft = 0x1;
	const unsigned char tooRight = 0x2;
	if (x1 < xmin) code1 = code1 | tooLeft;
	if (x1 > xmax) code1 = code1 | tooRight;
	if (y1 < ymin) code1 = code1 | tooLow;
	if (y1 > ymax) code1 = code1 | tooHigh;
	if (x2 < xmin) code2 = code2 | tooLeft;
	if (x2 > xmax) code2 = code2 | tooRight;
	if (y2 < ymin) code2 = code2 | tooLow;
	if (y2 > ymax) code2 = code2 | tooHigh;
	
    // Reject trivial cases (both are too high/low/left/right)
	if (code1 & code2)
	{
		return false;
	}
	
	// Otherwise, check the opcodes for point 1
	if (code1 & tooHigh)
	{
		x1 = x1 + ((x2 - x1) * (ymax - y1) / (y2 - y1));
		y1 = ymax;
	}
	else if (code1 & tooLow)
	{
		x1 = x1 + ((x2 - x1) * (ymin - y1) / (y2 - y1));
		y1 = ymin;
	}
	else if (code1 & tooLeft)
	{
		y1 = y1 + ((y2 - y1) * (xmin - x1) / (x2 - x1));
		x1 = xmin;
	}
	else if (code1 & tooRight)
	{
		y1 = y1 + ((y2 - y1) * (xmax - x1) / (x2 - x1));
		x1 = xmax;
	}
		
	//Now check the codes for point 2
	if ((code2 & tooHigh) && (y2 != y1))
	{
		x2 = x1 + ((x2 - x1) * (ymax - y1) / (y2 - y1));
		y2 = ymax;
	}
	else if ((code2 & tooLow) && (y2 != y1))
	{
		x2 = x1 + ((x2 - x1) * (ymin - y1) / (y2 - y1));
		y2 = ymin;
	}
	else if ((code2 & tooLeft) && (x2 != x1))
	{
		y2 = y1 + ((y2 - y1) * (xmin - x1) / (x2 - x1));
		x2 = xmin;
	}
	else if ((code2 & tooRight) && (x2 != x1))
	{
		y2 = y1 + ((y2 - y1) * (xmax - x1) / (x2 - x1));
		x2 = xmax;
	}
	
	// Now make a second pass, which may be necessary
	// if a point had two conditions (Left/High, Right/Low, etc.)
	code1 = code2 = 0;
	if (x1 < xmin) code1 = code1 | tooLeft;
	if (x1 > xmax) code1 = code1 | tooRight;
	if (y1 < ymin) code1 = code1 | tooLow;
	if (y1 > ymax) code1 = code1 | tooHigh;
	if (x2 < xmin) code2 = code2 | tooLeft;
	if (x2 > xmax) code2 = code2 | tooRight;
	if (y2 < ymin) code2 = code2 | tooLow;
	if (y2 > ymax) code2 = code2 | tooHigh;
	
	// Reject trivial cases (both are too high/low/left/right)
	if (code1 & code2)
	{
		return false;
	}
	
	// check the opcodes for point 1
	if (code1 & tooHigh)
	{
		x1 = x1 + ((x2 - x1) * (ymax - y1) / (y2 - y1));
		y1 = ymax;
	}
	else if (code1 & tooLow)
	{
		x1 = x1 + ((x2 - x1) * (ymin - y1) / (y2 - y1));
		y1 = ymin;
	}
	else if (code1 & tooLeft)
	{
		y1 = y1 + ((y2 - y1) * (xmin - x1) / (x2 - x1));
		x1 = xmin;
	}
	else if (code1 & tooRight)
	{
		y1 = y1 + ((y2 - y1) * (xmax - x1) / (x2 - x1));
		x1 = xmax;
	}
		
	//Now check the codes for point 2
	if ((code2 & tooHigh) && (y2 != y1))
	{
		x2 = x1 + ((x2 - x1) * (ymax - y1) / (y2 - y1));
		y2 = ymax;
	}
	else if ((code2 & tooLow) && (y2 != y1))
	{
		x2 = x1 + ((x2 - x1) * (ymin - y1) / (y2 - y1));
		y2 = ymin;
	}
	else if ((code2 & tooLeft) && (x2 != x1))
	{
		y2 = y1 + ((y2 - y1) * (xmin - x1) / (x2 - x1));
		x2 = xmin;
	}
	else if ((code2 & tooRight) && (x2 != x1))
	{
		y2 = y1 + ((y2 - y1) * (xmax - x1) / (x2 - x1));
		x2 = xmax;
	}
	// Check to see if our line is clipped.
	// Some lines may still be outside the world window.
	code1 = code2 = 0;
	if (x1 < xmin) code1 = code1 | tooLeft;
	if (x1 > xmax) code1 = code1 | tooRight;
	if (y1 < ymin) code1 = code1 | tooLow;
	if (y1 > ymax) code1 = code1 | tooHigh;
	if (x2 < xmin) code2 = code2 | tooLeft;
	if (x2 > xmax) code2 = code2 | tooRight;
	if (y2 < ymin) code2 = code2 | tooLow;
	if (y2 > ymax) code2 = code2 | tooHigh;
	if ((code1 == 0) && (code2 == 0)) return true;
	else return false;
}


// Creates a composite transformation matrix
// Uses command-line inputs to set rotation, scaling, and translation
// parms
void Line::CreateTransformationMatrix(XPMData *thefile)
{
	// We only need to compute the matrix once.
	if(TransformationMatrixComputed) return;
	
	// create rotation matrix R
	double RotateTransform[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	const double pi = 3.141592653589;
	double rotRadians = (thefile->getCmdLine()->getrotDegrees())*pi/180;
	RotateTransform[0][0] = cos(rotRadians);
	RotateTransform[0][1] = -sin(rotRadians);
	RotateTransform[1][0] = sin(rotRadians);
	RotateTransform[1][1] = cos(rotRadians);
	
	// create scaling matrix S
	double ScaleTransform[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	ScaleTransform[0][0] = thefile->getCmdLine()->getscalingfactor();
	ScaleTransform[1][1] = thefile->getCmdLine()->getscalingfactor();
	
	// create translation matrix T
	double TransTransform[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	TransTransform[0][2] = thefile->getCmdLine()->getxTrans();
	TransTransform[1][2] = thefile->getCmdLine()->getyTrans();
	
	// R*S
	double TempTransform[3][3];
	MatrixMultiply(TempTransform, RotateTransform, ScaleTransform);
	
	// T*(R*S) and exit
	MatrixMultiply(TransformationMatrix, TransTransform, TempTransform);
}