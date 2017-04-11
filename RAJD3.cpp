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
const int MAXN = 1000005;
multiset<int> dis[MAXN];
set<int> g[MAXN];
int in[MAXN];
bool vis[MAXN];
VI order;
int n, m;

void dfs(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) dfs(*it);
	order.PB(u);
}

void delete_path(multimap<int,int> &M, VI& P, int x) {
	PII u(-1,0);
	//FOREACH(it,g[x]) if(dis[*it] > u.ST) u = MP(dis[*it], *it);
	printf("Odwiedzam %d, (%d,%d)\n", x, u.ST, u.ND);
	P.PB(x);
	if(u.ND != 0) {
		g[x].erase(g[x].find(u.ND));
		in[u.ND]--;
		//if(in[u.ND] == 0) M.insert(MP(dis[u.ND], u.ND));
		printf("Usuwam (%d,%d)\n", x, u.ND);
		delete_path(M, P, u.ND);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].insert(b);
		in[b]++;
	}

	FOR(i,1,n) if(!vis[i] && in[i]==0) dfs(i);
	FOREACH(it,order) FOREACH(itt,g[*it]) dis[*it].insert( dis[*itt].empty() ? 1 : (*(--dis[*itt].end())+1));

	FOR(i,1,n) vis[i] = 0;

	multimap<int,int> M;
	//FOR(i,1,n) for(int x: dis[i]) M.insert(MP(dis[i],i));

	while(!M.empty()) {
		PII u = *(--M.end());
		M.erase(--M.end());

		VI path;
		delete_path(M, path, u.ND);

		for(int x: path) printf("%d ", x);
		NL;
	}

	FOR(i,1,n) {
		printf("%d: ", i);
		for(int x: dis[i]) printf("%d ", x);
		NL;
	}

	return 0;
}
