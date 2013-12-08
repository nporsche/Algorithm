#include <iostream>
#include <string>
using namespace std;
/*
 *pSource is the string needs to convert to target string
 last the last index of string, source is from[0, source_last]
 * */
enum operation
{
	rep,
	del,
	add
};

int replace_cost(char s, char t)
{
	return 1;
}

int del_cost(char c)
{
	return 1;
}

int add_cost(char c)
{
	return 1;
}

int string_distance_recursive(const char* pSource, int source_last, const char* pTarget, int target_last)
{
	if(source_last == -1)	//pSource is empty
	{
		int cost = 0;
		for(int i = 0; i<= target_last;++i)
		{
			cost+=add_cost(pTarget[i]);
		}

		return cost;
	}
	if(target_last == -1)
	{
		int cost = 0;
		for(int i = 0; i<= source_last;++i)
		{
			cost += del_cost(pSource[i]);
		}
		return cost;
	}

	/////
	if(pSource[source_last] == pTarget[target_last])
		return string_distance_recursive(pSource, source_last-1, pTarget, target_last-1);
	else
	{
		int op[3];	//
		op[rep] = string_distance_recursive(pSource, source_last-1, pTarget, target_last-1) + replace_cost(pSource[source_last],pTarget[target_last]);
		op[del] = string_distance_recursive(pSource, source_last-1, pTarget, target_last) + del_cost(pSource[source_last]);
		op[add] = string_distance_recursive(pSource, source_last, pTarget, target_last-1) + add_cost(pTarget[target_last]);

		int min = 0x7fffffff;
		for(int i = 0; i< 3;++i)
		{
			if(op[i] < min)
				min = op[i];
		}

		return min;
	}
}

int main()
{
	int count = 0;
	cin >> count;
	cin.ignore();
	while(count--)
	{
		string args[2];
		getline(cin,args[0]);
		getline(cin,args[1]);
		
		cout << string_distance_recursive(args[0].c_str(), args[0].length()-1, args[1].c_str(), args[1].length() - 1) << endl;
		cin.ignore();
	}

}
