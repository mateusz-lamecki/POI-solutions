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
const int MAXN = 1005;
const int MAXA = 105;
int T[MAXA][MAXN];
int u[MAXN], v[MAXN];
int w[MAXN];
int t, a;
int n;

int main() {
	scanf("%d %d", &t, &a);
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d %d %d", &u[i], &v[i], &w[i]);

	REP(i,MAXA) REP(j,MAXA) T[i][j] = INF;
	T[0][0] = 0;

	//printf("t = %d, a = %d, n = %d\n", t, a, n);

	FOR(i,1,n) {
		//printf(" %d %d %d\n", u[i], v[i], w[i]);
		FORD(j,t,0) {
			FORD(k,a,0) {
				int td = min(t, j + u[i]);
				int ad = min(a, k + v[i]);
				//printf(" td = %d, ad  = %d\n", td, ad);

				T[td][ad] = min(T[td][ad], T[j][k] + w[i]);
			}
		}
	}

	/*REP(i,70) {
		printf("%d: ", i);
		REP(j,6) printf("%d ", T[j][i]);
		NL;
	}*/

	printf("%d\n", T[t][a]);

	return 0;
}
