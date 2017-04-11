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
const int MAXN = 1000005;
vector<PII> r;
int d[MAXN];
int n;

int upper_bound(int x, int p) {
	int lo = 0, hi = p;
	int ret = INF;
	while(lo <= hi) {
		int mid = lo + (hi-lo) / 2;
		if(r[mid].ND <= x) {
			ret = mid;
			lo = mid + 1;
		} else hi = mid - 1;

	}
	return ret;
}

int main() {
	scanf("%d", &n);
	REP(i,n) {
		int a, b;
		scanf("%d%d", &a, &b);
		r.PB(MP(b,a));
	}

	sort(ALL(r));
	REP(i,n) swap(r[i].ST, r[i].ND);

	d[0] = r[0].ND - r[0].ST;
	FOR(i,1,n-1) {
		int u = upper_bound(r[i].ST, i-1);
		if(u == INF) d[i] = max(d[i-1], r[i].ND - r[i].ST);
		else d[i] = max(d[i-1], d[u] + r[i].ND - r[i].ST);
	}
	
	printf("%d\n", d[n-1]);

	return 0;
}
