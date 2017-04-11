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

const bool DEBUG = 0;

struct MaxTree {
	int *tr, *lz, s;
	MaxTree(int size) {
		s = (1 << size);
		tr = new int[2*s];
		lz = new int[2*s];
		REP(i,2*s) tr[i] = lz[i] = 0;
	}
	~MaxTree() {
		delete[] tr;
		delete[] lz;
	}
	void update(int i, int j, int v) {
		if(i > j) return;
		update2(i,j,v,1,0,s-1);
	}
	void update2(int i, int j, int v, int node, int a, int b) {
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
		update2(i,j,v,node*2,a,(a+b)/2);
		update2(i,j,v,node*2+1,(a+b)/2+1,b);
		tr[node] = max(tr[node*2], tr[node*2+1]);
	}
	int query(int i, int j) {
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
		if(a>=i && b<=j) {
			return tr[node];
		}
		int q1 = query2(i,j,node*2,a,(a+b)/2);
		int q2 = query2(i,j,node*2+1,(a+b)/2+1,b);
		return max(q1,q2);
	}
};

struct MaxTree2 {
	int *e, s;
	MaxTree2(int size) {
		s = 1 << size;
		e = new int[2*s];
		REP(i,2*s) e[i] = 0;
	}
	~MaxTree2() {
		delete[] e;
	}
	void insert(int u, int v) {
		u += s;
		e[u] = v;
		u /= 2;
		while(u > 0) {
			e[u] = max(e[2*u], e[2*u+1]);
			u /= 2;
		}
	}
	int query(int a, int b) {
		int res = 0;
		a += s;
		b += s;
		while(a < b) {
			if(a&1) res = max(res, e[a++]);
			if(!(b&1)) res = max(res, e[b--]);
			a /= 2;
			b /= 2;
		}
		if(a == b) res = max(res, e[a]);
		return res;
	}
	int query(int x) {
		return e[x+s];
	}
};

const int INF = 2147483640;
const int MAXN = 500005;
const int MAXM = 1000005;
VI g[MAXN];
VI gw[MAXN];
bool vis[MAXN];
int t[MAXN];
int r[MAXN];
PII in[MAXM];
int l_start[MAXN];
int l_end[MAXN];
int first[MAXN];
int last[MAXN];
int id[MAXN];
PII res[MAXN];
int deg[MAXN];
VI order;
VI vert;
int n, m;

void mark(int u, int p) {
	vis[u] = 1;
	first[p] = min(first[p], u);
	last[p] = max(last[p], u);
	id[u] = p;
	vert.PB(u);
	FOREACH(it,g[u]) if(!vis[*it]) mark(*it,p);
	FOREACH(it,gw[u]) if(!vis[*it]) mark(*it,p);
}

void scan(int &x) {
#define gc getchar_unlocked
	char c = gc();
	x = 0;
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = x*10 + c - '0';
		c = gc();
	}
}

int main() {
	scan(n);
	scan(m);
	REP(i,m) {
		int a, b;
		scan(a);
		scan(b);
		g[a].PB(b);
		in[i] = MP(a,b);
		deg[b]++;
	}

	priority_queue<int> S;
	FOR(i,1,n) if(deg[i] == 0) S.push(-i);

	while(!S.empty()) {
		int u = -S.top();
		S.pop();
		order.PB(u);
		while(!g[u].empty()) {
			int v = g[u].back();
			g[u].pop_back();
			deg[v]--;
			if(deg[v] == 0) S.push(-v);
		}
	}

	REP(i,SIZE(order)) {
		t[i] = order[i];
		r[order[i]] = i;
	}

	FOR(i,1,n) g[i].clear();
	REP(i,m) {
		int a = in[i].ST;
		int b = in[i].ND;
		a = r[a];
		b = r[b];
		g[a].PB(b);
		gw[b].PB(a);
	}

	REP(i,n) vis[i] = 0;
	int k = 0;
	REP(i,n) if(!vis[i]) {
		vert.clear();
		first[k] = last[k] = i;
		mark(i,k);
		++k;
	}

	MaxTree2 pref_end(19), suf_start(19);

	FORD(i,n-1,0) FOREACH(it,g[i]) l_start[i] = max(l_start[i], l_start[*it]+1);
	REP(i,n) FOREACH(it,gw[i]) l_end[i] = max(l_end[i], l_end[*it]+1);

	FORD(i,n-1,0) suf_start.insert(i,l_start[i]);
	FOR(i,0,n-1) pref_end.insert(i,l_end[i]);

	MaxTree tree(19);
	REP(i,n) FOREACH(it,g[i]) {
		int l = l_end[i] + l_start[*it] + 1;
		tree.update(i+1,*it-1,l);
	}

	REP(i,n) res[i].ST = INT_MAX;

	REP(i,n) {
		int idd = id[i];
		if(first[idd] == last[idd]) continue;
		int first_scc = first[idd];
		int last_scc = last[idd];
		int q1 = pref_end.query(first_scc,i-1);
		int q2 = suf_start.query(i+1,last_scc);
		int q3 = tree.query(i,i);
		int r = max(max(q1,q2), q3);

		if(r <= res[idd].ST) res[idd] = MP(r, i);
	}

	PII answer(0,1);
	multiset<int> longest;
	REP(i,k) longest.insert(l_start[first[i]]);
	int d = 0;

	REP(i,k) {
		if(first[i] == last[i]) continue;
		if(res[i].ST >= answer.ST) {
			answer = MP(res[i].ST, t[res[i].ND]);
			d = i;
		}
	}

	multiset<int>::iterator it = longest.find(l_start[first[d]]);
	assert(it != longest.end());
	longest.erase(longest.find(l_start[first[d]]));

	int pp = 0;
	if(!longest.empty()) pp = *(--longest.end());
	answer.ST = max(answer.ST,  pp);

	printf("%d %d\n", answer.ND, answer.ST);

	return 0;
}
