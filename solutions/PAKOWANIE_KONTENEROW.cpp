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

const int INF = 214748360;
const int MAXN = 1000005;
vector<PII> b, c;
VI e;
int d[MAXN];
multiset<PII> S;
int n, q;

PII g(int x) {
	set<PII>::iterator it = S.begin();
	REP(i,x) ++it;
	return *it;
}

int main() {
	scanf("%d", &n);
	REP(i,n) {
		int s, v;
		scanf("%d %d", &s, &v);
		b.PB(MP(s,v));
	}
	scanf("%d", &q);
	REP(i,q) {
		int s, k;
		scanf("%d %d", &s, &k);
		d[s] += k;
		REP(i,k) e.PB(s);
		c.PB(MP(s,k));
	}

	sort(ALL(b));
	sort(ALL(c));
	sort(ALL(e));

	REP(i,n) S.insert(b[i]);

	bool valid = true;
	int res = 0;

	REP(i,SIZE(e)) {
		while((*S.begin()).ST < e[i] && SIZE(S)>1) {
			PII a = g(0);
			PII b = g(1);
			if(a.ST != b.ST) {
				S.erase(S.begin());
			} else {
				S.erase(S.begin());
				S.erase(S.begin());
				S.insert(MP(a.ST+1, a.ND+b.ND));
			}
		}
		if(S.empty() || (*S.begin()).ST != e[i]) {
			valid = false;
			break;
		}
		PII v = *S.begin();
		res += v.ND;
		S.erase(S.begin());
	}

	if(valid) printf("%d\n", res);
	else printf("NIE\n");

	return 0;
}
