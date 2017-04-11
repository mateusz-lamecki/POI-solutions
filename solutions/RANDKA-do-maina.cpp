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

const int INF = 214748360;
const int MAXN = 500005;
const int LOGN = 20;
VI gw[MAXN];
VI g[MAXN];
int p[LOGN][MAXN];
int size[MAXN];
int pre[MAXN];
bool vis[MAXN];
bool cycle[MAXN];
int e[MAXN];
int in[MAXN];
int lead[MAXN];
VI trees[MAXN];
int comp[MAXN];
int dcycl[MAXN];
int scycl[MAXN];
int level[MAXN];
int leadc[MAXN];
int n, k;
int id;

void clear() {
	FOR(i,1,n) vis[i] = 0;
}

void find_cycle(int u) {
	while(!vis[u]) {
		vis[u] = 1;
		u = e[u];
	}
	int p = e[u];
	if(cycle[p]) return;
	int dis = dcycl[u] = 1;
	int s = 1;
	while(p != u) {
		cycle[p] = 1;
		dcycl[p] = ++dis;
		s++;
		p = e[p];
	}
	cycle[u] = 1;
	p = e[u];
	while(p != u) {
		scycl[p] = s;
		p = e[p];
	}
	scycl[p] = s;
}

void mark_tree(int u, int leader, int c) {
	vis[u] = 1;
	lead[u] = leader;
	trees[c].PB(u);
	FOREACH(it,gw[u]) {
		int x = *it;
		if(!vis[x] && x != e[leader] && !cycle[x]) {
			mark_tree(x,leader,c);
		}
	}
}

void dfs(int u) {
	vis[u] = 1;
	pre[u] = ++id;
	FOREACH(it,gw[u]) {
		int x = *it;
		if(!vis[x] && !cycle[x]) {
			p[0][x] = u;
			level[x] = level[u] + 1;
			dfs(x);
			size[u] += size[x] + 1;
		}
	};
}

void find_components(int u, int c) {
	vis[u] = 1;
	comp[u] = c;
	FOREACH(it,g[u]) {
		int x = *it;
		if(!vis[x]) find_components(x,c);
	}
}

bool ancestor(int u, int v) {
	return (pre[u] >= pre[v] && pre[u] < pre[v] + size[v]);
}

int lca(int u, int v) {
	if(ancestor(u,v)) return v;
	if(ancestor(v,u)) return u;
	
	int i = u;
	int j = LOGN-1;
	while(j>=0) {
		if(ancestor(v,p[j][i])) j--;
		else i = p[j][i];
	}
	return p[0][i];
}

int get_distance(int u, int v) {
	int l1 = lead[u];
	int l2 = lead[v];
	if(dcycl[l2] < dcycl[l1]) return scycl[l1] - abs(dcycl[l2] - dcycl[l1]);
	else return dcycl[l2] - dcycl[l1];

}

PII dis_lca(int u, int v ) {
	int l = lca(u,v);
	return MP(level[u] - level[l], level[v] - level[l]);
}

PII dis_cycle(int u, int v) {
	PII r1, r2;

	// 1. variant: x goes to y
	r1.ST = level[u] + get_distance(u,v);
	r1.ND = level[v];

	// 2. variant: y goes to x
	r2.ST = level[u];
	r2.ND = level[v] + get_distance(v,u);

	if(max(r1.ST,r1.ND) != max(r2.ST,r2.ND)) {
		if(max(r1.ST,r1.ND) < max(r2.ST,r2.ND)) return r1;
		else return r2;
	}

	if(min(r1.ST,r1.ND) != min(r2.ST,r2.ND)) {
		if(min(r1.ST,r1.ND) < min(r2.ST,r2.ND)) return r1;
		else return r2;
	}

	if(r1.ND < r2.ND) return r1;
	return r2;
}

PII find_answer(int a, int b) {
	if(comp[a] != comp[b]) return MP(-1,-1);
	if(lead[a] == lead[b]) return dis_lca(a,b);
	return dis_cycle(a,b);
}


int main() {
	scanf("%d %d", &n, &k);
	FOR(i,1,n) {
		int b;
		scanf("%d", &b);
		e[i] = b;
		in[b]++;
		g[i].PB(b);
		g[b].PB(i);
		gw[b].PB(i);
	}

	id = 0;
	FOR(i,1,n) if(!vis[i]) {
		leadc[++id] = i;
		find_components(i,id);
	}

	clear();
	id = 0;

	FOR(i,1,n) if(leadc[i] != 0) {
		find_cycle(leadc[i]);
	} else break;


	clear();

	id = 0;
	FOR(i,1,n) if(cycle[i]) mark_tree(i,i,++id);


	id = 0;

	clear();
	FOR(i,1,n) gw[i].PB(e[i]);

	clear();
	id = 0;


	FOR(i,1,n) {
		if(!trees[i].empty()) {
			dfs(trees[i].front());
			p[0][trees[i].front()] = trees[i].front();
		}
		else break;
	}

	FOR(i,1,n) size[i]++;
	FOR(i,1,LOGN-1) FOR(j,1,n) p[i][j] = p[i-1][p[i-1][j]];


	REP(i,k) {
		int a, b;
		scanf("%d %d", &a, &b);
		PII res = find_answer(a,b);
		printf("%d %d\n", res.ST, res.ND);
	}


	return 0;
}
