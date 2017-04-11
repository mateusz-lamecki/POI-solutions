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
const int MAXN = 2005;
const int MAXM = 1000005;
int dp[MAXN][MAXN];
int a[MAXN];
int b[MAXN];
set<int> S1[MAXM];
set<int> S2[MAXM];

int largest_nogreater(set<int> &S, int x) {
	auto it = S.upper_bound(x);
	if(it == S.begin()) return 0;
	--it;
	if(it == S.begin()) return 0;
	--it;
	return *it;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	FOR(i,1,n) scanf("%d", &a[i]);
	FOR(i,1,m) scanf("%d", &b[i]);

	FOR(i,1,n) S1[a[i]].insert(i);
	FOR(i,1,m) S2[b[i]].insert(i);

	FOR(i,1,n) {
		FOR(j,1,m) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

			// rozważam poszerzenie o a[i];
			int l1 = largest_nogreater(S1[a[i]], i);
			int l2 = largest_nogreater(S2[a[i]], j);
			if(l1 && l2) dp[i][j] = max(dp[i][j], dp[l1-1][l2-1]+1);

			// rozważam poszerzenie o b[j];
			l1 = largest_nogreater(S1[b[j]], i);
			l2 = largest_nogreater(S2[b[j]], j);
			if(l1 && l2) dp[i][j] = max(dp[i][j], dp[l1-1][l2-1]+1);
		}
	}

	printf("%d\n", dp[n][m]*2);

	return 0;
}
