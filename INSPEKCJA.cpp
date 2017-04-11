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
int s[MAXN];
int m[MAXN];
int vis[MAXN];
int dis[MAXN];
int par[MAXN];
int n;

void dfs(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		par[*it] = u;
		dfs(*it);
		s[u] += s[*it] + 1;
	}
}

void dfs2(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		dis[*it] = dis[u] + 1;
		dfs2(*it);
	}
}

LL get_sum(int u) {
	FOR(i,1,n) dis[i] = vis[i] = 0;
	dfs2(u);
	LL sum = 0;
	FOR(i,1,n) sum += dis[i];
	return sum;
}

LL largest(int u) {
	FOR(i,1,n) vis[i] = s[i] = 0;
	dfs(u);
	PII res(1,-1);
	FOREACH(it,g[u]) if(s[*it] > res.ND) {
		res.ST = *it;
		res.ND = s[*it];
	}
	FOR(i,1,n) vis[i] = dis[i] = 0;
	vis[u] = 1;
	dfs2(res.ST);
	return (*max_element(dis+1,dis+n+1))+1;
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
	FOR(i,1,n) FOREACH(it,g[i]) if(*it!=par[i]) m[i] = max(m[i], s[*it]+1);
	FOR(i,1,n) m[i] = max(m[i], n-s[i]-1);

	FOR(i,1,n) if(double(m[i]) <= n/2.0) {
		LL res = 2*get_sum(i);
		if(double(m[i]) < n/2.0) res -= *max_element(dis+1,dis+n+1);
		else res -= largest(i);
		printf("%lld\n", res);
	} else printf("-1\n");

	return 0;
}
