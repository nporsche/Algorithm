#include "util.h"

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
