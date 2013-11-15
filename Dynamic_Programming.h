#include <algorithm>    // std::min
#include <iostream>

int** AllocArray(int row, int col)
{
	int** table = new int*[row];
	for(int i = 0; i < row; ++i)
	{
		table[i] = new int[col];
	}

	return table;
}

void DeleteArray(int** p, int row)
{
	for(int i = 0;i<row;++i)
	{
		delete[] p[i];
	}

	delete[] p;
}

int fastestWayThroughStation(int line, int station, int** a, int* e, int** t)
{
	if(station == 1)
	{
		return a[line][1] + e[line];
	}

 	int anotherLine = line == 1 ? 2 : 1;

	return std::min(a[line][station]+fastestWayThroughStation(line, station - 1,a,e,t),
		a[line][station]+fastestWayThroughStation(anotherLine, station - 1,a,e,t) + t[anotherLine][station-1]);
}


int fastestWayThroughStation_dp(int line, int station, int** a, int* e, int** t)
{
	int** result = AllocArray(3,station+1);
	result[1][1] = e[1] + a[1][1];
	result[2][1] = e[2] + a[2][1];

	for(int iStation = 2; iStation <= station; iStation++)
	{
		for(int iLine = 1; iLine <= 2; iLine++)
		{
			int anotherLine = iLine == 1? 2: 1;
			int fromSameLine = result[iLine][iStation - 1] + a[iLine][iStation];
			int fromAnotherLine  = result[anotherLine][iStation - 1] + t[anotherLine][iStation-1] + a[iLine][iStation];
			result[iLine][iStation] = std::min(fromSameLine, fromAnotherLine);
		}
	}

	int r = result[line][station];
	DeleteArray(result,3);
	
	return r;
}

int fastestWayThroughFactory(int station, int** a, int* e, int** t,int* x)
{
		return  std::min(fastestWayThroughStation_dp(1,station,a,e,t) + x[1], fastestWayThroughStation_dp(2,station,a,e,t) + x[2]);
}


void BeginManufacturing()
{
	std::cout << "Begin" << std::endl;
	int** a = AllocArray(3,7);
	a[1][1] = 7;
	a[1][2] = 9;
	a[1][3] = 3;
	a[1][4] = 4;
	a[1][5] = 8;
	a[1][6] = 4;

	a[2][1] = 8;
	a[2][2] = 5;
	a[2][3] = 6;
	a[2][4] = 4;
	a[2][5] = 5;
	a[2][6] = 7;

	int** t = AllocArray(3,6);
	t[1][1] = 2;
	t[1][2] = 3;
	t[1][3] = 1;
	t[1][4] = 3;
	t[1][5] = 4;

	t[2][1] = 2;
	t[2][2] = 1;
	t[2][3] = 2;
	t[2][4] = 2;
	t[2][5] = 1;

	int e[3];
	e[1] = 2;
	e[2] = 4;

	int x[3];
	x[1] = 3;
	x[2] = 2;

	int fw = fastestWayThroughFactory(6,a,e,t,x);
	std::cout << "Fastest Way through Factory is: " << fw << std::endl;

	DeleteArray(a,3);
	DeleteArray(t,3);
}
