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
#include <unordered_set>
#include <unordered_map>
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
VI g[MAXN];
VI gw[MAXN];
VI scc[MAXN];
bool vis[MAXN];
int p[MAXN];
PII longest[MAXN];
VI paths[MAXN];
VI order;
int n, m;

void dfs(int u, int c) {
	vis[u] = 1;
	scc[c].PB(u);
	FOREACH(it,g[u]) if(!vis[*it]) dfs(*it,c);
	order.PB(u);
}

void generate_path(int u, VI& A) {
	A.PB(u);
	while(longest[u].ST) {
		u = longest[u].ND;
		A.PB(u);
	}
}

PII find_max(int x) {
	PII mx(SIZE(paths[x])-2,1);
	int p = 0;
	FOREACH(it,paths[x]) {
		printf(" *it = %d\n", *it);

		bool found = 0;

		// jeśli usunę syna *it
		FOREACH(itt,g[*it]) if(*itt != longest[*it].ND) {
			int len2 = p + longest[*itt].ST + 1;
			if(len2 > mx.ST) mx = MP(len2, *it);
			found = 1;
		}

		if(!found) {
			printf("Brak w %d!, %d lub %d\n", *it, max(0,p-1), max(0,longest[*it].ST-1));
			int d = min(max(0,p-1), max(0,longest[*it].ST-1));
			if(d > mx.ST) mx = MP(d, *it);
		}

		p++;
	}
	return mx;
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		gw[b].PB(a);
		p[b]++;
	}

	int k = 0;
	FOR(i,1,n) if(!vis[i] && p[i]==0) dfs(i,++k);

	FOREACH(it,order) {
		FOREACH(itt,g[*it]) if(longest[*itt].ST+1 >= longest[*it].ST) {
			longest[*it] = MP(longest[*itt].ST+1, *itt);
		}
	}

	FOR(i,1,k) {
		PII mx(0,0);
		FOREACH(it,scc[i]) if(longest[*it].ST >= mx.ST) {
			mx.ST = longest[*it].ST;
			mx.ND = *it;
		}
		generate_path(mx.ND, paths[i]);
	}
	FOR(i,1,n) vis[i] = 0;
	
	PII res(0,INT_MAX);
	multiset<int> S;
	FOR(i,1,k) S.insert(SIZE(paths[i]));

	FOR(i,1,k) {
		S.erase(S.find(SIZE(paths[i])));

		printf("Symuluję usunięcie wierzchołka w scc = %d\n", i);

		int mx = (!S.empty()) ? *(--S.end()) : 0;
		PII r = find_max(paths[i].front()); // (len, id)

		printf(" nie usuwając max = %d\n", mx);
		printf(" usuwając max = %d (%d)\n", r.ST, r.ND);

		if(r.ST < mx) r = MP(mx, r.ND);
		if(r.ST < res.ND) res = MP(r.ND, r.ST);

		S.insert(SIZE(paths[i]));
	}

	FOR(i,1,n) {
		printf("%d: (%d,%d)\n", i, longest[i].ST, longest[i].ND);
	}
	
	FOR(i,1,k) {
		printf("%d: ", i);
		for(int x: paths[i]) printf("%d ", x);
		NL;
	}

	printf("%d %d\n", res.ST, res.ND);

	return 0;
}
