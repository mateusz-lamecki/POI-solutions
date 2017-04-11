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
const int MAXN = 2000005;
const int MAXS = (1<<21);
LL e[2*MAXS];
int w[MAXN];
LL f[MAXN];
LL s[MAXN];
int n, d;
LL p;

void insert(int x, LL v) {
	x += MAXS;
	e[x] = v;
	x /= 2;
	while(x > 0) {
		e[x] = max(e[x*2], e[x*2+1]);
		x /= 2;
	}
}

LL query(int a, int b) {
	a += MAXS;
	b += MAXS;
	LL res = 0;
	while(a < b) {
		if(a&1) res = max(res, e[a++]);
		if(!(b&1)) res = max(res, e[b--]);
		a /= 2;
		b /= 2;
	}
	if(a == b) res = max(res, e[a]);
	return res;
}

void calc_f() {
	LL sum = 0;
	FOR(i,1,d) sum += w[i];

	FOR(i,d+1,n+1) {
		insert(i-d,sum);
		f[i-d] = sum;
		sum += w[i];
		sum -= w[i-d];
	}
	FOR(i,n-d+2,n) {
		insert(i,s[n]-s[i-1]);
		f[i] = s[n] - s[i-1];
	}
}

int get_last(LL x) { // return greatest i, that s[i] <= x && i <= n
	int lo = 1, hi = n;
	int ret = 0;
	while(lo <= hi) {
		int mid = lo+(hi-lo)/2;
		if(s[mid] <= x) {
			ret = mid;
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return ret;
}

int main() {
	scanf("%d %lld %d", &n, &p, &d);
	FOR(i,1,n) scanf("%d", &w[i]);

	FOR(i,1,n) s[i] = s[i-1] + w[i];

	calc_f();
	int res = 0;

	FOR(i,1,n) {
		int b = get_last(s[i-1]+p);

		LL q = query(i,b+1);
		//FOR(j,i,b+1) q = max(q, f[j]);

		int last = get_last(s[i-1]+p+q);
		int dis = last-i+1;

		res = max(res, dis);

		//printf("%d..%d\n", i, i+dis-1);
	}

	printf("%d\n", res);

	//FOR(i,1,n) printf("%lld ", f[i]);
	//NL;

	return 0;
}
