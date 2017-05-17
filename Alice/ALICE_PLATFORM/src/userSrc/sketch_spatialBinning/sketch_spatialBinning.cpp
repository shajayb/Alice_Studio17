#define _MAIN_


#ifdef _MAIN_

#include "main.h"
#include "MODEL.h"
#include <array>
#include <memory>
#include<time.h>
#include<experimental/generator> 

using namespace std;
using namespace std::experimental;
#include "sketch_spatialBinning\spatialBin.h"


///////// ----------------------------------------- model - view - controller (MVC) paradigm / pattern / template  ----------------- ////////////////////////////// 
/////////////////////////// model  ///////////////////////////////////////////

/// ----- variables
#define rx ofRandom(-1,1)
#define NUMBER_OF_POINTS 5000
vec pos[NUMBER_OF_POINTS]; // an empty array of vectors, to hold the positions of the points;

spaceGrid grd; // to perform uniform grid spatial partitioning

/// 

void setup()
{


	for (int i = 0; i < NUMBER_OF_POINTS; i++)pos[i] = vec(rx, rx, rx).normalise() * 50;

	// pass the pointer (by reference) to the vec array (pos) to the connstructor of grd class ;
	// thus when locations of the vectors in the pos array changes, the vec array inside grd is automatically updated
	// downside : you have to destruct grd when pos goes out of scope or is invalid;

	// CONSTRUCT A UNIFORM SPATIAL GRID-BIN , DEFAULT RESOLUTION IN 30 X 30 X 30 ;
	// grid resolution is a parameter that needs to be tuned to specific point distributions, for best performance
	// for highly uneven distribution of points, consider other spatial bins such as octree, kdtree etc.

	// initialise the spaceGrid object;
	grd = *new spaceGrid(pos, NUMBER_OF_POINTS); // the first argument is a pointer to an array of vectors(pos). this array can be inside a class.
}

void update(int value)
{

	// if needed , update locations of points in pos array
	for (int i = 0; i < NUMBER_OF_POINTS; i++)pos[i] += vec(rx, rx, rx).normalise() * 0.1;
	
	
	// re-compute the spatial binning
	// notice the grd.positions array doesn't need to be updated;
	// this is because the spaceGrid stores a pointer to the array of vectors (pos)
	grd.PartitionParticlesToBuckets();
}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	//drawGrid(20);

	// draw particles in each voxel / bucket. 
	grd.drawParticlesInBuckets();


	// for each particle in the pos array, get the (Ids of) nearest neighbors (within a radius), draw lines to them
	int *nbors; // an empty array , to hold ID of neigbors.

	glColor3f(0, 0, 0);
	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		int n = grd.getNeighBors(nbors, pos[i], 6); // arguments : 1. empty container to hold nBorIds, 2. input position to query neighbors 3. search radius
													// nBors integer array gets filled by this function.

		// draw lines from current query point to all its neighbors witin search radius.
		for (int j = 0; j < n; j++) drawLine(pos[i], pos[nbors[j]]);

	}
	
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


	

}





#endif // _MAIN_
