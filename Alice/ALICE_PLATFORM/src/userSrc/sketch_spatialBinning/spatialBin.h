#ifndef SPATIAL_BIN
#define SPATIAL_BIN

#include "ALICE_DLL.h"

#define bucketSize 30
struct bucket
{
	int n;
	int ids[bucketSize];
	void addId(int &i)
	{

		if (n >= bucketSize)return;
		ids[n] = i;
		n++;
	}
	void clearBucket()
	{
		n = 0;
	}
	bool containsParticles()
	{
		return (n > 0);
	}
};


class spaceGrid
{

#define MAX_SPATIAL_BIN_POINTS 100000
public:

	vec *positions;

	int np;

	#define RES 30 	
	bucket buckets[RES*RES*RES];
	double dx, dy, dz;
	vec min, max;

	spaceGrid()
	{
		np = 0;
		positions = new vec[MAX_SPATIAL_BIN_POINTS];
	}

	spaceGrid( vec *pos, int _np)
	{
		positions = pos;
		np = _np;
	}
	////////////////////////////////////////////////////////////////////////// utility methods 
	
	void addPosition(vec & pt)
	{
		positions[np] = pt;
		np++;
	}
	int getNeighBors(int *&nBorIds, vec inPt, double searchRadius)
	{
		int sRad_x, sRad_y, sRad_z;
		sRad_x = (searchRadius / dx) + 2;
		sRad_y = (searchRadius / dy) + 2;
		sRad_z = (searchRadius / dz) + 2;

		////////////////////////////////////////////////////////////////////////// calculate voxel nBor search-index based on link-radius

		int u, v, w, index, nborId; // to store 1D and 3D voxel indices per particles, and neighbor id.
		vec pt, p_n, vel, v_n, diff; // to temp.store positions/velocities of particle and its neighbor.
		double dSq; // to store square of the distance

		nBorIds = new int[bucketSize * sRad_x * 2 + bucketSize * sRad_y * 2 + bucketSize * sRad_z * 2];
		int n_cnt = 0;

		{
			pt = inPt;
			threeDIndexFromPosition(pt, u, v, w);
			if (u == -1 || v == -1 || w == -1)return 0;
			//search in nborhood

			for (int i = u - sRad_x; i <= u + sRad_x; i++)
				for (int j = v - sRad_y; j <= v + sRad_y; j++)
					for (int k = w - sRad_z; k <= w + sRad_z; k++)
					{
						index = threeDIndexToIndex(i, j, k);

						if (index < RES*RES*RES && index >= 0)
							if (buckets[index].containsParticles())
								for (int nb = 0; nb < buckets[index].n; nb++)
								{

									nborId = buckets[index].ids[nb];
									if (nborId >= np)continue;

									p_n = positions[nborId];
									diff = p_n - pt;
									if (diff * diff < searchRadius * searchRadius)
									{
										nBorIds[n_cnt] = nborId;
										n_cnt++;
									}
								}
					}
		}
		return (n_cnt);
	}
	int getPointsFromLowestNBuckets(int *&nPoints, int nBoxes)
	{

		int numPoints = 0;
		int nbx = 0;
		while (nbx < nBoxes && nbx < RES*RES*RES)
		{
			if (buckets[nbx].containsParticles())numPoints += buckets[nbx].n;
			nbx++;
		}


		int cnt = 0;
		nPoints = new int[numPoints];

		for (int i = 0; i < nBoxes; i++)
			for (int j = 0; j < buckets[i].n; j++)
			{
				nPoints[cnt] = buckets[i].ids[j];
				cnt++;
			}
		return cnt;
	}
	void indexToThreeDIndex(int &index, int &u, int &v, int &w)
	{
		u = index % RES;
		v = (index / RES) % RES;
		w = index / (RES * RES);
	}
	int threeDIndexToIndex(int &i, int &j, int &k)
	{
		int index = (i + j*RES + k*RES*RES);
		return (index > 0 && index < RES*RES*RES) ? index : -1;
	}
	void threeDIndexFromPosition(vec p, int &u, int &v, int &w)
	{
		p.x -= min.x;
		p.y -= min.y;
		p.z -= min.z;
		u = floor(p.x / dx); v = floor(p.y / dy); w = floor(p.z / dz);

		if (u >= RES || u < 0)u = -1;
		if (v >= RES || v < 0)v = -1;
		if (w >= RES || w < 0)w = -1;
	}
	vec centerOfBucket(int &u, int &v, int &w)
	{
		return (min + (vec(u*dx, v*dy, w*dz) + vec(dx, dy, dz)) * 0.5);
	}
	void clearBuckets()
	{
		int index;
		for (int i = 0; i < RES; i++)
			for (int j = 0; j < RES; j++)
				for (int k = 0; k < RES; k++)buckets[i + j*RES + k*RES*RES].clearBucket();
	}
	void computeBucketDimensions()
	{
		if ((max.z - min.z) < 0) max.z = min.z = 0;

		vec diff = max - min;
		dx = diff.x / (float)RES;
		dy = diff.y / (float)RES;
		dz = diff.z / (float)RES;

		if (dz < 1e-04)dz = 1e-04;

		/*oneOverDx = 1.0 / dx;
		oneOverDy = 1.0 / dy;
		oneOverDz = 1.0 / dz;*/
	}
	void getBoundingBox(vec &min, vec &max)
	{
		double x = pow(10, 10);
		min = vec(x, x, x);
		max = min * -1;

		for (int i = 0; i < np; i++)
		{
			min.x = MIN(positions[i].x, min.x);
			min.y = MIN(positions[i].y, min.y);
			min.z = MIN(positions[i].z, min.z);

			max.x = MAX(positions[i].x, max.x);
			max.y = MAX(positions[i].y, max.y);
			max.z = MAX(positions[i].z, max.z);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void PartitionParticlesToBuckets()
	{
		clearBuckets();

		getBoundingBox(min, max);


		computeBucketDimensions();

		vec pt; int index;
		int u, v, w;
		for (int i = 0; i < np; i++)
		{
			pt = positions[i];
			threeDIndexFromPosition(pt, u, v, w);
			index = threeDIndexToIndex(u, v, w);

			if (index != -1)
				buckets[index].addId(i);

		}
	}

	//////////////////////////////////////////////////////////////////////////
	void drawBuckets()
	{
		glLineWidth(1);
		int index;
		for (int i = 0; i < RES; i++)
			for (int j = 0; j < RES; j++)
				for (int k = 0; k < RES; k++)
					if (buckets[threeDIndexToIndex(i, j, k)].containsParticles())
						drawCube(min + vec(i*dx, j*dy, k*dz), min + vec(i*dx, j*dy, k*dz) + vec(dx, dy, dz), vec(0, 0, 0), false, vec4(0.35, 0.35, 0.35, 1));
	}
	void drawParticlesInBuckets()
	{
		glPointSize(5);
		int u, v, w;
		for (int i = 0; i < RES*RES*RES; i++)
		{

			if (buckets[i].n > 0)
			{
				indexToThreeDIndex(i, u, v, w);
				for (int nb = 0; nb < buckets[i].n; nb++)
				{
					glColor3f(ofMap(u, 0, RES, 0, 1), ofMap(v, 0, RES, 0, 1), ofMap(w, 0, RES, 0, 1));
					drawPoint(positions[buckets[i].ids[nb]]);
				}
			}
		}
		glPointSize(1);
	}

};
#endif // !SPATIAL_BIN
