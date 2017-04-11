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

const int INF = 1047483640;
const int MAXN = 2000015;
VI g[MAXN];
int s[MAXN];
int t[MAXN];
int d[MAXN];
VI r[MAXN];
bool vis[MAXN];
int dis[MAXN];
bool res[MAXN];
int n, m, k;

int bfs(int u) {
	FOR(i,1,2*n+1) vis[i] = 0;
	FOR(i,1,2*n+1) dis[i] = INF;
	vis[u] = 1;
	dis[u] = 0;
	queue<int> Q;
	Q.push(u);
	int res = 0;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		res++;
		FOREACH(it,g[u]) {
			dis[*it] = min(dis[*it], dis[u]+1);
			if(!vis[*it]) {
				vis[*it] = 1;
				Q.push(*it);
			}
		}
	}
	return res-1;
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a*2].PB(b*2+1);
		g[a*2+1].PB(b*2);
		g[b*2].PB(a*2+1);
		g[b*2+1].PB(a*2);
	}

	REP(i,k) scanf("%d %d %d", &s[i], &t[i], &d[i]);
	REP(i,k) r[s[i]].PB(i);

	FOR(i,1,n) {
		int q = bfs(i*2);
		FOREACH(it,r[i]) {
			int v = t[*it];
			int ds = d[*it];
			res[*it] = (dis[v*2+(ds%2)] <= ds && q);

		}
	}

	REP(i,k) printf("%s\n", res[i] ? "TAK" : "NIE");

	return 0;
}
