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
	int total;	//
};

string LCS(const string& s1, const string& s2)
{
	
	string X(" ");
	string Y(" ");
	X += s1;
	Y += s2;
	int m = s1.length();
	int n = s2.length();
	//X, Y are the strings from [1,m], [1,n] respectively
	
	//create the memory of result like a 2 demissions array, from [0~m][0~n]
	vector<vector<slot> > s;
	vector<slot> t;
	t.resize(n + 1,slot());
	s.resize(m + 1, t);

	for(int row = 0; row <= m;++row)
	{
		s[row][0].total = 0;
	}

	for(int column = 0; column <= n; ++column)
	{
		s[0][column].total = 0;
	}
	
	//fill the result to s[][], s[i][j].total means the maximum length of LCS of Xi, Yj
	for(int i = 1; i<= m;++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			if(X[i] == Y[j])
			{
				s[i][j].total = s[i-1][j-1].total + 1;
				s[i][j].c = '\\';
			}
			else	//get sub optimization problems. find the longest common string from s[i-1][j] and s[i][j-1]
			{
				if(s[i-1][j].total > s[i][j-1].total)
				{
					s[i][j].total = s[i-1][j].total;
					s[i][j].c = '^';
				}
				else
				{
					s[i][j].total = s[i][j-1].total;
					s[i][j].c = '<';
				}
			}
		}
	}
	//now we have the result of s[0~m][0~n]
	stack<char> stack_of_char;

	int i = m;
	int j = n;
	while(true)
	{
		if(s[i][j].c == '\\')
		{
			stack_of_char.push(X[i]);
			i--;
			j--;
		}
		else if(s[i][j].c == '<')
			j--;
		else if(s[i][j].c == '^')
			i--;
		else 
			break;
	}

	string result;
	while(!stack_of_char.empty())
	{
		result += stack_of_char.top();

		stack_of_char.pop();
	}

	return result;
}

int main()
{
	int set_count;
	cin >> set_count;
	cin.ignore();
	while(set_count--)
	{		
		string inputs[2];

		getline(cin, inputs[0]);
		getline(cin,inputs[1]);
		string commonString = LCS(inputs[0], inputs[1]);
		cout << commonString << endl;
		cin.ignore();
	}
	
}
