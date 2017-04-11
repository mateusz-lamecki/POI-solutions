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

const int INF = 2147483640;
const int MOD = 7;//1000000007;
const int MAXM = 2005;
const int MAXN = 10;
char s[MAXN][MAXM];
int h[MAXN][MAXM];
int p[MAXM];
int n;

int get_hash(int i, int a, int b) {
	return h[i][b] - h[i][a-1]*p[b-a+1];
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%s", s[i]+1);

	p[0] = 1;
	FOR(i,1,MAXM-2) p[i] = p[i-1] * MOD;

	FOR(i,1,n) {
		int m = strlen(s[i]+1);
		h[i][1] = s[i][1];
		FOR(j,2,m) h[i][j] = h[i][j-1] * MOD + s[i][j];
		FOR(j,1,m) printf("%d ", h[i][j]);
		NL;
	}

	int mn = INT_MAX;
	FOR(i,1,n) mn = min(mn, (int)strlen(s[i]+1));

	int res = 0;

	FOR(i,1,mn) {
		printf("i = %d\n", i);

		int lo = i, hi = mn;
		while(lo <= hi) {
			int mid = lo + (hi-lo)/2;
			printf(" %d .. %d\n", i, mid);

			bool valid = 1;
			FOR(j,2,n) if(get_hash(j,i,mid) != get_hash(1,i,mid)) valid = 0;

			if(valid) res = max(res, mid-i+1);

			if(valid) {
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
	}

	printf("%d\n", res);

	return 0;
}
