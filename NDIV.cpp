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
bool p[MAXN];
VI primes;

int main() {
	REP(i,MAXN) p[i] = 1;
	p[0] = p[1] = 0;

	for(int i=2; i<MAXN; i++) if(p[i] && LL(i)*LL(i)<LL(MAXN)) {
		for(int j=i*i; j<MAXN; j+=i) p[j] = 0;
	}

	REP(i,MAXN) if(p[i]) primes.PB(i);

	REP(i,20) printf("%d ", primes[i]);
	return 0;
}
