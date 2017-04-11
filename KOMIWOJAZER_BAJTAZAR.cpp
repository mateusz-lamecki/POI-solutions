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
#include <functional>
//#include <unordered_set>
//#include <unordered_map>
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

const int INF = 2147483640;
const int MAXN = 30005;;
const int LOGN = 17;
VI g[MAXN];
int p[LOGN][MAXN];
int pre[MAXN];
int siz[MAXN];
bool vis[MAXN];
int dep[MAXN];
int n, m;

int k;

void dfs(int u) {
	vis[u] = 1;
	pre[u] = k++;
	siz[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		p[0][*it] = u;
		dep[*it] = dep[u]+1;
		dfs(*it);
		siz[u] += siz[*it];
	}
}

bool ancestor(int u, int v) {
	return (pre[u]>=pre[v] && pre[u]<pre[v]+siz[v]);
}

int lca(int u, int v) {
	if(ancestor(u,v)) return v;
	if(ancestor(v,u)) return u;
	int i = u, j = LOGN-1;
	while(j >= 0) {
		if(ancestor(v,p[j][i])) j--;
		else i = p[j][i];
	}
	return p[0][i];
}

int main() {
	scanf("%d", &n);
	REP(i,n-1) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}

	dfs(1);
	p[0][1] = 1;

	FOR(i,1,LOGN-1) FOR(j,1,n) p[i][j] = p[i-1][p[i-1][j]];

	int res = 0;
	int prev = 0;

	scanf("%d", &m);
	REP(i,m) {
		int a;
		scanf("%d", &a);
		if(i == 0) res = dep[a];
		else {
			int q = lca(a,prev);
			res += dep[a] + dep[prev] - 2*dep[q];
		}
		prev = a;
	}

	printf("%d\n", res);

	return 0;
}
