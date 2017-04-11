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
const int MAXN = 605;
int x[MAXN][MAXN];
int dp[MAXN][MAXN];
int w[MAXN][MAXN];
int r[MAXN][MAXN];
int n, k;
VI res;

int get(int a, int b, int c, int d) {
	int ret = dp[b+1][d+1] - dp[a][d+1] - dp[b+1][c] + dp[a][c];
	//printf("  liczę (%d,%d) - (%d,%d) = %d\n", a, b, c, d, ret);
	return ret;
}

void calc_dp() {
	REP(i,n+1) REP(j,n+1) {
		dp[i+1][j+1] = dp[i][j+1] + dp[i+1][j] - dp[i][j] + x[i][j];
	}
}

int main() {
	scanf("%d%d", &n, &k);
	FOR(i,1,n-1) FOR(j,i+1,n) scanf("%d", &x[i][j]);

	calc_dp();

	/*REP(i,n+1) {
		REP(j,n+1) printf("%d\t", x[i][j]);
		NL;
	}
	NL;*/

	FOR(i,1,k) {
		//printf("Dla %d kontrol:\n", i);
		FORD(j,n,1) {
			//printf(" dla stacji %d..%d\n", j, n);
			FOR(k,j,n-i) {
				int u = w[k+1][i-1] + get(j,k,k+1,n);
				if(u > w[j][i]) {
					//printf("   aktualizuję %d do %d\n", w[j][i], u);
					w[j][i] = u;
					r[j][i] = k;
				}
			}
		}
	}

	/*REP(i,n+1) {
		REP(j,k+1) {
			printf("%d ", w[i][j]);
		}
		NL;
	}
	NL;
	REP(i,n+1) {
		printf("%d: ", i);
		REP(j,k+1) {
			printf("%d\t", r[i][j]);
		}
		NL;
	}*/

	set<int> res;
	
	int x = k, y = 1;
	while(x>0) {
		res.insert(r[y][x]);
		y = r[y][x] + 1;
		x--;
	}

	if(res.find(0) != res.end()) res.erase(res.find(0));

	FOR(i,1,n) if(SIZE(res) < k && res.find(i) == res.end()) res.insert(i);

	FOREACH(it,res) printf("%d ", *it);
	NL;

	return 0;
}
