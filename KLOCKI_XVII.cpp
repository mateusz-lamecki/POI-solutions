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
int x[MAXN];
LL a[MAXN];
int n, m;

void scan(int &x) {
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = x*10 + c - '0';
		c = gc();
	}
}

int main() {
	scan(n);
	scan(m);
	FOR(i,1,n) scan(x[i]);

	int lo = INT_MAX, hi = INT_MIN;
	FOR(i,1,n) lo = min(lo, x[i]);
	FOR(i,1,n) hi = max(hi, x[i]);

	REP(i,m) {
		int k;
		scan(k);

		if(k <= lo) {
			printf("%d ", n);
			continue;
		}
		if(k > hi) {
			printf("%d ", 0);
			continue;
		}

		FOR(i,1,n) a[i] = x[i]-k;
		FOR(i,1,n) a[i] += a[i-1];

		vector<PII> P;
		FOR(i,1,n) P.PB(MP(a[i],i));
		P.PB(MP(0,0));

		sort(ALL(P));

		int mx = 0;
		int res = 0;

		while(!P.empty()) {
			vector<PII> R;
			R.PB(P.back());
			P.pop_back();
			while(!P.empty() && P.back().ST == R.back().ST) {
				R.PB(P.back());
				P.pop_back();
			}
			REP(i,SIZE(R)) mx = max(mx, R[i].ND);
			REP(i,SIZE(R)) {
				PII x = R[i];
				if(a[mx]-a[x.ND] >= 0) res = max(res, mx-x.ND);
			}
		}

		printf("%d ", res);
	}
	NL;

	return 0;
}
