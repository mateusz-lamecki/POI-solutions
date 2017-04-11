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
#include <unordered_set>
#include <unordered_map>
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

const int INF = 2147;//483640;
const int MAXN = 1000005;
LL dp[MAXN][3];
int x[MAXN];
int n;

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &x[i]);

	FOR(i,1,n) REP(j,3) dp[i][j] = INF;
	dp[1][x[1]+1] = 0;

	FOR(i,1,n-1) {
		dp[i+1][x[i+1]+1] = 0;
		if(x[i] == -1) {
			dp[i+1][0] = min(dp[i+1][0], min(dp[i][1]+1, dp[i][2]+2));
			dp[i+1][1] = min(dp[i+1][1], dp[i][2]+1);
		}
		if(x[i] == 0) {
			REP(j,3) dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
			dp[i+1][0] = min(dp[i+1][0], min(dp[i][1]+1, dp[i][2]+2));
			dp[i+1][2] = min(dp[i+1][2], min(dp[i][1]+1, dp[i][0]+2));
		}
		if(x[i] == 1) {
			dp[i+1][1] = min(dp[i+1][1], dp[i][0]+1);
			dp[i+1][2] = min(dp[i+1][2], min(dp[i][0]+2, dp[i][1]+1));
		}
	}

	REP(i,3) {
		FOR(j,1,n) printf("%lld\t", dp[j][i]);
		NL;
	}

	return 0;
}
