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
const int MAXN = 500005;
char s[MAXN];
int p[MAXN];
int h[MAXN];
VI d[MAXN];
int n, q;

int get_hash(int a, int b) {
	if(a>b) return 0;
	int len = b-a+1;
	return h[b] - h[a-1]*p[len];
}

bool equal(int a, int b, int o) {
	if(o == 0) return 1;
	int p = get_hash(a,a+o-1);
	int q = get_hash(b-o+1,b);
	if(p != q) return false;
	// TODO
	return s[a] == s[b-o+1];
}

void scan(int &x) {
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = x*10 + c - '0';
		c = gc();
	}
}

void scan_string() {
#define gc getchar_unlocked
	char c = gc();
	while(c < 'a' || c > 'z') c = gc();
	FOR(i,1,n) {
		s[i] = c;
		c = gc();
	}
}

int main() {
	scan(n);
	scan_string();

	p[0] = 1;
	FOR(i,1,MAXN-1) p[i] = p[i-1] * MOD;

	h[1] = s[1];
	FOR(i,2,n) h[i] = h[i-1] * MOD + s[i];

	FOR(i,1,n) for(int j=i; j<=n; j+=i) d[j].PB(i);

	scan(q);
	REP(i,q) {
		int a, b;
		scan(a);
		scan(b);
		int res = n;
		int len = b-a+1;
		FOREACH(it,d[len]) {
			//printf(" Sprawdzam słowo [%d..%d] z okresem = %d\n", a, b, *it);
			if(equal(a,b,*it) && equal(a,b,len-*it)) {
				res = *it;
				break;
			}
		}
		printf("%d\n", res);
	}

	/*FOR(i,1,n) {
		printf("%d: ", i);
		FOREACH(it, d[i]) printf("%d ", *it);
		NL;
	}*/

	return 0;
}
