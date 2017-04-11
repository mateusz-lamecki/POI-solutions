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

struct SegmentTree {
	LL *el, *lz, s;
	SegmentTree(int size) {
		s = 1<<size;
		el = new LL[2*s];
		lz = new LL[2*s];
		REP(i,2*s) el[i] = lz[i] = 0;
	}
	~SegmentTree() {
		delete[] el;
		delete[] lz;
	}
	void insert(int i, int j, int v) {
		insert2(i,j,v,1,0,s-1);
	}
	void insert2(int i, int j, int v, int node, int a, int b) {
		if(lz[node] != 0) {
			el[node] += lz[node];
			if(a != b) {
				lz[node*2] += lz[node];
				lz[node*2+1] += lz[node];
			}
			lz[node] = 0;
		}
		if(a>b || a>j || b<i) return;
		if(a>=i && b<=j) {
			el[node] += v;
			if(a != b) {
				lz[node*2] += v;
				lz[node*2+1] += v;
			}
			return;
		}
		insert2(i,j,v,node*2,a,(a+b)/2);
		insert2(i,j,v,node*2+1,(a+b)/2+1,b);
		el[node] = max(el[node*2], el[node*2+1]);
	}
	int query(int i, int j) {
		return query2(i,j,1,0,s-1);
	}
	int query2(int i, int j, int node, int a, int b) {
		if(a>b || a>j || b<i) return 0;
		if(lz[node] != 0) {
			el[node] += lz[node];
			if(a != b) {
				lz[node*2] += lz[node];
				lz[node*2+1] += lz[node];
			}
			lz[node] = 0;
		}
		if(a>=i && b<=j) return el[node];
		LL q1 = query2(i,j,node*2,a,(a+b)/2);
		LL q2 = query2(i,j,node*2+1,(a+b)/2+1,b);
		return max(q1,q2);
	}
} tree(16);

int main() {
	int n, m, z;
	scanf("%d %d %d", &n, &m, &z);
	REP(i,z) {
		int p, k, l;
		scanf("%d %d %d", &p, &k, &l);
		--k;
		if(tree.query(p,k)+l <= m) {
			tree.insert(p,k,l);
			printf("T\n");
		} else {
			printf("N\n");
		}
	}

	return 0;
}
