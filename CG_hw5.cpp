/* Author: Saumya Saxena
CS536: Computer Graphics - Assignment 5
Date: December 7, 2018
Description: Hierarchical Models
*/

/* Header Files */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

#define M_PI 3.1415926535

/* Function to return radian values */
double get_radians(double degrees)
{
	double radians = ( degrees * M_PI ) / 180.0;
	return radians;
}

/* Function to multiply two matrices */
vector<vector<double> > multiplyMatrix(vector<vector<double> > matrix1, vector<vector<double> > matrix2) 
{
	int rowsInA = matrix1.size();

	int columnsInA = matrix1[0].size();
	int columnsInB = matrix2[0].size();
    
	vector<vector<double> > matrixMultiply;

	matrixMultiply.resize(rowsInA,vector<double>(columnsInB));

	for (int i = 0; i < rowsInA; i++) {
		for (int j = 0; j < columnsInB; j++) {
			for (int k = 0; k < columnsInA; k++) {
				matrixMultiply[i][j] = matrixMultiply[i][j] + matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return matrixMultiply;
}

/* Function to rotate a matrix where flag tells the direction of rotation(clock-wise or anti-clockwise) */
vector<vector<double> > rotationMatrix(double theta, vector<vector<double> > matrix, int flag)
{
	vector<vector<double> > yRotation,zRotation;
	yRotation.resize(4,vector<double>(4));
	zRotation.resize(4,vector<double>(4));

	yRotation[0][0] = cos(get_radians(theta));    yRotation[0][1] = 0.0; 
	yRotation[0][2] = sin(get_radians(theta));    yRotation[0][3] = 0.0;

	yRotation[1][0] = 0.0; yRotation[1][1] = 1.0; yRotation[1][2] = 0.0; yRotation[1][3] = 0.0;

	yRotation[2][0] = -sin(get_radians(theta));   yRotation[2][1] = 0.0; 
	yRotation[2][2] = cos(get_radians(theta));    yRotation[2][3] = 0.0;

	yRotation[3][0] = 0.0; yRotation[3][1] = 0.0; yRotation[3][2] = 0.0; yRotation[3][3] = 1.0;


	zRotation[0][0] = cos(get_radians(theta));    zRotation[0][1] =  -sin(get_radians(theta)); 
	zRotation[0][2] = 0.0;						  zRotation[0][3] = 0.0;

	zRotation[1][0] = sin(get_radians(theta));    zRotation[1][1] = cos(get_radians(theta));  
	zRotation[1][2] = 0.0;						  zRotation[1][3] = 0.0;

	zRotation[2][0] = 0.0; zRotation[2][1] = 0.0; zRotation[2][2] = 1.0; zRotation[2][3] = 0.0;
	zRotation[3][0] = 0.0; zRotation[3][1] = 0.0; zRotation[3][2] = 0.0; zRotation[3][3] = 1.0;


	vector<vector<double> > vertexMatrix;
	vertexMatrix.resize(4,vector<double>(1));

	vertexMatrix[3][0] = 1.0;

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<3;j++)
		{
			vertexMatrix[j][0] = matrix[i][j];
		}
		if(flag==0)
		{
			vertexMatrix = multiplyMatrix(yRotation , vertexMatrix);
		}
		else if(flag==1)
		{
			vertexMatrix = multiplyMatrix(zRotation , vertexMatrix);
		}
		for(int j=0;j<3;j++)
		{
			matrix[i][j] = vertexMatrix[j][0];
		}
	}					
	return matrix;
}

/* Function to generate a matrix */
vector<vector<double> > generateMatrix(vector<vector<double> > matrix,double x1,double y1,double z1,double x2,double y2,double z2)
{
	matrix[0][0] = x1;	 matrix[0][1] = y1;    matrix[0][2] = z1;
	matrix[1][0] = -x1;	 matrix[1][1] = y1;    matrix[1][2] = z1;
	matrix[2][0] = -x1;	 matrix[2][1] = -y1;   matrix[2][2] = z1;
	matrix[3][0] = x1;	 matrix[3][1] = -y1;   matrix[3][2] = z1;
	matrix[4][0] = -x2;	 matrix[4][1] = -y2;   matrix[4][2] = z2;
	matrix[5][0] = x2;	 matrix[5][1] = -y2;   matrix[5][2] = z2;
	matrix[6][0] = x2;	 matrix[6][1] = y2;    matrix[6][2] = z2;
	matrix[7][0] = -x2;	 matrix[7][1] = y2;    matrix[7][2] = z2;
	
	return matrix;
}

/* Function to calculate the centre */
vector<double> center(vector<vector<double> > matrix){

	double x1 = matrix[1][0];
	double y1 = matrix[1][1];
	double z1 = matrix[1][2];
	double x2 = matrix[3][0];
	double y2 = matrix[3][1];
	double z2 = matrix[3][2];

	double midX = (x1+x2) / 2.0;
	double midY = (y1+y2) / 2.0;
	double midZ = (z1+z2) / 2.0;

	vector<double> midPoint;

	midPoint.resize(3);

	midPoint[0] = midX;
	midPoint[1] = midY;
	midPoint[2] = midZ;

	return midPoint;
}

/* Function to translate a matrix */
vector<vector<double> > translateMatrix(double x,double y,double z, vector<vector<double> > matrix)
{
	vector<vector<double> > translatedMatrix;
	translatedMatrix.resize(4,vector<double>(4));
	
	translatedMatrix[0][0] = 1.0; translatedMatrix[0][1] = 0.0; translatedMatrix[0][2] = 0.0; translatedMatrix[0][3] = x;
	translatedMatrix[1][0] = 0.0; translatedMatrix[1][1] = 1.0; translatedMatrix[1][2] = 0.0; translatedMatrix[1][3] = y;
	translatedMatrix[2][0] = 0.0; translatedMatrix[2][1] = 0.0; translatedMatrix[2][2] = 1.0; translatedMatrix[2][3] = z;
	translatedMatrix[3][0] = 0.0; translatedMatrix[3][1] = 0.0; translatedMatrix[3][2] = 0.0; translatedMatrix[3][3] = 1.0;

	vector<vector<double> > vertexMatrix ;
	vertexMatrix.resize(4,vector<double>(1));
	vertexMatrix[3][0]=1.0;

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<3;j++)
		{
			vertexMatrix[j][0] = matrix[i][j];
		}
		vertexMatrix = multiplyMatrix(translatedMatrix , vertexMatrix);

		for(int j = 0;j < 3; j++)
		{
			matrix[i][j] = vertexMatrix[j][0];
		}
	}
	return matrix;
}

