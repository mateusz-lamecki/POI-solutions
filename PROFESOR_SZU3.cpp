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

const int INF = 2147483640;
const int MAXN = 1000005;
const int MAXM = 36501;
VI g[MAXN];
int *scc;
int *e;
vector<bool> vis(MAXN);
int *order;
int n, m;
int c;

void find_order(int u) {
	vis[u] = 1;
	REP(i,SIZE(g[u])) if(!vis[g[u][i]]) find_order(g[u][i]);
	order[c++] = u;
}

void mark(int u, int c) {
	VI S;
	S.PB(u);
	vis[u] = 1;
	scc[u] = c;
	while(!S.empty()) {
		int u = S.back();
		S.pop_back();
		REP(i,SIZE(g[u])) if(!vis[g[u][i]]) {
			vis[g[u][i]] = 1;
			scc[g[u][i]] = c;
			S.PB(g[u][i]);
		}
	}
}

void count(int u) {
	e[u] = 1;
	REP(u,c) REP(i,SIZE(g[order[u]])) e[g[order[u]][i]] = min(MAXM, e[order[u]]+e[g[order[u]][i]]);
}

void merge(int u) {
	VI Q;
	Q.PB(u);
	vis[u] = 1;
	while(!Q.empty()) {
		int u = Q.back();
		Q.pop_back();
		REP(i,SIZE(g[u])) if(e[u]>0 && e[g[u][i]]>0 && scc[u]==scc[g[u][i]]) e[u] = e[g[u][i]] = MAXM;
		REP(i,SIZE(g[u])) {
			if(e[u]>0 && e[g[u][i]]>0 && scc[u]==scc[g[u][i]]) e[u] = e[g[u][i]] = MAXM;
			if(e[u] == MAXM) e[g[u][i]] = MAXM;
			if(!vis[g[u][i]]) {
				vis[g[u][i]] = 1;
				Q.PB(g[u][i]);
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[b].PB(a);
	}

	order = new int[n+2];

	REP(i,n+2) order[i] = 0;

	FOR(i,1,n+1) if(!vis[i]) find_order(i);
	REP(i,c/2) swap(order[i],order[c-i-1]);

	FOR(i,1,n+1) vis[i] = 0;

	int p = c;
	int t = 0;

	scc = new int[n+2];
	e = new int[n+2];
	REP(i,n+2) scc[i] = e[i] = 0;

	FORD(i,p-1,0) if(!vis[order[i]]) mark(order[i], ++t);

	FOR(i,1,n+1) vis[i] = 0;
	count(n+1);

	delete[] order;

	FOR(i,1,n+1) vis[i] = 0;
	merge(n+1);

	int mx = 0;
	FOR(i,1,n+1) mx = max(mx, e[i]);

	if(mx == MAXM) printf("zawsze\n");
	else printf("%d\n", mx);

	int res = 0;
	FOR(i,1,n) if(e[i] == mx) res++;

	printf("%d\n", res);
	FOR(i,1,n) if(e[i] == mx) printf("%d ", i);
	NL;

	delete[] scc;
	delete[] e;

	return 0;
}
