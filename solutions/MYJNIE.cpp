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
const int MAXN = 405;
int a[MAXN], b[MAXN];
int c[MAXN];
int x[MAXN];
int n, m;

pair<int,VI> res;

int main() {
	scanf("%d %d", &n, &m);
	REP(i,n) scanf("%d %d %d", &a[i], &b[i], &c[i]);

	VI p(m);
	REP(i,m) p[i] = i;

	int t = (1 << m);
	REP(i,t) {
		int pos = m-1;
		int bitmask = i;
		VI q(m,0);
		while(bitmask > 0) {
			if(bitmask&1) {
				q[pos] = 1;
			}
			pos--;
			bitmask /= 2;
		}

		FOR(i,1,n) x[i] = 0;
		REP(i,m) if(q[i]) {
			FOR(j,a[i],b[i]) x[j] = max(x[j], c[i]);
		}

		int vres = 0;
		REP(i,m) {
			FOR(j,a[i],b[i]) if(x[j] <= c[i]) {
				vres += x[j];
				//printf(" %d-ty kierowca odwiedzi myjnię %d!\n", i, j);
				break;
			}
		}

		VI e(n);
		REP(i,n) e[i] = x[i+1];
		if(vres > res.ST) {
			res.ST = vres;
			res.ND = e;
		}

		FOR(i,1,n) printf("%d ", x[i]);
		NL;
		//printf("vres = %d\n", vres);
		//NL;
	}

	printf("%d\n", res.ST);
	FOREACH(it,res.ND) printf("%d ", *it);
	NL;


	return 0;
}
