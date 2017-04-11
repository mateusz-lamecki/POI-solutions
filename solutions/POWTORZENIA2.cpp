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
const int MOD = 1000000007;
const int MAXN = 2005;
int p[MAXN];
char s[6][MAXN];
int hsh[6][MAXN];
set<int> S[6];
int n;

int get_hash(int x, int a, int b) {
	return hsh[x][b]-(a ? hsh[x][a-1]*p[b-a+1] : 0);
}

bool valid(int x) {
	REP(i,n) S[i].clear();
	REP(i,n) {
		int m = strlen(s[i]);
		REP(j,m-x+1) S[i].insert(get_hash(i,j,j+x-1));
	}
	FOREACH(it,S[0]) {
		int cnt = 1;
		FOR(j,1,n-1) if(S[j].find(*it) != S[j].end()) cnt++;
		if(cnt == n) return true;
	}
	return false;
}

int main() {
	scanf("%d", &n);
	REP(i,n) scanf("%s", s[i]);

	p[0] = 1;
	FOR(i,1,MAXN-1) p[i] = p[i-1] * MOD;

	REP(i,n) {
		hsh[i][0] = s[i][0];
		int m = strlen(s[i]);
		FOR(j,1,m) hsh[i][j] = hsh[i][j-1] * MOD + s[i][j];
	}

	int lo = 1, hi = INT_MAX;
	REP(i,n) hi = min(hi, (int)strlen(s[i]));

	int res = 0;

	while(lo <= hi) {
		int mid = lo+(hi-lo)/2;
		if(valid(mid)) {
			res = mid;
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}

	printf("%d\n", res);

	return 0;
}
