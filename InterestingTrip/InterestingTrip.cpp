#include <iostream>
#include <vector>
#include <math.h>
#include <queue> // очередь
#include <stack> // стек
using namespace std;

using namespace std;

int rast(int x1, int y1, int x2, int y2)
{
	return abs(x2 - x1) + abs(y2 - y1);
}

int main()
{
	int n;
	cin >> n;

	vector<vector<int>> koord(n);
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		koord[i].push_back(x);
		koord[i].push_back(y);
	}

	int max_rast;
	cin >> max_rast;

	int ind1_town, ind2_town;
	cin >> ind1_town >> ind2_town;

	int tec_rast = 0;

	//Расчет расстояния между каждой парой городов.
	vector<vector<int>> graf;
	graf.resize(n);
	bool verNull = true;

	for (int i = 0; i < n; i++)
	{
		graf[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			if (j != i)
			{
				int tec_rast = rast(koord[i][0], koord[i][1], koord[j][0], koord[j][1]);
				if (tec_rast <= max_rast && tec_rast>0) {
					graf[i][j] = 1;
					verNull = false;
				}
				else graf[i][j] = 0;
			}
			else graf[i][j] = 0;
		}
	}
	if (verNull) cout << -1 << endl;
	else {
		queue<int> Queue;
		queue<int> Queue_buf;
		int req;

		vector<int> nodes; 
		nodes.resize(n);
		for (int i = 0; i < n; i++) 
			nodes[i] = 0;

		req = ind2_town; req--;

		Queue.push(ind1_town - 1); 

		int count = 0;
		bool flag = false;
		bool flag1 = false;
		while (!Queue.empty())
		{
			flag1 = false;
			int node = Queue.front(); 
			Queue.pop();
			nodes[node] = 2; 
			for (int j = 0; j < n; j++)
			{
				if (graf[node][j] == 1 && nodes[j] == 0)
				{ 
					Queue_buf.push(j); 
					nodes[j] = 1; 
					if (node == req)
					{
						break;
					}
				}
				if (j == n - 1 && Queue.empty())
				{
					count++;
					Queue = Queue_buf;
					while (!Queue_buf.empty())
					{
						int s = Queue_buf.front();
						if (s == req) {
							flag = true;
							break;
						}
						Queue_buf.pop();
					}
				}
				if (flag) break;
			}
			if (flag)break;
		}
		if (Queue.empty() && Queue_buf.empty() && !flag)
		{
			count = -1;
			cout << count;
			return 0;
		}
		if (count == 0) cout << -1;
		else cout << count;
	}
	return 0;
}
