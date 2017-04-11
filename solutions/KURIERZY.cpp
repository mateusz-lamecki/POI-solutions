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
const int MAXN = 500005;
int a[MAXN];
map<int,int> P[MAXN];
int cnt[MAXN];
int n, m;

struct Node {
	PII a, b;
	Node() { }
	Node(PII a, PII b) : a(a), b(b) { }
	inline Node operator +(Node rhs) {
		map<int,int> M;
		M[a.ST] += a.ND;
		M[b.ST] += b.ND;
		M[rhs.a.ST] += rhs.a.ND;
		M[rhs.b.ST] += rhs.b.ND;

		multimap<int,int> P;
		FOREACH(it,M) if(it->ST != 0) P.insert(MP(it->ND, it->ST));
		//for(PII x: M) if(x.ST != 0) P.insert(MP(x.ND,x.ST));

		PII u = MP(0,0);
		if(!P.empty()) u = *(--P.end());
		swap(u.ST, u.ND);

		PII v = MP(0,0);
		if(SIZE(P) > 1) v = *(--(--P.end()));
		swap(v.ST, v.ND);

		return Node(u,v);
	}
};

VI X;

struct Tree {
	vector<Node> e;
	int s;
	Tree(int size, VI& X) { 
		s = 1 << size;
		e.resize(2*s);
		build(X,1,0,s-1);
	}
	void build(VI &X, int node, int a, int b) {
		if(a > b) return;
		if(a == b) {
			if(a < SIZE(X)) e[node].a = MP(X[a],1);
			return;
		}
		if(a < b) {
			build(X,node*2,a,(a+b)/2);
			build(X,node*2+1,(a+b)/2+1,b);
			e[node] = e[node*2] + e[node*2+1];
		}
	}
	void find(int i, int j, int node, int a, int b) {
		if(a>b || a>j || b<i) return;
		if(a>=i && b<=j) {
			X.PB(node);
			return;
		}
		if(a < b) {
			find(i,j,node*2,a,(a+b)/2);
			find(i,j,node*2+1,(a+b)/2+1,b);
		}
	}
	int query(int a, int b) {
		X.clear();
		find(a,b,1,0,s-1);

		Node res = e[X[0]];
		FOR(i,1,SIZE(X)-1) res = res + e[X[i]];

		//printf("(%d,%d) (%d,%d)\n", res.a.ST, res.a.ND, res.b.ST, res.b.ND);

		int len = b-a+1;
		if(res.a.ND*2 > len) return res.a.ST;
		else return 0;
	}
};

void scan(int &x) {
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = 10*x + c - '0';
		c = gc();
	}
}

int main() {
	scan(n);
	scan(m);
	VI e(n);
	REP(i,n) {
		scan(e[i]);
		P[e[i]].insert(MP(i,++cnt[e[i]]));
	}

	Tree tree(19, e);
	
	REP(i,m) {
		int a, b;
		scan(a);
		scan(b);
		--a; --b;
		int res = tree.query(a,b);

		int found = 0;

		map<int,int>::iterator it1 = P[res].lower_bound(a);
		map<int,int>::iterator it2 = P[res].upper_bound(b);
		if(it1 != P[res].end() && it2 != P[res].begin()) {
			--it2;
			int d = it2->ND - it1->ND + 1;
			if(d*2 > b-a+1) found = 1;
		}

		printf("%d\n", res*found);
	}

	return 0;
}
