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

struct Edge {
	int v, c;
	Edge(int v, int c) : v(v), c(c) { }
};

const int INF = 2147483640;
const int MAXN = 100005;
vector<Edge> g[MAXN];
vector<Edge> f[MAXN];
set<int> h[MAXN];
int u1[MAXN], u2[MAXN];
bool vis[MAXN];
int n, m;

int main() {
	scanf("%d %d", &n, &m);

	FOR(i,1,n) u1[i] = u2[i] = 1;

	REP(i,m) {
		int a, b, s, t;
		scanf("%d %d %d %d", &a, &b, &s, &t);
		if(s == 0) s = 1;
		else s = -1;
		if(t == 0) t = 1;
		else t = -1;
		g[a].PB(Edge(b,s));
		g[b].PB(Edge(a,s));
		f[a].PB(Edge(b,t));
		f[b].PB(Edge(a,t));
		if(s != t) {
			h[a].insert(b);
			h[b].insert(a);
		}
	}

	bool valid = 1;
	FOR(i,1,n) {
		int u1 = 1, u2 = 1;
		FOREACH(it,g[i]) u1 *= it->c;
		FOREACH(it,f[i]) u2 *= it->c;
		if(u1 != u2) valid = 0;
	}

	if(!valid) {
		printf("NIE\n");
		return 0;
	}
	
	vector<VI> res;

	FOR(i,1,n) {
		VI S;
		S.PB(i);
		vis[i] = 1;

		while(!h[i].empty()) {
			if(S.empty()) S.PB(i);
			int w = *h[S.back()].begin();
			h[S.back()].erase(h[S.back()].find(w));
			h[w].erase(h[w].find(S.back()));
			S.PB(w);
			if(vis[w]) {
				res.PB(VI());
				res.back().PB(w);
				S.pop_back();
				while(!S.empty() && S.back() != w) {
					res.back().PB(S.back());
					vis[S.back()] = 1;
					S.pop_back();
				}
				res.back().PB(w);
			} else {
				vis[w] = 1;
			}
		}
	}

	printf("%d\n", SIZE(res));
	REP(i,SIZE(res)) {
		printf("%d ", SIZE(res[i])-1);
		FOREACH(it,res[i]) printf("%d ", *it);
		NL;
	}

	return 0;
}
