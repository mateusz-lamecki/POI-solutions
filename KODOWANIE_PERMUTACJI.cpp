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
const int MAXN = 30005;
int a[MAXN];

struct PosTree {
	int *el, s;
	PosTree(int size) {
		el = new int[1 << ((s=size)+1)];
		REP(i,1<<(s+1)) el[i] = 0;
	}
	~PosTree() {
		delete[] el;
	}
	void insert(int x, int v) {
		for(x = (1 << s) + x; x > 0; x = x >> 1) el[x] += v;
	}
	int query(int x) {
		int po = 1;
		REP(i,s) {
			po <<= 1;
			if(el[po] < x) x -= el[po++];
		}
		return po - (1 << s);
	}
};

int main() {
	int n;
	scanf("%d", &n);
	REP(i,n) scanf("%d", &a[i]);

	VI res;
	bool valid = true;

	PosTree tree(15);
	FOR(i,1,n) tree.insert(i,1);

	int m = n;
	FORD(i,n-1,0) {
		if(m <= a[i]) {
			valid = false;
			break;
		}
		int u = tree.query(m - a[i]);
		//printf(" u = %d\n", u);
		res.PB(u);
		tree.insert(u,-1);
		m--;
	}

	if(valid) FORD(i,n-1,0) printf("%d\n", res[i]);
	else printf("NIE\n");
	
	return 0;
}
