#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
#include <cmath>
#include <queue>
#include <stack>
#include <cassert>
#include <cstring>
#include <climits>
#define VAR(i,v) __typeof(v) i = (v)
#define SIZE(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define REP(i,b) for(int i=0; i<(b); ++i)
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define FORD(i,a,b) for(int i=(a); i>=(b); --i)
#define FOREACH(i,c) for(VAR(i,(c).begin()); i != (c).end(); ++i)
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define NL printf("\n")

using namespace std;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef long long LL;

const int INF = 214748360;
const int MAXN = 4005;
set<int> g[MAXN];
bool vis[MAXN];
int dis[MAXN];
int best[MAXN];
int n;

bool bfs() {
	REP(i,MAXN) vis[i] = 0;
	REP(i,MAXN) dis[i] = best[i] = INF;
	vis[1] = 1;
	dis[1] = 0;
	
	queue<int> Q;
	Q.push(1);

	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		FOREACH(it,g[u]) if(!vis[*it]) {
			if(dis[*it] > dis[u] + 1) {
				dis[*it] = dis[u] + 1;
				best[*it] = u;
			}
			vis[*it] = true;
			Q.push(*it);
		}
	}

	VI r;
	int u = n;
	while(u != 1 && u != INF && best[u] != INF) {
		g[best[u]].erase(g[best[u]].find(u));
		r.PB(u);
		u = best[u];
	}

	return !r.empty();
}

int main() {
	scanf("%d", &n);
	REP(i,n-1) {
		int k;
		scanf("%d", &k);
		REP(j,k) {
			int d;
			scanf("%d", &d);
			g[i+1].insert(d);
		}
	}

	int res = 0;
	while(bfs()) res++;

	printf("%d\n", res);

	
	return 0;
}
