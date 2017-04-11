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
const int MOD = 1000000007;
const int MAXN = 200005;
int a[MAXN];
LL p[MAXN];
LL h[MAXN];
LL r[MAXN];
int n;

LL get_hash1(int a, int b) {
	int len = b-a+1;
	return h[b] - h[a-1]*p[len];
}

LL get_hash2(int a, int b) {
	a = n-a+1;
	b = n-b+1;
	if(a > b) swap(a,b);
	int len = b-a+1;
	return r[b] - r[a-1]*p[len];
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &a[i]);

	p[0] = 1;
	FOR(i,1,MAXN-1) p[i] = p[i-1] * MOD;

	h[1] = a[1];
	FOR(i,2,n) h[i] = h[i-1] * MOD + a[i];

	r[1] = a[n];
	FOR(i,2,n) r[i] = r[i-1] * MOD + a[n-i+1];

	pair<int,VI> P;

	FOR(i,1,n) {
		set<LL> S;
		for(int j=1; j<=n; j+=i) if(j+i-1 <= n) {
			LL e = get_hash1(j,j+i-1) * get_hash2(j,j+i-1);
			S.insert(e);
		}
		if(SIZE(S) > P.ST) {
			P.ND.clear();
			P.ST = SIZE(S);
			P.ND.PB(i);
		} else if(SIZE(S) == P.ST) P.ND.PB(i);
	}

	printf("%d %d\n", P.ST, SIZE(P.ND));
	FOREACH(it,P.ND) printf("%d ", *it);
	NL;

	return 0;
}
