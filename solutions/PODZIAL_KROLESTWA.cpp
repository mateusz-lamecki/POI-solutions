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
int n, m;

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}

	VI r;
	FOR(i,1,n) r.PB(i);

	int s = (1 << n);
	pair<VI,int> res;
	res.ND = INT_MAX;

	REP(i,s) {
		VI t;
		int pos = n;
		int bitmask = i;
		while(bitmask > 0) {
			if(bitmask&1) t.PB(pos);
			pos--;
			bitmask /= 2;
		}
		if(SIZE(t) == n/2) {
			reverse(ALL(t));
			int o = 0;
			FOREACH(it,t) FOREACH(itt,g[*it]) if(!binary_search(ALL(t),*itt)) o++;
			if(o < res.ND) {
				res.ST = t;
				res.ND = o;
			}
		}
	}

	FOREACH(it,res.ST) printf("%d ", *it);
	NL;

	return 0;
}
