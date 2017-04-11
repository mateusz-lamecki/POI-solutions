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

const int INF = 21474;//8360;
const int MAXN = 1000005;
int x[MAXN];
int dp[MAXN][3];
int d[MAXN][3];
int n;

int main() {
	scanf("%d", &n);
	REP(i,n) scanf("%d", &x[i]);

	REP(i,n) REP(j,3) dp[i][j] = INF;
	REP(i,n) dp[i][x[i]+1] = 0;

	FOR(i,1,n-1) {
		if(x[i] == 1 && dp[i-1][0] != INF) {
			dp[i][1] = min(dp[i][1], 1);
			dp[i][0] = min(dp[i][0], 2);
		}
		if(x[i] == 0) {
			if(dp[i-1][2] != INF) dp[i][2] = min(dp[i][2], 1);
			if(dp[i-1][0] != INF) dp[i][0] = min(dp[i][0], 1);
		}
		if(x[i] == -1 && dp[i-1][2] != INF) {
			dp[i][2] = min(dp[i][2], 2);
			dp[i][1] = min(dp[i][1], 1);
		}
	}

	REP(i,n) REP(j,3) d[i][j] = INF;
	REP(i,3) d[n-1][i] = dp[n-1][i];

	FORD(i,n-2,0) FORD(j,2,0) {
		d[i][j] = min(d[i][j], d[i+1][j] + dp[i][j]);
		if(j<2) d[i][j] = min(d[i][j], d[i+1][j+1] + dp[i][j]);
		if(j<1) d[i][j] = min(d[i][j], d[i+1][j+2] + dp[i][j]);
	}

	FORD(j,2,0) {
		REP(i,n) printf("%d\t", dp[i][j]);
		NL;
	}

	NL;NL;

	FORD(j,2,0) {
		REP(i,n) printf("%d\t", d[i][j]);
		NL;
	}



	return 0;
}
