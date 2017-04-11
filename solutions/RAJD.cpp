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
const int MAXN = 1000005;
VI g[MAXN];
int vis[MAXN];
int dis[MAXN];
int l[MAXN];
int n, m;

void topo(int u, VI& order) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) topo(*it,order);
	order.PB(u);
}

void dfs(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		dis[*it] = max(dis[*it], dis[u]+1);
		dfs(*it);
	}
}

int find_longest(int s) {
	REP(i,n+1) {
		vis[i] = 0;
		dis[i] = -INF;
	}
	VI order, out(n+1);
	FOR(i,1,n) {
		REP(j,SIZE(g[i])) out[g[i][j]]++;
	}
	FOR(i,1,n) if(out[i] == 0 && i!=s) {
		topo(i,order);
		dis[i] = 0;
	}
	FOR(i,1,n) vis[i] = 0;
	FORD(i,SIZE(order)-1,0) if(!vis[order[i]] && order[i]!=s) {
		dfs(order[i]);
	}

	int ret = 0;
	FOR(i,1,n) ret = max(ret, dis[i]);

	return ret;
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		l[b] = a;
	}

	PII res(0,INF);

	FOR(i,1,n) {
		VI a, d = g[i];
		g[i].clear();
		FOR(j,1,n) {
			VI::iterator it = g[j].begin();
			while(it != g[j].end()) {
				if(*it == i) {
					g[j].erase(it);
					a.PB(j);
					break;
				}
				++it;
			}
		}

		int v = find_longest(i);

		if(v < res.ND) res = MP(i,v);

		FOREACH(it,a) g[*it].PB(i);
		g[i] = d;
	}

	printf("%d %d\n", res.ST, res.ND);

	return 0;
}
