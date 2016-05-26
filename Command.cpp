#include "Command.h"

Command::~Command()
{
}

// A basic 3x3 Matrix Multiply
void Command::MatrixMultiply(double out[3][3], double a[3][3], double b[3][3])
{
	int i, j, k;
	double sum;
	for (i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			sum = 0;
			for (k=0; k<3; k++)
			{
				sum += a[i][k]*b[k][j];
			}
      	  out[i][j] = sum;
		}
	}
}

// A basic (3x3)x(3x1) matrix-vector multiply
void Command::MatrixVector(double out[3], double a[3][3], double x[3])
{
	out[0] = (a[0][0]*x[0])+(a[0][1]*x[1])+(a[0][2]*x[2]);
	out[1] = (a[1][0]*x[0])+(a[1][1]*x[1])+(a[1][2]*x[2]);
	out[2] = (a[2][0]*x[0])+(a[2][1]*x[1])+(a[2][2]*x[2]);
}
