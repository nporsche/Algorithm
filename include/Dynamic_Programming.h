#ifndef DYNMIC_PROGRAMMING_H
#define DYNMIC_PROGRAMMING_H

int** AllocArray(int row, int col);
void DeleteArray(int** p, int row);
int fastestWayThroughStation(int line, int station, int** a, int* e, int** t);
int fastestWayThroughStation_dp(int line, int station, int** a, int* e, int** t);
int fastestWayThroughFactory(int station, int** a, int* e, int** t,int* x);
void BeginManufacturing();

#endif
