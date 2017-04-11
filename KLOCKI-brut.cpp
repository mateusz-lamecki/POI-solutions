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
int a[MAXN];
int t[MAXN];
int p[MAXN];
int n;

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &a[i]);

	FOR(i,1,n) {
		if(a[i] > i) t[i] = 0;
		else {
			t[i] = 1;
			FOR(j,1,i-1) if(a[j] < a[i] && j-a[j]<=i-a[i]) {
				if(t[j]+1 >= t[i]) {
					t[i] = t[j]+1;
					p[i] = j;
				}
			}
		}
	}

	int e = 0;
	FOR(i,1,n) if(t[i] > t[e]) e = i;

	VI res;
	while(e > 0) {
		res.PB(e);
		e = p[e];
	}

	reverse(ALL(res));

	FOR(i,1,n) printf("%d ", t[i]);
	NL;
	FOR(i,1,n) printf("%d ", p[i]);
	NL;

	printf("%d\n", SIZE(res));
	REP(i,SIZE(res)) printf("%d ", res[i]);
	NL;

	return 0;
}
