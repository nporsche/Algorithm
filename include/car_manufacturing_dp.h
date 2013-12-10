#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>
using namespace std;

#define INFINITE 0xffff
struct slot
{
	slot()
	{
		pre_line = -1;
		total = INFINITE;
	}
	int pre_line;
	int total;
};

int fastest_way_through_factory(int e[2], int a[2][6], int t[2][5], int x[2])
{
	slot s[2][6];
    
	for(int iStation = 0; iStation < 6; ++iStation)	//station index
	{
		for(int iLine = 0; iLine < 2;++iLine)	//line index
		{
			int cur_station_cost = a[iLine][iStation];
			if(iStation == 0)
			{
				s[iLine][iStation].total = cur_station_cost + e[iLine];
			}
			else
			{
				for(int pre_Line = 0; pre_Line < 2; ++ pre_Line)	//寻找子问题，前趋s[pre_Line][iStation-1]
				{
					int tmp_time = 0;
					tmp_time += s[pre_Line][iStation-1].total;
					if(pre_Line != iLine)
					{
						tmp_time += t[pre_Line][iStation-1];
					}
					tmp_time += cur_station_cost;
                    
					if(tmp_time < s[iLine][iStation].total)
					{
						s[iLine][iStation].total = tmp_time;
						s[iLine][iStation].pre_line = pre_Line;
					}
				}
			}
            
		}
	}
    
	slot f;
	int final_out_of_line;
	for(int iLine = 0; iLine < 2; ++iLine)
	{
		if(s[iLine][5].total + x[iLine] < f.total)
		{
			f = s[iLine][5];
			final_out_of_line = iLine;
		}
	}

	stack<int> stack_of_line;
	int iLine = final_out_of_line;
	int iStation = 5;	
	while(true)
	{
		if(iStation == 0)
			break;

		stack_of_line.push(s[iLine][iStation].pre_line);
		iLine = s[iLine][iStation].pre_line;
		iStation--;
	}
	while (!stack_of_line.empty())
	{
		cout << stack_of_line.top() + 1 << " ";
		stack_of_line.pop();
	}
	cout << final_out_of_line + 1 << endl;

    
	return f.total + x[final_out_of_line];
}

int car_manufacturing(int e[2], int a[2][6], int t[2][5], int x[2])
{
	return fastest_way_through_factory(e,a,t,x);
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


