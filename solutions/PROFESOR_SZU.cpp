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

const int INF = 2147483640;
const int MAXN = 500005;
const int MAXA = 36501;
VI g[MAXN];
VI gw[MAXN];
bool self[MAXN];
bool vis[MAXN];
int s[MAXN];
int h[MAXN];
VI post;
int n, m;

void dfs(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		dfs(*it);
	}
	post.PB(u);
}

void mark(int u, int t) {
	vis[u] = 1;
	s[u] = t;
	FOREACH(it,gw[u]) if(!vis[*it]) mark(*it,t);
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		gw[b].PB(a);
		if(a == b) self[a] = 1;
	}

	FOR(i,1,n) if(!vis[i]) dfs(i);
	FOR(i,1,n+1) vis[i] = 0;

	int t = 1;
	FORD(i,SIZE(post)-1,0) if(!vis[post[i]]) {
		mark(post[i],t++);
	}

	VI res;
	FOR(i,1,n) h[s[i]]++;
	FOR(i,1,n) {
		if(h[s[i]] > 1 || self[i]) res.PB(i);
	}

	if(!res.empty()) {
		printf("zawsze\n");
		printf("%d\n", SIZE(res));
		FOREACH(it,res) printf("%d ", *it);
		NL;
	} else {
		FOR(i,1,n) h[i] = 0;
		h[n+1] = 1;
		int res2 = 0;
		REP(i,SIZE(post)) {
			int x = post[i];
			FOREACH(it,gw[x]) h[*it] = min(MAXA, h[*it] + h[x]);
		}
		FOR(i,1,n) {
			if(h[i] > res2) {
				res.clear();
				res.PB(i);
				res2 = h[i];
			} else if(h[i] == res2) res.PB(i);
		}
		if(res2 < MAXA) printf("%d\n", res2);
		else printf("zawsze\n");
		printf("%d\n", SIZE(res));
		FOREACH(it,res) printf("%d ", *it);
		NL;
	}

	return 0;
}
