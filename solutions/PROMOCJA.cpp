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
const int MAXN = 1000005;

int main() {
	multiset<int> P;

	LL res = 0;

	int n;
	scanf("%d", &n);
	REP(i,n) {
		int k;
		scanf("%d", &k);
		REP(i,k) {
			int x;
			scanf("%d", &x);
			P.insert(x);
		}

		int u = *P.begin();
		P.erase(P.begin());

		int v = *(--P.end());
		P.erase(--P.end());

		res += v-u;
	}

	printf("%lld\n", res);

	return 0;
}
