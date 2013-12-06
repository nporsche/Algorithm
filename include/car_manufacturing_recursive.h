#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>
using namespace std;


int fastest_way_through_station(int iStation, int line, int e[2], int a[2][6], int t[2][5], int mem[])
{
	if(iStation == 0)
	{
		return e[line] + a[line][iStation];
	}
	///////
	int anotherline = line == 0 ? 1:0;
	int time_of_cur_station = a[line][iStation];
	int r1 = fastest_way_through_station(iStation - 1, line, e,a,t, mem) + time_of_cur_station;	//from same line
	int r2 = fastest_way_through_station(iStation - 1, anotherline, e,a,t,mem) + time_of_cur_station + t[anotherline][iStation - 1];
	mem[iStation] = r1 < r2? line : anotherline;

	return min(r1,r2);
}

int car_manufacturing(int e[2], int a[2][6], int t[2][5], int x[2])
{
	int mem1[6]; //mem[i][j] 第i个station选的是哪一个line
	int r1 = fastest_way_through_station(5,0,e,a,t,mem1) + x[0];	//from station 1,6.

	int mem2[6]; 
	int r2 = fastest_way_through_station(5,1,e,a,t,mem2) + x[1];	//from station 2,6
	
	int* final_mem = r1 < r2? mem1:mem2;
	int final_line = r1 < r2 ? 0:1;
	stack<int> s;
	s.push(final_line);
	for(int i = 5; i > 1; ++i)
	{
		s.push(final_mem[i]);
	}
	while(!s.empty())
	{
		cout << s.top();
		cout << " ";
		s.pop();
	}
	cout << endl;
	return min(r1,r2);
}

int main()
{
	int e[2];
	int a[2][6];
	int t[2][5];
	int x[2];

	cin >> e[0] >> e[1];	//fill e
	for(int i = 0; i<2;++i)	//fill a
	{
		for(int j = 0; j< 6;++j)
		{
			cin >> a[i][j]; 
		}

	}

	for(int i = 0; i<2;++i)
	{
		for(int j = 0; j< 5;++j)
		{
			cin >> t[i][j]; 
		}
	}

	cin >> x[0] >> x[1];
	
	cout << "The fastest way required:" << car_manufacturing(e,a,t,x) << endl;;

	return 0;

}

