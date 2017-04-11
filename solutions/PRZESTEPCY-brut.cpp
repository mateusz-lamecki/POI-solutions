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
int c[MAXN];
int x[MAXN], y[MAXN];
set<int> S[MAXN];
int m, l;
int n, k;

int main() {
	scanf("%d %d", &n, &k);
	FOR(i,1,n) scanf("%d", &c[i]);
	scanf("%d %d", &m, &l);
	FOR(i,1,m) scanf("%d", &x[i]);
	FOR(i,1,l) scanf("%d", &y[i]);

	FOR(i,1,n) S[c[i]].insert(i);

	set<int> res;

	FOR(i,1,n) {
		int first = i, last = i;
		FOR(j,i,n) if(c[j] == c[i]) last = j;

		FOR(j,1,m) {
			bool found = 0;
			FOR(k,first+1,n) if(c[k] == x[j]) {
				found = 1;
				first = k;
				break;
			}
			if(!found) {
				first = n+1;
				break;
			}
		}
		FOR(j,1,l) {
			bool found = 0;
			FORD(k,last-1,1) if(c[k] == y[j]) {
				found = 1;
				last = k;
				break;
			}
			if(!found) {
				last = 0;
				break;
			}
		}

		FOR(i,first,last) if(c[i] == x[m]) res.insert(i);
	}

	printf("%d\n", SIZE(res));
	for(int x: res) printf("%d ", x);
	NL;

	return 0;
}
