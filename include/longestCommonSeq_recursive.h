#include <string>
#include <iostream>
using namespace std;

string LCS(const string& s1, const string& s2)
{
	string commonString;
	if(s1.length() == 0 || s2.length() == 0)
		return commonString;
	////
	if(s1[s1.length() - 1] == s2[s2.length() - 1])
	{
		commonString = LCS(s1.substr(0, s1.length()-1), s2.substr(0, s2.length()-1));
		commonString += s1[s1.length() - 1];
	}
	else
	{
		string r1 = LCS(s1, s2.substr(0, s2.length()-1));
		string r2 = LCS(s1.substr(0, s1.length()-1), s2);
		commonString = r1.length() > r2.length()? r1: r2;
	}

	return commonString;
}
int main()
{
	int set_count;
	cin >> set_count;
	cin.ignore();

	while(set_count--)
	{		
		string inputs[2];
		getline(cin,inputs[0]);
		getline(cin,inputs[1]);

		string commonString = LCS(inputs[0], inputs[1]);
		cout << commonString << endl;
		cin.ignore();
	}
}
