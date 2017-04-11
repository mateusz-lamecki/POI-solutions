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
const LL LLONG_MAX = 9223372036854775807LL;
const int MAXN = 1000005;
vector<LL> fib;

void calc() {
	fib.PB(0);
	fib.PB(1);
	REP(i,100) {
		long long r = fib[SIZE(fib)-2] + fib.back();
		if(r <= 400000000000000000LL) fib.PB(r);
		else break;
	}
	vector<LL> fib2 = fib;
	FOREACH(it,fib2) fib.PB(-*it);
}

int main() {
	calc();

	int k;
	scanf("%d", &k);
	REP(i,k) {
		long long x;
		scanf("%llu", &x);
		int res = 0;
		while(x != 0) {
			long long r = 1;
			long long p = LLONG_MAX;
			FOREACH(it,fib) if(abs(*it-x) < p) {
				r = *it;
				p = abs(*it-x);
			}
			x -= r;
			res++;
		}
		printf("%d\n", res);
	}

	return 0;
}