int main(int argc, char** argv)
{
	double angle1 = -51, angle2 = 39, angle3 = 65, l1_val=4.0, l2_val=3.0, l3_val=2.5;
		
	vector<vector<double> > base;
	vector<vector<double> > first;
	vector<vector<double> > second;
	vector<vector<double> > third;

	int n = 8, m = 3;
	
	base.resize(n,vector<double>(m));
	first.resize(n,vector<double>(m));
	second.resize(n,vector<double>(m));
	third.resize(n,vector<double>(m));

	vector<double> midpoint;

	midpoint.resize(3);
	
	// loop to take arguments from command line else take up default values
    for (int i = 0; i < argc; ++i)
    {
       if( strcmp(argv[i],"-t") == 0)
       {
           i++;
           angle1 = atof(argv[i]);
           //cout<<argv[i]<<" ";
       }
       else if(strcmp(argv[i], "-u") == 0)
       {
           i++;
           angle2 = atof(argv[i]);
           //cout<<argv[i]<<" ";
       }
       else if(strcmp(argv[i], "-v") == 0)
       {
           i++;
           angle3 = atof(argv[i]);
           //cout<<argv[i]<<" ";
       }
       else if(strcmp(argv[i], "-l") == 0)
       {
           i++;
           l1_val = atof(argv[i]);
           //cout<<argv[i]<<" ";
       }
       else if(strcmp(argv[i], "-m") == 0)
       {
       	   i++;
           l2_val = atof(argv[i]);
           //cout<<argv[i]<<" ";
       }
       else if(strcmp(argv[i], "-n") == 0)
       {
       	   i++;
           l3_val = atof(argv[i]);
           //cout<<argv[i]<<" ";
       }
    }
	
	base = generateMatrix(base, 2.0, 2.0, 1.0, -2.0, -2.0, 0.0);
	first = generateMatrix(first, 0.5, 0.5, l1_val, -0.5, -0.5, 0.0);
	second = generateMatrix(second, 0.5, 0.5, l2_val, -0.5, -0.5, 0.0);
	third = generateMatrix(third, 0.5, 0.5, l3_val, -0.5, -0.5, 0.0);

	first = rotationMatrix(angle1 , first, 1);
	midpoint = center(base);
	first = translateMatrix(midpoint[0], midpoint[1], midpoint[2], first);
		
	second = rotationMatrix(angle2, second, 0);
	second = rotationMatrix(angle1, second, 1);
	midpoint=center(first);
	second = translateMatrix(midpoint[0], midpoint[1], midpoint[2], second);
		
	third = rotationMatrix(angle2 + angle3, third, 0);
	third = rotationMatrix(angle1, third, 1);
	midpoint=center(second);
	third = translateMatrix(midpoint[0], midpoint[1], midpoint[2], third);

	midpoint=center(third);

	cout << "#Inventor V2.0 ascii\n";
	
	cout<<"Separator {\n";
	cout<<"  Coordinate3 {\n";
	cout<<"    point [\n";
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<"   "<<base[i][j];
		}
		if(i!=7)
			cout<<",\n";
	}
	cout<<"\n	]\n	}";

	cout<<"  IndexedLineSet {\n";
	cout<<"    coordIndex [\n";
	cout<<"	 0, 1, 2, 0, -1,\n";
	cout<<"	 0, 2, 3, 0, -1,\n";
	cout<<"	 7, 6, 5, 7, -1,\n";
	cout<<"	 7, 5, 4, 7, -1,\n";
	cout<<"	 0, 3, 7, 0, -1,\n";
	cout<<"	 0, 7, 4, 0, -1,\n";
	cout<<"	 1, 5, 6, 1, -1,\n";
	cout<<"	 1, 6, 2, 1, -1,\n";
	cout<<"	 0, 4, 5, 0, -1,\n";
	cout<<"	 0, 5, 1, 0, -1,\n";
	cout<<"	 3, 2, 6, 3, -1,\n";
	cout<<"	 3, 6, 7, 3, -1\n";
	cout<<"    ]\n";
	cout<<"  }\n";
	cout<<"}\n";

	cout<<"Separator {\n";
	cout<<"  Coordinate3 {\n";
	cout<<"    point [\n";
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<"   "<<first[i][j];
		}
		if(i!=7)
			cout<<",\n";
	}
	cout<<"\n	]\n	}";

	cout<<"  IndexedLineSet {\n";
	cout<<"    coordIndex [\n";
	cout<<"	 0, 1, 2, 0, -1,\n";
	cout<<"	 0, 2, 3, 0, -1,\n";
	cout<<"	 7, 6, 5, 7, -1,\n";
	cout<<"	 7, 5, 4, 7, -1,\n";
	cout<<"	 0, 3, 7, 0, -1,\n";
	cout<<"	 0, 7, 4, 0, -1,\n";
	cout<<"	 1, 5, 6, 1, -1,\n";
	cout<<"	 1, 6, 2, 1, -1,\n";
	cout<<"	 0, 4, 5, 0, -1,\n";
	cout<<"	 0, 5, 1, 0, -1,\n";
	cout<<"	 3, 2, 6, 3, -1,\n";
	cout<<"	 3, 6, 7, 3, -1\n";
	cout<<"    ]\n";
	cout<<"  }\n";
	cout<<"}\n";

	cout<<"Separator {\n";
	cout<<"  Coordinate3 {\n";
	cout<<"    point [\n";
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<"   "<<second[i][j];
		}
		if(i!=7)
			cout<<",\n";
	}
	cout<<"\n	]\n	}";

	cout<<"  IndexedLineSet {\n";
	cout<<"    coordIndex [\n";
	cout<<"	 0, 1, 2, 0, -1,\n";
	cout<<"	 0, 2, 3, 0, -1,\n";
	cout<<"	 7, 6, 5, 7, -1,\n";
	cout<<"	 7, 5, 4, 7, -1,\n";
	cout<<"	 0, 3, 7, 0, -1,\n";
	cout<<"	 0, 7, 4, 0, -1,\n";
	cout<<"	 1, 5, 6, 1, -1,\n";
	cout<<"	 1, 6, 2, 1, -1,\n";
	cout<<"	 0, 4, 5, 0, -1,\n";
	cout<<"	 0, 5, 1, 0, -1,\n";
	cout<<"	 3, 2, 6, 3, -1,\n";
	cout<<"	 3, 6, 7, 3, -1\n";
	cout<<"    ]\n";
	cout<<"  }\n";
	cout<<"}\n";

	cout<<"Separator {\n";
	cout<<"  Coordinate3 {\n";
	cout<<"    point [\n";
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<"   "<<third[i][j];
		}
		if(i!=7)
			cout<<",\n";
	}
	cout<<"\n	]\n	}";

	cout<<"  IndexedLineSet {\n";
	cout<<"    coordIndex [\n";
	cout<<"	 0, 1, 2, 0, -1,\n";
	cout<<"	 0, 2, 3, 0, -1,\n";
	cout<<"	 7, 6, 5, 7, -1,\n";
	cout<<"	 7, 5, 4, 7, -1,\n";
	cout<<"	 0, 3, 7, 0, -1,\n";
	cout<<"	 0, 7, 4, 0, -1,\n";
	cout<<"	 1, 5, 6, 1, -1,\n";
	cout<<"	 1, 6, 2, 1, -1,\n";
	cout<<"	 0, 4, 5, 0, -1,\n";
	cout<<"	 0, 5, 1, 0, -1,\n";
	cout<<"	 3, 2, 6, 3, -1,\n";
	cout<<"	 3, 6, 7, 3, -1\n";
	cout<<"    ]\n";
	cout<<"  }\n";
	cout<<"}\n";

	cout<<"Separator {\n";
	cout<<"LightModel {\n";
	cout<<"model PHONG\n";
	cout<<"}\n";
	cout<<"Material {\n";
	cout<<"        diffuseColor 1.0 1.0 1.0\n"; 
	cout<<"}\n";
	cout<<"Sphere {\n";
	cout<<"        radius  0.20\n"; 
	cout<<"}\n";
	cout<<"}\n";
	cout<<"Separator {\n";
	cout<<"LightModel {\n";
	cout<<"model PHONG\n";
	cout<<"}\n";
	cout<<"Material {\n";
	cout<<"        diffuseColor 1.0 1.0 1.0\n"; 
	cout<<"}\n";
	cout<<"Transform {\n";
	cout<<"	translation "<<midpoint[0]<<" "<<midpoint[1]<<" "<<midpoint[2]<<"\n";
	cout<<"}\n";
	cout<<"Sphere {\n";
	cout<<"        radius  0.20\n"; 
	cout<<"}\n";
	cout<<"}\n";		
	return 0;
}