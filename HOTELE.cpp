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
const bool DEBUG = false;
const int MAXN = 5005;
VI g[MAXN];
VI d[MAXN];
bool vis[MAXN];
int dis;
int n;

void dfs(int u, int x) {
	vis[u] = true;
	d[++dis].PB(x);
	REP(i,SIZE(g[u])) if(!vis[g[u][i]]) {
		dfs(g[u][i], x);
	}
	--dis;
}

LL calc(int u) {
	vis[u] = true;
	int id = 0;
	REP(i,SIZE(g[u])) {
		dis = 0;
		dfs(g[u][i], id++);
	}
	LL res = 0;
	REP(i,n+1) {
		VI w;
		int prev = -1;
		REP(j,SIZE(d[i])) {
			if(d[i][j] != prev) {
				w.PB(1);
				prev = d[i][j];
			} else w[SIZE(w)-1]++;
		}
		LL s1 = 0, s2 = 0, s3 = 0;
		REP(i,SIZE(w)) {
			s1 += LL(w[i]);
			s2 += LL(w[i]) * LL(w[i]);
			s3 += LL(w[i]) * LL(w[i]) * LL(w[i]);
		}
		res += ((s1*s1*s1) - 3*s1*s2 + 2*s3) / 6ll;
	}
	return res;
}

int main() {
	scanf("%d", &n);
	REP(i,n-1) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a; --b;
		g[a].PB(b);
		g[b].PB(a);
	}

	LL res = 0;
	REP(i,n) {
		REP(j,n) {
			vis[j] = 0;
			d[j].clear();
		}
		res += calc(i);
	}

	printf("%lld\n", res);

	return 0;
}
