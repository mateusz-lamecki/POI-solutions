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
int x[MAXN], y[MAXN];
int c[MAXN];
int last[MAXN];
int pos[MAXN];
int dp1[MAXN];
int dp2[MAXN];
int d[MAXN];
int e[MAXN];
int m, l;
int n, k;

int main() {
	scanf("%d %d", &n, &k);
	FOR(i,1,n) scanf("%d", &c[i]);

	int t = max(n,k);

	scanf("%d %d", &m, &l);
	FOR(i,1,m) scanf("%d", &x[i]);
	FOR(i,1,l) scanf("%d", &y[i]);

	FOR(i,1,m) pos[x[i]] = i;
	FORD(i,n,1) {
		last[c[i]] = i;
		int r = pos[c[i]];
		if(r == 0) continue;
		if(r == m) dp1[i] = i;
		else {
			int col = x[r+1];
			dp1[i] = dp1[last[col]];
		}
	}

	FOR(i,1,t) last[i] = pos[i] = 0;

	FOR(i,1,l) pos[y[i]] = i;
	FOR(i,1,n) {
		last[c[i]] = i;
		int r = pos[c[i]];
		if(r == 0) continue;
		if(r == l) dp2[i] = i;
		else {
			int col = y[r+1];
			dp2[i] = dp2[last[col]];
		}
	}

	FOR(i,1,n) if(c[i] != x[1]) dp1[i] = 0;
	FOR(i,1,n) if(c[i] != y[1]) dp2[i] = 0;

	int w = 0;
	FORD(i,n,1) {
		d[c[i]] = w;
		if(c[i] == x[1]) w = dp1[i];
	}
	w = 0;
	FOR(i,1,n) {
		e[c[i]] = w;
		if(c[i] == y[1]) w = dp2[i];
	}

	FOR(i,1,t) last[i] = 0;
	FOR(i,1,n) {
		if(d[i] != 0 && e[i] != 0 && d[i] <= e[i]) {
			last[d[i]]++;
			last[e[i]+1]--;
		}
	}

	VI res;
	int s = 0;

	FOR(i,1,n) {
		s += last[i];
		if(s > 0 && c[i] == x[m]) res.PB(i);
		//printf("na pozycji %d: %d przedziałów\n", i, s);
	}

	printf("%d\n", SIZE(res));
	REP(i,SIZE(res)) printf("%d ", res[i]);
	NL;

	//FOR(i,1,k) printf("%d ", d[i]); NL;
	//FOR(i,1,k) printf("%d ", e[i]); NL;
	//FOR(i,1,n) printf("%d ", dp1[i]); NL;
	//FOR(i,1,n) printf("%d ", dp2[i]); NL;
	

	return 0;
}
