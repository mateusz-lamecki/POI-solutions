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
const int MAXN = 100005;
int w[MAXN], h[MAXN];
int n, m;

bool get_result(int x) {
	//printf("Sprawdzam %d\n", x);
	if(x==0) return true;
	multiset<int> W;
	REP(i,n) W.insert(w[i]);

	FORD(i,x-1,0) {
		multiset<int>::iterator it = W.lower_bound(h[i]);
		if(it == W.end()) return false;
		else {
			//printf("lower_bould(%d) = %d\n", h[i], *it);
			int u = *it;
			W.erase(it);
			W.insert(u-h[i]);
			//printf("usuwam %d, wstawiam %d\n", u, u-h[i]);
		}
	}
	
	//FOREACH(it,W) printf("%d ", *it);
	//NL;

	return true;
}

int main() {
	scanf("%d %d", &n, &m);
	REP(i,n) scanf("%d", &w[i]);
	REP(i,m) scanf("%d", &h[i]);

	sort(w,w+n);
	sort(h,h+m);

	int res = 0;
	int lo = 0, hi = m;
	while(lo<=hi) {
		int mid = lo + (hi-lo)/2;
		bool possible = get_result(mid);
		if(possible) res = max(res, mid);
		if(lo==hi) break;
		if(possible) lo = mid + 1;
		else hi = mid - 1;
	}

	printf("%d\n", res);


	return 0;
}
