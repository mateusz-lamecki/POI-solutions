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
const int MAXN = 30005;

struct KthTree {
	int *e, s;
	KthTree(int size) {
		s = 1<<size;
		e = new int[2*s];
		REP(i,2*s) e[i] = 0;
	}
	~KthTree() {
		delete[] e;
	}
	void insert(int x, int v=1) {
		x += s;
		while(x > 0) {
			e[x] += v;
			x /= 2;
		}
	}
	int kth(int x, int node=1) {
		if(node >= s) return node-s;
		if(x <= e[node*2]) return kth(x,node*2);
		else return kth(x-e[node*2],node*2+1);
	}
} tree(15);
int a[MAXN];
int b[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &b[i]);

	FOR(i,1,n) tree.insert(i);

	bool res = 1;

	FORD(i,n,1) {
		int t = i-b[i];
		int u = tree.kth(t);
		if(u == 0) res = 0;
		a[i] = u;
		tree.insert(u,-1);
	}

	if(res) FOR(i,1,n) printf("%d\n", a[i]);
	else printf("NIE\n");

	return 0;
}

