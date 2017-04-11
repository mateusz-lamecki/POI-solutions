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
const int MAXN = 5000005;

struct MaxTree {
	int *tr, *lz, s;
	MaxTree(int size) {
		s = 1<<size;
		tr = new int[2*s];
		lz = new int[2*s];
		REP(i,2*s) tr[i] = lz[i] = 0;
	}
	~MaxTree() {
		delete[] tr;
		delete[] lz;
	}
	void insert(int i, int j, int v) {
		if(i>j) return;
		insert2(i,j,v,1,0,s-1);
	}
	void insert2(int i, int j, int v, int node, int a, int b) {
		if(lz[node] != 0) {
			tr[node] = max(tr[node], lz[node]);
			if(a != b) {
				lz[node*2] = max(lz[node*2], lz[node]);
				lz[node*2+1] = max(lz[node*2+1], lz[node]);
			}
			lz[node] = 0;
		}
		if(a>b || a>j || b<i) return;
		if(a>=i && b<=j) {
			tr[node] = max(tr[node], v);
			if(a != b) {
				lz[node*2] = max(lz[node*2], v);
				lz[node*2+1] = max(lz[node*2+1], v);
			}
			return;
		}
		insert2(i,j,v,node*2,a,(a+b)/2);
		insert2(i,j,v,node*2+1,(a+b)/2+1,b);
		tr[node] = max(tr[node*2], tr[node*2+1]);
	}
	int query(int i, int j) {
		if(i>j) return 0;
		return query2(i,j,1,0,s-1);
	}
	int query2(int i, int j, int node, int a, int b) {
		if(a>b || a>j || b<i) return 0;
		if(lz[node] != 0) {
			tr[node] = max(tr[node], lz[node]);
			if(a != b) {
				lz[node*2] = max(lz[node*2], lz[node]);
				lz[node*2+1] = max(lz[node*2+1], lz[node]);
			}
			lz[node] = 0;
		}
		if(a>=i && b<=j) return tr[node];
		int q1 = query2(i,j,node*2,a,(a+b)/2);
		int q2 = query2(i,j,node*2+1,(a+b)/2+1,b);
		return max(q1,q2);
	}
};

VI g[MAXN];
VI gw[MAXN];
set<int> S[MAXN];
bool vis[MAXN];
int start[MAXN];
int end[MAXN];
int topo[MAXN];
PII res[MAXN];
int idsc[MAXN];
vector<VI > sc;
VI post;
int n, m;

void dfs(int u) {
	vis[u] = 1;
	sc.back().PB(u);
	idsc[u] = SIZE(sc);
	FOREACH(it,g[u]) if(!vis[*it]) dfs(*it);
	post.PB(u);
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		S[a].insert(b);
		gw[b].PB(a);
	}

	FOR(i,1,n) if(!vis[i]) {
		sc.PB(VI());
		dfs(i);
	}

	FOREACH(it,post) FOREACH(jt,g[*it]) start[*it] = max(start[*it], start[*jt]+1);
	reverse(ALL(post));
	FOREACH(it,post) FOREACH(jt,gw[*it]) end[*it] = max(end[*it], end[*jt]+1);

	REP(i,SIZE(post)) topo[post[i]] = i;

	MaxTree tree(19);

	FOR(i,1,n) FOREACH(it,g[i]) {
		int a = topo[i];
		int b = topo[*it];
		tree.insert(a+1,b-1,end[i]+start[*it]+1);
	}

	PII ans(0,0);

	FOREACH(it,sc) {
		PII r(0,INF);
		FOREACH(jt,*it) {
			int prev = (topo[*jt]>0 ? post[topo[*jt]-1] : 0);
			int nxt = (topo[*jt]<SIZE(post)-1 ? post[topo[*jt]+1] : 0);

			int p = 0, q = 0;

			if(idsc[prev] == idsc[*jt]) p = end[prev];
			if(idsc[*jt] == idsc[nxt]) q = start[nxt];

			int h = max(tree.query(topo[*jt],topo[*jt]), max(p,q));
			if(h < r.ND) r = MP(*jt,h);
		}
		if(r.ND >= ans.ND) ans = r;
	}

	printf("%d %d\n", ans.ST, ans.ND);

	return 0;
}
