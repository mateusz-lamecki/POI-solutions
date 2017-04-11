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
const int MAXS = (1<<20);
const int MAXD = 256;
int e[2*MAXS];

void insert(int x, int v) {
	x += MAXS;
	while(x > 0) {
		e[x] += v;
		x /= 2;
	}
}

int sum(int a, int b) {
	a += MAXS;
	b += MAXS;
	int res = 0;
	while(a < b) {
		if(a&1) res += e[a++];
		if(!(b&1)) res += e[b--];
		a /= 2;
		b /= 2;
	}
	if(a == b) res += e[a];
	return res;
}

char s1[MAXN];
char s2[MAXN];
VI t[MAXD];

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", s1+1);
	scanf("%s", s2+1);

	FOR(i,1,n) t[(int)s2[i]].PB(i);

	FOR(i,'A','Z') reverse(ALL(t[i]));

	LL res = 0;
	FOR(i,1,n) {
		int c = (int)s1[i];
		int k = t[c].back();
		t[c].pop_back();
		insert(k,1);
		k -= sum(1,k-1);
		res += k-1;
	}

	printf("%lld\n", res);

	return 0;
}
