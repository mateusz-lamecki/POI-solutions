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
const int MAXN = 1005;
const int MAXS = 50005;
int m[MAXN];
VI t[MAXS];
int n;

VI get(int x) {
	VI res;
	while(x > 0) {
		res.PB(t[x].front());
		x -= t[x].front();
	}
	return res;
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &m[i]);

	sort(m+1,m+n+1);

	int s = 0;
	FOR(i,1,n) s += m[i];

	t[0].PB(0);

	int p = 0;
	int q = 0;
	int remaining = 0;

	FOR(i,1,n) {
		FORD(j,s,0) if(!t[j].empty()) {
			if(t[j+m[i]].empty()) {
				t[j+m[i]].PB(m[i]);
			} else {
				p = i;
				q = j;
				remaining = m[i];
			}
		}
	}

	VI res1 = get(q);
	res1.PB(remaining);
	VI res2 = get(q+m[p]);

	if(p == 0) {
		res1.clear();
		res2.clear();
	}

	printf("%d %d\n", SIZE(res1), SIZE(res2));
	FOREACH(it,res1) printf("%d ", *it); NL;
	FOREACH(it,res2) printf("%d ", *it); NL;


	return 0;
}
