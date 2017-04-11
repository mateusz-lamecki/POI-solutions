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

const int INF = 21474800;
const int MAXN = 500005;
const int WINF = 36501;
VI g[MAXN];
VI gw[MAXN];
bool vis[MAXN];
int s[MAXN];
bool av[MAXN];
int res[MAXN];
bool self[MAXN];
int n, m;
VI S;

void dfs(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) dfs(*it);
	S.PB(u);
}

void dfs2(int u, int t) {
	vis[u] = 1;
	s[u] = t;
	FOREACH(it,gw[u]) if(!vis[*it]) dfs2(*it,t);
}

void mark_avaible(int u) {
	vis[u] = av[u] = 1;
	FOREACH(it,gw[u]) if(!vis[*it]) mark_avaible(*it);
}

void count() {
	int *count = new int[n+2];
	REP(i,n+2) count[i] = 0;

	FOR(i,1,n) count[s[i]]++;

	FOR(i,1,n) if(count[s[i]] > 1 || self[i]) res[i] = WINF;

	delete[] count;
}

void dfs3(int u) {
	vis[u] = 1;
	FOREACH(it,gw[u]) res[*it] = min(WINF, res[*it] + res[u]);
	FOREACH(it,gw[u]) if(!vis[*it]) dfs3(*it);
}

void calc_results() {
	res[n+1] = 1;
	dfs3(n+1);
}

void clear() {
	FOR(i,1,n+1) vis[i] = 0;
	vis[n+1] = 1;
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		if(a==b) self[a] = 1;
		g[a].PB(b);
		gw[b].PB(a);
	}

	FOR(i,1,n+1) if(!vis[i]) dfs(i);

	clear();

	int t = 0;
	FORD(i,SIZE(S)-1,0) if(!vis[S[i]]) dfs2(S[i],++t);

	clear();
	mark_avaible(n+1);

	clear();
	count();
	
	clear();

	calc_results();

	int best = 0;
	FOR(i,1,n) best = max(best, res[i]);

	VI result;
	FOR(i,1,n) if(res[i] == best) result.PB(i);

	if(best == WINF) printf("zawsze\n");
	else printf("%d\n", best);
	printf("%d\n", SIZE(result));
	FOREACH(it,result) printf("%d ", *it);
	NL;

	
	return 0;
}
