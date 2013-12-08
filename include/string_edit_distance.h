#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
/*
 *pSource is the string needs to convert to target string
 last the last index of string, source is from[0, source_last]
 * */
enum operation
{
	rep,
	del,
	add,
	match
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

struct slot
{
	slot()
	{
		cost_total = 0;
		op = -1;
	}
	int op;
	int cost_total;
};

int string_distance_DP(const char* pSource, int source_last, const char* pTarget, int target_last)
{
	string X(" ");
	string Y(" ");
	X += pSource;
	Y += pTarget;
	int m = source_last + 1;
	int n = target_last + 1;
	//build X, Y strings both from the start index of 1, X[1-m], Y[1-n]
	
	//build s as the memory of result, s[0-m][0-n], s[i][j] indicates the lowest edit cost of Xi and Yj
	vector<vector<slot> > s;
	vector<slot> t;
	t.resize(n+1,slot());
	s.resize(m+1,t);
	for(int row  = 0; row <= m;++row)
	{
		s[row][0].cost_total = row * del_cost(' ');
        s[row][0].op = del;
	}
    
	for(int col = 0; col <= n; ++col)
	{
		s[0][col].cost_total = col * add_cost(' ');
        s[0][col].op = add;
	}
	
	for(int i = 1; i <= m; ++i)
	{
		for(int j = 1; j<=n; ++j)
		{
			if(X[i] == Y[j])
			{
				s[i][j].op = match;
				s[i][j].cost_total = s[i-1][j-1].cost_total;
			}
			else	//sub problem of repalce, del, add
			{
				int op = -1;
				int lowest_cost = 0x7fffffff;
				for(int opindex = 0; opindex < 3; ++opindex)
				{
					int cost;
					if(opindex == rep)
					{
						cost = s[i-1][j-1].cost_total + replace_cost(X[i], Y[j]);
					}
					if(opindex == del)
					{
						cost = s[i-1][j].cost_total + del_cost(X[i]);
					}
					if(opindex == add)
					{
						cost = s[i][j-1].cost_total + add_cost(Y[j]);
					}
					
					if(cost < lowest_cost)
					{
						lowest_cost = cost;
						op = opindex;
					}
				}
                
				s[i][j].cost_total = lowest_cost;
				s[i][j].op = op;
			}
		}
	}
    
	int i = m;
	int j = n;
	stack<int> stack_of_op;
	while(true)
	{
		int op = s[i][j].op;
        
		if(i == 0 || j == 0)
		{
			if(i == 0 && j != 0)
			{
				for(int x = 0; x < j; x++)
					stack_of_op.push(op);
			}
			else if(i != 0 && j == 0)
			{
				for(int x = 0; x < i; x++)
					stack_of_op.push(op);
			}
			break;
		}
        
		stack_of_op.push(op);
		if(op == match)
		{
			--i;
			--j;
		}
		else if(op == rep)
		{
			--i;
			--j;
		}
		else if(op == del)
		{
			--i;
		}
		else if(op == add)
		{
			--j;
		}
	}
    
	while(!stack_of_op.empty())
	{
		char op[] = {'r','d','a','m'};
		cout << op[stack_of_op.top()];
		stack_of_op.pop();
	}
	cout << endl;
    
	return s[m][n].cost_total;
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
		
		//cout << string_distance_recursive(args[0].c_str(), args[0].length()-1, args[1].c_str(), args[1].length() - 1) << endl;
		cout << string_distance_DP(args[0].c_str(), args[0].length()-1, args[1].c_str(), args[1].length() - 1) << endl;
        
		cin.ignore();
	}
    
}

