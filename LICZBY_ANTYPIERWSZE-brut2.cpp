#include <cstdio>
#include <cstdlib>
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
const int MAXM = 500000000;
int *t;

int find_dividers(int x) {
	int res = 1;
	PII r(0,0);
	while(x > 1) {
		if(r.ST == t[x]) {
			r.ND++;
		} else {
			res *= r.ND + 1;
			r.ST = t[x];
			r.ND = 1;
		}
		x /= t[x];
	}
	return res;
}

int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(0);

	int n = (argc > 1) ? atoi(argv[1]) : MAXM;

	t = (int*)malloc(sizeof(t) * (n+1));

	FOR(i,2,n) {
		for(int j = i; j <= n; j += i) if(t[j] == 0) t[j] = i;
	}

	int a = 0;
	FOR(i,1,n) {
		int d = find_dividers(i);
		if(d > a) {
			cout << i << endl;
			a = d;
		}
	}

	free(t);

	return 0;
}
