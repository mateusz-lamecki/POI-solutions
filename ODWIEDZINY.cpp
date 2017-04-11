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
const int MAXN = 50005;
const int MAXD = 200;
const int LOGN = 17;
VI g[MAXN];
int c[MAXN];
int t[MAXN];
int q[MAXN][MAXD];
bool vis[MAXN];
int siz[MAXN];
int pre[MAXN];
int dis[MAXN];
int k[MAXN];
int p[LOGN][MAXN];
int n;

int cnt;

void dfs(int u) {
	vis[u] = 1;
	siz[u] = 1;
	pre[u] = ++cnt;
	FOREACH(it,g[u]) if(!vis[*it]) {
		p[0][*it] = u;
		dis[*it] = dis[u] + 1;
		dfs(*it);
		siz[u] += siz[*it];
	}
}

void dfs2(int u) {
	vis[u] = 1;
	int d = u, j = 1;
	FOR(i,1,MAXD-1) {
		d = p[0][d];
		q[u][i] = c[u] + q[d][i];
		j++;
	}
	FOREACH(it,g[u]) if(!vis[*it]) dfs2(*it);
}

void calc_lca() {
	p[0][1] = 1;
	FOR(i,1,LOGN-1) FOR(j,1,n) p[i][j] = p[i-1][p[i-1][j]];
}

bool ancestor(int u, int v) {
	return pre[u] >= pre[v] && pre[u] < pre[v]+siz[v];
}

int lca(int u, int v) {
	if(ancestor(u,v)) return v;
	if(ancestor(v,u)) return u;
	int i = u, j = LOGN-1;
	while(j >= 0) {
		if(ancestor(v,p[j][i])) j--;
		else i = p[j][i];
	}
	return p[0][i];
}

int kth_ancestor(int u, int k) {
	FORD(i,LOGN-1,0) {
		int y = (1 << i);
		if(k - y >= 0) {
			u = p[i][u];
			k -= y;
		}
	}
	return u;
}

void scan(int &x) {
	scanf("%d", &x);
	return;
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = 10*x + c - '0';
		c = gc();
	}
}


int query(int a, int b, int k) {
	int lc = lca(a,b);

	if(k < MAXD) {
		int lt_c = dis[a]-dis[lc];
		lt_c -= (lt_c%k);
		int rt_c = dis[b]-dis[lc];
		rt_c -= (rt_c%k);

		int lt = kth_ancestor(a,lt_c);
		int rt = kth_ancestor(b,rt_c);

		int ret = q[a][k]-q[lt][k]+c[lt] + q[b][k]-q[rt][k]+c[rt];
		if(lt == rt) ret -= c[lt];
		return ret;
	} else {
		int res = 0;
		while(dis[a] >= dis[lc]) {
			res += c[a];
			if(dis[a] < k) break;
			a = kth_ancestor(a,k);
		}
		while(dis[b] > dis[lc]) {
			res += c[b];
			if(dis[b] < k) break;
			b = kth_ancestor(b,k);
		}
		return res;
	}
	return 0;
}

int main() {
	scan(n); //scanf("%d", &n);
	FOR(i,1,n) scan(c[i]); //scanf("%d", &c[i]);
	REP(i,n-1) {
		int a, b;
		scan(a);
		scan(b);
		//scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}
	FOR(i,1,n) scan(t[i]); //scanf("%d", &t[i]);
	FOR(i,1,n-1) scan(k[i]); //scanf("%d", &k[i]);

	dfs(1);
	FOR(i,1,n) vis[i] = 0;
	dfs2(1);

	calc_lca();

	FOR(i,1,n-1) {
		int res = query(t[i], t[i+1], k[i]);
		printf("%d\n", res);
		//printf("%d..%d co %d: %d\n", t[i], t[i+1], k[i], res);
	}

	return 0;
}
