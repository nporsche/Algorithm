//#include "Loan.h"
#include "Dynamic_Programming.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;
int main(int argc, const char * argv[])
{
	BeginManufacturing();
	vector<int> v;
	v.push_back(10);
	for(auto x : v)
	{
		cout << x << endl;
	}
	map<int,int> m;
	m[10] = 5;

	cout << m[10] << endl;
	return 0;
}

