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
const int MAXN = 1000005;
int c[MAXN];
int x[MAXN];
int y[MAXN];
int nxt[MAXN];
int pos[MAXN];
int p[MAXN];
int q[MAXN];
int n, k;
int m, l;
int a, b;
int r;

int main() {
	scanf("%d %d", &n, &k);
	FOR(i,1,n) scanf("%d", &c[i]);

	scanf("%d %d", &m, &l);
	FOR(i,1,m) scanf("%d", &x[i]);
	FOR(i,1,l) scanf("%d", &y[i]);

	a = x[1];
	b = y[1];
	r = x[m]; // = y[l]

	// CASE 1:
	FORD(i,m-1,1) nxt[x[i]] = x[i+1];
	FORD(i,n,1) {
		int t = c[i];
		pos[t] = i;
		if(t == x[m]) p[i] = i;
		else p[i] = p[pos[nxt[t]]];
	}

	FOR(i,1,n) nxt[i] = pos[i] = 0;

	// CASE 2:
	FORD(i,l-1,1) nxt[y[i]] = y[i+1];
	FOR(i,1,n) {
		int t = c[i];
		pos[t] = i;
		if(t == y[l]) q[i] = i;
		else q[i] = q[pos[nxt[t]]];
	}

	// x[i] = position of last c[i]
	FOR(i,1,k) x[i] = 0;
	FOR(i,1,n) x[c[i]] = i;

	FOR(i,1,n) if(x[c[i]]) {
		int t = c[i];
		int u1 = i;
		int u2 = x[t];

		printf("%d: %d..%d\n", t, u1, u2);

		x[t] = 0;
	}

	FOR(i,1,n) printf("%d ", (c[i]==a)?p[i]:0); NL;
	FOR(i,1,n) printf("%d ", (c[i]==b)?q[i]:0); NL;

	return 0;
}
