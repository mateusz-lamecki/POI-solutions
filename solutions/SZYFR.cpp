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

const int INF = 2147483640;
const int MAXN = 1000005;
VI S1;
VI S2;
int n;
int c;

void calc(VI& S, VI& d) {
	int p = SIZE(d);
	int s = 1 << p;
	REP(i,s) {
		int sum = 0;
		int bitmask = i;
		int pos = p-1;
		while(bitmask > 0) {
			if((bitmask&1)==1) {
				sum += d[pos];
			}
			bitmask /= 2;
			pos--;
		}
		S.PB(sum);
	}
}

VI query(VI& p, int x) {
	int s = 1 << SIZE(p);
	REP(i,s) {
		VI r(SIZE(p));
		int bitmask = i;
		int pos = SIZE(p)-1;
		int sum = 0;
		while(bitmask > 0) {
			if((bitmask&1)==1) {
				r[pos] = 1;
				sum += p[pos];
			}
			pos--;
			bitmask /= 2;
		}
		if(sum == x) {
			return r;
		}
	}
	return VI();
}

int main() {
	scanf("%d", &n);

	int u = n/2;
	VI d1(u);
	REP(i,u) scanf("%d", &d1[i]);

	calc(S1,d1);

	VI d2(n-u);
	REP(i,n-u) scanf("%d", &d2[i]);

	calc(S2,d2);

	int s = 0;
	scanf("%d", &s);

	sort(ALL(S1));
	sort(ALL(S2));

	PII res(0,0);
	for(int x: S1) if(binary_search(ALL(S2),s-x)) res = MP(x, s-x);

	VI a = query(d1, res.ST);
	VI b = query(d2, res.ND);

	for(int x: a) printf("%d", x);
	for(int x: b) printf("%d", x);
	NL;

	return 0;
}
