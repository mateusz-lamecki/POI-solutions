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
const int MAXN = 1000005;
VI g[MAXN];
bool vis[MAXN];
int t[MAXN];
int k[MAXN];
int c[MAXN];
int n;

void dfs(int u) {
	vis[u] = 1;

	int p = 0;
	FOREACH(it,g[u]) if(!vis[*it]) p++;
	if(p == 0) {
		t[u] = c[u];
		return;
	}

	vector<PII> G;

	FOREACH(it,g[u]) if(!vis[*it]) {
		dfs(*it);
		k[u] += k[*it] + 2;
		G.PB(MP(*it,*it));
	}

	FOREACH(it,G) it->ST = t[it->ND] - k[it->ND];
	sort(ALL(G));
	reverse(ALL(G));

	printf("u = %d\n", u);
	FOREACH(it,G) printf(" %d %d\n", t[it->ND], k[it->ND]);

	VI X;
	/*X.PB(1);
	FOR(i,1,SIZE(G)-1) X.PB(X.back() + 1+k[G[i].ND]+1);*/

	REP(i,SIZE(G)) {
		X.PB(0);
		REP(j,i-1) X.back() += 1 + k[i] + 1;
		X.back()++;
	}

	FOREACH(it,G) printf("%d ", it->ND);
	NL;

	FOREACH(it,X) printf("%d ", *it);
	NL;

	REP(i,SIZE(G)) {
		int y = G[i].ND;
		t[u] = max(t[u], X[y] + t[y]);
	}

	NL;


}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &c[i]);
	REP(i,n-1) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}

	dfs(1);

	FOR(i,1,n) printf("%d ", t[i]); NL;
	FOR(i,1,n) printf("%d ", k[i]); NL;

	printf("%d\n", max(t[1], k[1]+c[1]));

	return 0;
}
