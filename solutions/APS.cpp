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
LL a[MAXN];
int p[MAXN];

void scan(int &x) {
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = 10*x + c - '0';
		c = gc();
	}
}

int main() {
	p[1] = 0;
	for(int i=1; i<MAXN; i++) {
		for(int j=i*2; j<MAXN; j+=i) {
			p[j] += i;
		}
	}

	a[0] = a[1] = 0;
	FOR(i,2,MAXN-1) a[i] = a[i-1] + LL(p[i]);

	int n;
	scan(n);

	REP(i,n) {
		int x;
		scan(x);
		printf("%lld\n", a[x]);
	}

	return 0;
}
