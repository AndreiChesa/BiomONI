#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;


ifstream f("biom.in");
ofstream g("biom.out");

const int NMAX = 1000002;

int n;
int costA;
int costB;
int costC;
int costD;

vector<pair<int,int>> G[NMAX];
string s;

pair<int,int> locatie[27];

// first -> primul indice
// second -> ultimul indice gasit
int mar;
bool viz[NMAX];

long long dij(int nod)
{
	priority_queue<pair<long long, int>> q;
	q.push({ 0,nod });
	while (!q.empty())
	{
		long long dist = q.top().first;
		int vf = q.top().second;
		q.pop();
		
		if (viz[vf] == true)
		{
			continue;
		}

		viz[vf] = true;

		if (vf == n)
		{
			return -dist;
		}

		for (auto it : G[vf])
		{
			if (viz[it.first] == false)
			{
				q.push({ dist - it.second,it.first });
			}
		}
	}
}

int main()
{
	f >> n;
	f >> costA >> costB >> costC >> costD;
	f >> s;
	mar = s.size();
	for (int i = 0; i <= mar - 1; i++)
	{
		int value = s[i] - 'a';
		if (locatie[value].first == 0)
		{
			locatie[value].first = i + 1;
		}
		else {
			G[i + 1].push_back({locatie[value].second,costD});
		}
		if (locatie[value].second != 0)
		{
			G[locatie[value].second].push_back({ i + 1,costC });
		}
		if (i != mar - 1)
		{
			G[i + 1].push_back({ i + 2,costA });
		}
		if(i!=0)
		{
			G[i + 1].push_back({ i,costB });
		}
		locatie[value].second = i + 1;
	}

	g << dij(1);
}