#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct slot
{
	slot()
	{
		total = 0;
		c = 0;
	}
	char c;	// '<' '^' '\'
	int total;
};

string LCS(const string& s1, const string& s2)
{
	int s1_len = s1.length();
	int s2_len = s2.length();

	vector<vector<slot> > s;
	vector<slot> t;
	t.resize(s2_len,slot());
	s.resize(s1_len, t);

	//build one matrix with row count = s1_len, column count = s2_len.
	//s[i][j] means the longest common sequence of Xi and Yi 
	for(int i = 0; i< s1_len; ++i)
	{
		for(int j = 0; j < s2.length(); ++j)
		{
			if(s1[i] == s2[j])
			{
				char c = '\\';
				if(i ==0 || j == 0)
					s[i][j].total = 1;
									
				else
					s[i][j].total += s[i-1][j-1].total + 1;

				s[i][j].c = c; 
			}
			else	//find the longest from subproblems of s[i-1][j] and s[i][j-1]
			{
				if( i == 0 && j == 0 )
				{
					//do nothing
				}
				else if(i != 0 && j==0)
				{
					s[i][j].total = s[i-1][j].total;
					s[i][j].c = '^';
				}
				else if(i == 0 && j!=0)
				{
					s[i][j].total = s[i][j-1].total;
					s[i][j].c = '<';
				}
				else
				{
					s[i][j].total = max(s[i-1][j].total, s[i][j-1].total);
					if(s[i-1][j].total > s[i][j-1].total)
						s[i][j].c = '^';
					else
						s[i][j].c = '<';
				}
			}
		}
	}
	stack<char> stack_of_char;
	int i = s1_len-1;

	int j = s2_len-1;
	while(true)
	{
		if(i < 0 || j < 0 || s[i][j].c == 0)
			break;
		if(s[i][j].c == '\\')
		{
			stack_of_char.push(s1[i]);
			i--;
			j--;
		}
		else if(s[i][j].c == '<')
		{
			j--;
		}
		else if(s[i][j].c == '^')
		{
			i--;
		}
	}

	string result;
	while(!stack_of_char.empty())
	{
		result += stack_of_char.top();
		stack_of_char.pop();
	}

	return result;
}

using namespace std;
int main()
{
	int set_count;
	cin >> set_count;

	while(set_count--)
	{
		string line;
		int i = 0;
		string inputs[2];

		while(getline(cin,line))
		{
			if(line.length() == 0)
				continue;

			inputs[i++] = line;
			if( i == 2 )
			{
				string commonString = LCS(inputs[0], inputs[1]);
				cout << commonString << endl;
				i = 0;
			}
		}
	}
}
