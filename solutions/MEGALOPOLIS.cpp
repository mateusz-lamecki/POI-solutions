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
const int MAXN = 250005;
const int MAXS = 1<<18;
VI g[MAXN];
int e[MAXS*2];
int dis[MAXN];
int pre[MAXN];
int prer[MAXN];
int siz[MAXN];
bool vis[MAXN];
int n, m;

void update(int x, int v) {
	x += MAXS;
	while(x > 0) {
		e[x] += v;
		x /= 2;
	}
}

int sum(int a, int b) {
	a += MAXS;
	b += MAXS;
	int res = 0;
	while(a < b) {
		if(a&1) res += e[a++];
		if(!(b&1)) res += e[b--];
		a /= 2;
		b /= 2;
	}
	if(a == b) res += e[a];
	return res;
}

void update(int a, int b, int k) {
	update(a,k);
	update(b+1,-k);
}

int query(int x) {
	return sum(0,x);
}

int k;
void dfs(int u) {
	vis[u] = 1;
	++k;
	pre[u] = k;
	prer[k] = u;
	siz[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		dis[*it] = dis[u] + 1;
		dfs(*it);
		siz[u] += siz[*it];
	}
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

	FOR(i,1,n) update(pre[i],pre[i],dis[i]);

	scanf("%d", &m);
	REP(i,n+m-1) {
		char s[5];
		scanf("%s", s);
		if(s[0] == 'W') {
			int x;
			scanf("%d", &x);
			printf("%d\n", query(pre[x]));
		} else {
			int a, b;
			scanf("%d %d", &a, &b);
			if(dis[a] > dis[b]) swap(a,b); // 1-...-a-b
			update(pre[b], pre[b]+siz[b]-1, -1);
		}
		
	}

	return 0;
}
