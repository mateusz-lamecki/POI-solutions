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
const int MAXN = 105;
int a[MAXN][MAXN];
int n, m;

int main() {
	scanf("%d %d", &n, &m);
	FOR(i,1,n) FOR(j,1,m) scanf("%d", &a[i][j]);

	FOR(i,1,n) a[i][1] = a[i][m] = INF;
	FOR(i,1,m) a[1][i] = a[n][i] = INF;

	multimap<int,PII> M;
	FOR(i,2,n-1) FOR(j,2,m-1) M.insert(MP(a[i][j], MP(i,j)));

	int res = 0;

	while(!M.empty()) {
		pair<int,PII> u = *M.begin();
		M.erase(M.begin());

		int mn = INF;
		mn = min(mn, a[u.ND.ST-1][u.ND.ND]);
		mn = min(mn, a[u.ND.ST+1][u.ND.ND]);
		mn = min(mn, a[u.ND.ST][u.ND.ND-1]);
		mn = min(mn, a[u.ND.ST][u.ND.ND+1]);

		int p = a[u.ND.ST][u.ND.ND];
		if(mn != INF) res += mn-p;
		else res += p;

		a[u.ND.ST][u.ND.ND] = INF;

	}

	printf("%d\n", res);

	return 0;
}
