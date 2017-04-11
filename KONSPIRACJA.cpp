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
const int MAXN = 5005;
int c[MAXN];
int d[MAXN];
int n;

int main() {
	scanf("%d", &n);

	int g = 0;

	REP(i,n) {
		int e;
		scanf("%d", &e);
		REP(i,e) scanf("%*d");
		++c[e];
		g += e;
	}

	g /= 2;
	int l = 0;
	FORD(i,n-1,0) REP(j,c[i]) d[l++] = i;

	int res = 0;
	int sum = 0;
	REP(i,n-1) {
		sum += d[i] - i;
		if(sum == g) {
			if(d[i+1] == d[i]) res += c[d[i]];
			else ++res;
		}
	}

	printf("%d\n", res);

	return 0;
}
