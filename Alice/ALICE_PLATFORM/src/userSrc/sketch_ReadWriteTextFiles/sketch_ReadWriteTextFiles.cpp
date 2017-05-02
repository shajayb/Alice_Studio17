

#ifdef _MAIN_

#include "main.h"
#include "MODEL.h"
#include <array>
#include <memory>
#include<time.h>
#include<experimental/generator> 

using namespace std;
using namespace std::experimental;



///////// ----------------------------------------- model - view - controller (MVC) paradigm / pattern / template  ----------------- ////////////////////////////// 
/////////////////////////// model  ///////////////////////////////////////////


int maxLines = 1000;
vector<vec> pts; // storage container (vector) to store the vectors (points);


void setup()
{
	// open the appropriate file for reading
	std::fstream fs("data/pts.txt", ios::in);

	// set initial number of lines to 0;
	int numLines = 0;
	
	// while the file has content left to be read (i.e. the end of file has NOT been reached ), repeatedly perform these actions
	/*
	1. get the current line from the open file
	2. convert contents of the line into coordinates and then to a point
	3. store point in pts container
	*/
	while (!fs.eof() && numLines < maxLines ) // the second condition is a safety check, in case the file is corrupt
	{
		char str[2000]; // a storage container to store characters
		fs.getline(str, 2000); // get the current line from the open file, store contents of line in str (character array);
		vector<string> content = splitString(str, ","); // collect characters into strings, by looking for comma separators in the character array;
		
			if (content.size() != 3)continue; // if the number of strings is not equal 3, skip and go to next line
		
		float x = atof( content[0].c_str() ); // convert the first string into characters (.c_str()), then convert character to float (atof);
		float y = atof( content[1].c_str() );// convert the second string into characters (.c_str()), then convert character to float (atof);
		float z = atof( content[2].c_str() );// convert the thrid string into characters (.c_str()), then convert character to float (atof);

		vec curPt = vec(x,y,z); // create a point(vector) from floats;
		pts.push_back(curPt); // push back the Point into the storage container (vector - pts)

		numLines++; // increment the counter keeping track of number of lines.
	}

	fs.close(); // close file;
}

void update(int value)
{
}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);


	///----- drawLines
	glLineWidth(3);
	glColor3f(0, 0, 0);
	lineStyle(3);

		int n = pts.size();
		for (int i = 0; i < n; i++)
		{
			int next = (i + 1) % n; // a formula to get the next number to the current in a cyclical way : i.e next of 1 = 2, next of last point = 0;
									// % is the modulo operation, and returns thee remainder when the numerator( i+1) is divided by n;
								    // thus when i + 1 == n, the remainder is 0;
			drawLine(pts[i], pts[next]); // draw line between current point and next point;
		}


	glLineWidth(1);
	lineStyle(0);

	///----- drawPoints

	glPointSize(15);
	glColor3f(1, 0, 0);
	for (int i = 0; i < n; i++)drawPoint(pts[i]);

	glPointSize(1);
	glColor3f(1, 1, 1);
}

/////////////////////////// control  ///////////////////////////////////////////
void mousePress(int b, int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{
}

void keyPress(unsigned char k, int xm, int ym)
{

	// when 'w' is pressed,  output the contents of the pts vector into a text file
	if (k == 'w')
	{
		// construct outputFile object
		ofstream outputFileName;
		char outStr[600]; // character array

		//- create a file called out.txt in the data folder  
		outputFileName.open( "data/out.txt", ios::out);

		// check if file was created, else report an error
			if ( outputFileName.fail() )cout << " error in creating file : data/out.txt " << endl;

		// iterate through the points of pts vector, write the coordinates into the open file
		for (int i = 0; i < pts.size(); i++)
		{
			vec pt = pts[i]; // get current point in vector

			// format the output string, separated by commas, and plugging in coordinates ;
			sprintf(outStr, " %1.2f,%1.2f,%1.2f", pt.x,pt.y,pt.z ); /* see fo details http://www.cplusplus.com/reference/cstdio/sprintf/ */
			
			// output (stream) the formatted string into the open file.
			outputFileName << outStr << endl;
		}

		// close the file
		outputFileName.close();
		
		// report success
		cout << " exporting points / writing file : DONE " << endl;
	}
	

}





#endif // _MAIN_
