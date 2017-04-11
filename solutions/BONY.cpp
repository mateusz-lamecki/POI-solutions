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
bool b[MAXN];
bool vis[MAXN];
LL pos[MAXN];
int m, n;

int main() {
	int mx = 0;

	scanf("%d", &m);
	REP(i,m) {
		int k;
		scanf("%d", &k);
		b[k] = 1;
		mx = max(mx, k);
	}

	FOR(i,1,mx) pos[i] = i;

	LL cnt = 0;
	vector<LL> res;

	scanf("%d", &n);
	REP(i,n) {
		int a;
		scanf("%d", &a);
		LL p = pos[a];
		LL r = 0;
		while(r < a && p <= mx) {
			if(!vis[p]) {
				r++;
				vis[p] = 1;
				if(b[p]) {
					b[p] = 0;
					res.PB(cnt+r);
				}
			}
			p += a;
		}
		cnt += a;
		pos[a] = p;
	}

	printf("%d\n", SIZE(res));
	FOREACH(it,res) printf("%lld\n", *it);

	return 0;
}
