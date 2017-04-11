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
VI g[MAXN];
int a[MAXN];
int b[MAXN];
int m;
int n;

int main() {
	scanf("%d", &m);
	FOR(i,1,m) scanf("%d", &a[i]);

	FOR(i,1,m) g[a[i]].PB(i);

	scanf("%d", &n);
	REP(i,n) {
		int k;
		scanf("%d", &k);

		int pos = 0;
		bool result = 1;

		REP(i,k) {
			int x;
			scanf("%d", &x);

			VI::iterator it = upper_bound(ALL(g[x]),pos);
			if(it != g[x].end()) pos = *it;
			else result = 0;
		}

		printf("%s\n", result ? "TAK" : "NIE");

	}

	return 0;
}
