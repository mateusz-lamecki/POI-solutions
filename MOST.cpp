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
const int MAXN = 100005;
int t[MAXN];
int n;

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &t[i]);

	if(n == 1) {
		printf("%d\n", t[1]);
		return 0;
	}

	int i = 1;

	int res = t[++i];
	int hm = 2;
	if(n%2 == 1) {
		res += t[++i] + t[1];
		hm++;
	}

	while(hm < n) {
		int a = t[++i];
		int b = t[++i];
		if(a <= 2 * t[2] - t[1]) res += a + b + 2 * t[1];
		else res += b + 2 * t[2] + t[1];
		hm += 2;
	}

	printf("%d\n", res);

	return 0;
}
