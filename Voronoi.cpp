//source code by Harsh Kumar Narula, harsh.narula@iitbombay.org
//nstructions for compiling the code with different compilers (g++, cl.exe, and clang) and different flags.
// g++ -fopenmp -static -O3 -o grow2d.exe grow2d.cpp -lgomp -ldl
// cl.exe /EHsc /openmp /Ox grow2d.cpp
// clang & gcc clang++ -target x86_64-pc-windows-gnu -fopenmp -O3 -o grow2d.exe grow2d.cpp

#include "Voronoi.hpp"
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <fstream>



/**
 * Checks if the given vector is complete.
 *
 * A vector is considered complete if all its elements are non-zero.
 *
 * @param I The vector to be checked.
 * @return True if the vector is complete, false otherwise.
 */
bool iscomplete(const std::vector<int> &I)
{

	for (int i = 0; i < I.size(); ++i)
	{
		if (I[i] == 0)
		{

			return false;
		}
	}
	return true;
}

/**
 * Checks if the given vector of StageOfLife is complete.
 * 
 * @param a The vector of StageOfLife to check.
 * @return True if all elements in the vector are not equal to Growing, false otherwise.
 */
bool iscomplete(const std::vector<StageOfLife> &a)
{

	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] == Growing)
		{

			return false;
		}
	}
	return true;
}


/**
 * @brief Constructs a Voronoi object with the given parameters.
 * 
 * @param m The number of rows in the Voronoi diagram.
 * @param n The number of columns in the Voronoi diagram.
 * @param p The number of points in the Voronoi diagram.
 */
Voronoi::Voronoi(int m, int n, int p)
{
	this->m = m;
	this->n = n;
	this->p = p;
	this->r = 0;
	this->I.resize(m * n, 0);
	this->X.resize(p, 0);
	this->Y.resize(p, 0);
	this->a.resize(p, Growing);
	this->colors.resize(p+1);
}

/**
 * Nucleates the Voronoi diagram by randomly assigning labels to the grid cells.
 * 
 * @param M A pointer to the MTEngine object used for random number generation.
 */
void Voronoi::nucleate(MTEngine* M)
{
	
	int label = 1;
	int xo, yo, index;
	MTEngine M2;
	colors[0].r = 0;
	colors[0].g = 0;
	colors[0].b = 0;

	while (label <= p)
	{
		xo = round ((m - 1) * M->rand());
		yo = round ((n - 1) * M->rand());
		index = (n)*xo + yo;
		if (I[index] == 0)
		{
			I[index] = label;
			X[label - 1] = xo;
			Y[label - 1] = yo;
			M2.setseed(label);
			colors[label].r = M2.rand();
			colors[label].g = M2.rand();
			colors[label].b = M2.rand();
			label++;
		}
	}

	for (int i = 0; i < p; i++)
	{
		a[i] = Growing;
	}
	nucleated = true;
	r = 2;
}

/**
 * Nucleates the Voronoi diagram by creating a new MTEngine object,
 * calling the nucleate function, and then deleting the MTEngine object.
 */
void Voronoi::Nucleate()
{
	MTEngine* M = new MTEngine();
	nucleate(M);
	delete M;
}

/**
 * Nucleates the Voronoi diagram with the given seed.
 *
 * @param myseed The seed used for random number generation.
 */
void Voronoi::Nucleate(long long myseed)
{
	MTEngine* M = new MTEngine(myseed);
	nucleate(M);
	delete M;	
}

/**
 * @brief Grows the Voronoi diagram by one iteration.
 * 
 * This function performs one iteration of the growth process for the Voronoi diagram.
 * It checks each cell in the diagram and determines if it should be grown based on its neighbors.
 * The growth process continues until all cells have been grown or no more growth is possible.
 * 
 * @note This function assumes that the `Nucleate` function has been called before the first iteration of growth.
 * 
 * @note This function uses OpenMP parallelization to speed up the growth process.
 * 
 * @note This function updates the `I` and `a` arrays to reflect the growth of the diagram.
 * 
 * @note This function updates the `allgrown` flag to indicate if all cells have been grown.
 * 
 * @note This function updates the `r` variable to increase the radius of growth for the next iteration.
 * 
 * @note This function assumes that the `I`, `a`, `X`, `Y`, `m`, `n`, `p`, `Grown`, `Growing`, and `iscomplete` variables are properly initialized.
 */
