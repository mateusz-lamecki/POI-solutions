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
#include <unordered_set>
#include <unordered_map>
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
const int MAXM = 2000000005;

int divisors(int x) {
	int ret = 1;
	int sq = sqrt(x);
	int k = 2;
	while(x>1 && k<=sq) {
		int p = 0;
		while(x%k==0) {
			x /= k;
			p++;
		}
		++k;
		ret *= (p+1);
	}
	if(x>1) ret *= 2;
	return ret;
}

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(0);
	int last = 0;

	int n = (argc > 1) ? atoi(argv[1]) : MAXM;

	cout << 1 << endl;
	for(int i=2; i<n; i += 2) {
		int d = divisors(i);
		if(d > last) {
			cout << i << endl;
			last = d;
		}
	}

	return 0;
}
