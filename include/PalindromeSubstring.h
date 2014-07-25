#include <stdio.h>
#include <iostream>
#include <string>
#include <memory.h>
using namespace std;
const char unused_char = '#';
string GetLongestPalindromeSubstring(string target)
{
	//将target变成奇数
	string oddtarget;
	oddtarget += unused_char;
	for(unsigned int i = 0;i < target.length();++i)
	{
			oddtarget.append(target.c_str() + i, 1);
			oddtarget+=unused_char;
	}
	
	unsigned int* P = new unsigned int[oddtarget.length()];
	::memset(P, 0, oddtarget.length()* sizeof(int));
	
	unsigned int point = 0;
	unsigned int R = 0;
	for(unsigned int i = 0; i < oddtarget.length();++i)
	{
		P[i] = 1;
		if(point + R > i)
		{
			int j = 2*point-i;
			P[i] = ::min(P[j], point+R-i);
		}
		
		while(true)
		{
			if(oddtarget[i - P[i]] == oddtarget[i+P[i]])
				++P[i];
			else
				break;
		}
		
		if(P[i] > R)
		{
				point = i;
				R = P[i];
		}
	}
	
	string result;
	for(unsigned int i = point-R+1; i < point+R;++i)
	{
			if(oddtarget[i] != '#')
			{
					result += oddtarget[i];
			}
	}
	
	return result;
}