void Voronoi::grow()
{
	if (!nucleated)
	{
		Nucleate();		
	}

	if (allgrown)
	{
		return ;
	}
	
	

	int xo, yo, label, low, px, py, index, N, E, W, S, val1, val2, val3, val4;
	const int s = I.size();
	N = 0;
	E = 0;
	W = 0;
	S = 0;

#pragma omp parallel for private(xo, yo, label, low, px, py, N, E, W, S, index, val1, val2, val3, val4) schedule(dynamic)
	for (int k = 0; k < p; ++k)
	{

		if (a[k] == 1)
		{

			xo = X[k];
			yo = Y[k];
			a[k] = Grown;

			label = k + 1;
			low = 0;
			for (int i = 0; i <= r; ++i)
			{
				for (int j = 0; j <= r; ++j)
				{

					if (i * i + j * j < r * r)
					{
						px = xo + i;
						py = yo + j;

						if (px >= 0 && px < m && py >= 0 && py < n)
						{
							index = (n)*px + py;

							if (I[index] == 0)
							{

								N = index - n;
								E = index + n;
								W = index + 1;
								S = index - 1;

								if (N >= 0 && N < s)
								{
									val1 = I[N];
								}
								else
								{
									val1 = 0;
								}

								if (E >= 0 && E < s)
								{
									val2 = I[E];
								}
								else
								{
									val2 = 0;
								}

								if (W >= 0 && W < s)
								{
									val3 = I[W];
								}
								else
								{
									val3 = 0;
								}

								if (S >= 0 && S < s)
								{
									val4 = I[S];
								}
								else
								{
									val4 = 0;
								}

								if (val1 == label || val2 == label || val3 == label || val4 == label)
								{
									I[index] = label;
									a[k] = Growing;
								}
							}
						}

						px = xo - i;
						py = yo + j;

						if (px >= 0 && px < m && py >= 0 && py < n)
						{
							index = (n)*px + py;

							if (I[index] == 0)
							{

								N = index - n;
								E = index + n;
								W = index + 1;
								S = index - 1;

								if (N >= 0 && N < s)
								{
									val1 = I[N];
								}
								else
								{
									val1 = 0;
								}

								if (E >= 0 && E < s)
								{
									val2 = I[E];
								}
								else
								{
									val2 = 0;
								}

								if (W >= 0 && W < s)
								{
									val3 = I[W];
								}
								else
								{
									val3 = 0;
								}

								if (S >= 0 && S < s)
								{
									val4 = I[S];
								}
								else
								{
									val4 = 0;
								}

								if (val1 == label || val2 == label || val3 == label || val4 == label)
								{
									I[index] = label;
									a[k] = Growing;
								}
							}
						}

						px = xo + i;
						py = yo - j;

						if (px >= 0 && px < m && py >= 0 && py < n)
						{
							index = (n)*px + py;

							if (I[index] == 0)
							{

								N = index - n;
								E = index + n;
								W = index + 1;
								S = index - 1;

								if (N >= 0 && N < s)
								{
									val1 = I[N];
								}
								else
								{
									val1 = 0;
								}

								if (E >= 0 && E < s)
								{
									val2 = I[E];
								}
								else
								{
									val2 = 0;
								}

								if (W >= 0 && W < s)
								{
									val3 = I[W];
								}
								else
								{
									val3 = 0;
								}

								if (S >= 0 && S < s)
								{
									val4 = I[S];
								}
								else
								{
									val4 = 0;
								}

								if (val1 == label || val2 == label || val3 == label || val4 == label)
								{
									I[index] = label;
									a[k] = Growing;
								}
							}
						}

						px = xo - i;
						py = yo - j;

						if (px >= 0 && px < m && py >= 0 && py < n)
						{
							index = (n)*px + py;

							if (I[index] == 0)
							{

								N = index - n;
								E = index + n;
								W = index + 1;
								S = index - 1;

								if (N >= 0 && N < s)
								{
									val1 = I[N];
								}
								else
								{
									val1 = 0;
								}

								if (E >= 0 && E < s)
								{
									val2 = I[E];
								}
								else
								{
									val2 = 0;
								}

								if (W >= 0 && W < s)
								{
									val3 = I[W];
								}
								else
								{
									val3 = 0;
								}

								if (S >= 0 && S < s)
								{
									val4 = I[S];
								}
								else
								{
									val4 = 0;
								}

								if (val1 == label || val2 == label || val3 == label || val4 == label)
								{
									I[index] = label;
									a[k] = Growing;
								}
							}
						}
					}
				}
			}
		}
	}

	allgrown = iscomplete(I);
	r = r + 1;
}

void Voronoi::Grow()
{
	while (!allgrown)
	{
		grow();
	}
	
}


/**
 * Writes the 2D data (I) to a CSV file.
 *
 * @param filename The name of the CSV file to write the data to.
 */
void Voronoi::WriteDataToCSV(std::string& filename)
{
	std::ofstream fout;
	fout.open(filename.c_str());
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n-1; ++j)
		{
			int index = (n)*i + j;
			fout<<I[index]<<",";
		}
		fout<<I[n*i + n-1]<<"\n";
		//fout<<endl;
	}
	fout.close();
}

Voronoi::~Voronoi()
{
}