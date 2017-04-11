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
const int MAXN = (1 << 20);
const PII INVALID = MP(INF,INF);
PII a[2*MAXN];
PII b[2*MAXN];
int n, m;

bool is_power(int x) {
	return x == (x & -x);
}

void mark(int x) {
	x /= 2;
	if(a[x*2+1].ST == 0 && a[x*2+1].ND == 0) {
		a[x] = a[x*2];
		b[x] = b[x*2];
		return;
	}
	if(a[x*2].ND <= a[x*2+1].ST && a[x*2+1].ST != INF) a[x] = MP(a[x*2].ST, a[x*2+1].ND);
	else if(a[x*2].ND <= b[x*2+1].ST && b[x*2+1].ST != INF) a[x] = MP(a[x*2].ST, b[x*2+1].ND);
	else a[x] = INVALID;

	if(b[x*2].ND <= a[x*2+1].ST && a[x*2+1].ST != INF) b[x] = MP(b[x*2].ST, a[x*2+1].ND);
	else if(b[x*2].ND <= b[x*2+1].ST && b[x*2+1].ST != INF) b[x] = MP(b[x*2].ST, b[x*2+1].ND);
	else b[x] = INVALID;

	if(a[x].ST > b[x].ST)  swap(a[x], b[x]);
}

void update(int x) {
	while(x > 0) {
		mark(x);
		x /= 2;
	}
}

void print() {
	int r = MAXN;
	while(r > 0) {
		printf("(%d,%d):(%d,%d) ", a[r].ST, a[r].ND, b[r].ST, b[r].ND);
		r++;
		if(is_power(r)) {
			r /= 4;
			NL;
		}
	}
}

int main() {
	scanf("%d", &n);
	REP(i,MAXN) a[i] = b[i] = INVALID;
	REP(i,n) {
		int u, v;
		scanf("%d %d", &u, &v);
		if(u > v) swap(u,v);
		a[i+MAXN] = MP(u,u);
		b[i+MAXN] = MP(v,v);
	}

	int r = MAXN;
	while(r > 0) {
		if(r != 1) mark(r);
		r++;
		if(is_power(r)) r /= 4;
	}

	scanf("%d", &m);
	REP(i,m) {
		int u, v;
		scanf("%d %d", &u, &v);
		u += MAXN-1;
		v += MAXN-1;
		swap(a[u], a[v]);
		swap(b[u], b[v]);
		update(u);
		update(v);
		printf("%s\n", (a[1]!=INVALID || b[1]!=INVALID) ? "TAK" : "NIE");
	}
	return 0;
}
