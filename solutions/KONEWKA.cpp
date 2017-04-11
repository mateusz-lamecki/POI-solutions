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
typedef long long LL;
typedef pair<LL,LL> PII;
typedef vector<int> VI;

PII max(PII a, PII b) {
	if(a.ST >= b.ST) return a;
	else return b;
}

struct MaxTree {
	vector<PII> tr;
	VI lz;
	int s;
	MaxTree(int size) {
		s = (1 << size);
		tr.resize(2*s,MP(0,0));
		FOR(i,s,2*s-1) tr[i].ND = i-s;
		lz.resize(2*s,0);
	}
	void update(int i, int j, int v) {
		update2(i,j,v,1,0,s-1);
	}
	void update2(int i, int j, int v, int node, int a, int b) {
		if(lz[node] != 0) {
			tr[node].ST += lz[node];
			if(a != b) {
				lz[node*2] += lz[node];
				lz[node*2+1] += lz[node];
			}
			lz[node] = 0;
		}
		if(a>b || a>j || b<i) return;
		if(a >= i && b <= j) {
			tr[node].ST += v;
			if(a != b) {
				lz[node*2] += v;
				lz[node*2+1] += v;
			}
			return;
		}
		update2(i,j,v,node*2,a,(a+b)/2);
		update2(i,j,v,node*2+1,(a+b)/2+1,b);
		tr[node] = max(tr[node*2], tr[node*2+1]);
	}
	PII query(int i, int j) {
		return query2(i,j,1,0,s-1);
	}
	PII query2(int i, int j, int node, int a, int b) {
		if(a>b || a>j || b<i) return MP(-1,-1);
		if(lz[node] != 0) {
			tr[node].ST += lz[node];
			if(a != b) {
				lz[node*2] += lz[node];
				lz[node*2+1] += lz[node];
			}
			lz[node] = 0;
		}
		if(a >= i && b <= j) return tr[node];
		PII q1 = query2(i,j,node*2,a,(a+b)/2);
		PII q2 = query2(i,j,node*2+1,(a+b)/2+1,b);
		return max(q1,q2);
	}
};

struct SumTree {
	VI e;
	int s;
	SumTree(int size) {
		s = (1 << size);
		e.resize(2*s);
	}
	void insert(int x, int v=1) {
		x += s;
		while(x > 0) {
			e[x] += v;
			x /= 2;
		}
	}
	int query(int a, int b) {
		a += s;
		b += s;
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
};

const int INF = 1047483640;
const int MAXN = 1000005;
MaxTree tree(19);
SumTree tree2(19);
int n, k;

void update() {
	PII t(INT_MAX,INT_MAX);
	while(true) {
		t = tree.query(0,n-1);
		if(t.ST >= k) {
			tree.update(t.ND,t.ND,-INF);
			tree2.insert(t.ND);
			//printf("Ściągam dojrzałe %lld-te drzewo o wartości %lld\n", t.ND, t.ST);
		} else break;
	}
}

void inicjuj(int _n, int _k, int *D) {
	n = _n;
	k = _k;
	REP(i,n) tree.update(i,i,D[i]);

	update();
}

void podlej(int a, int b) {
	tree.update(a,b,1);
	update();
}

int dojrzale(int a, int b) {
	return tree2.query(a,b);
}

int main() { }
