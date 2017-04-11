#include <cstdio>
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

using namespace std;
typedef vector<int> VI;
typedef long long LL;

const int INF = 2147483646;
int a[] = { 1,
2,
4,
6,
12,
24,
36,
48,
60,
120,
180,
240,
360,
720,
840,
1260,
1680,
2520,
5040,
7560,
10080,
15120,
20160,
25200,
27720,
45360,
50400,
55440,
83160,
110880,
166320,
221760,
277200,
332640,
498960,
554400,
665280,
720720,
1081080,
1441440,
2162160,
2882880,
3603600,
4324320,
6486480,
7207200,
8648640,
10810800,
14414400,
17297280,
21621600,
32432400,
36756720,
43243200,
61261200,
73513440,
110270160,
122522400,
147026880,
183783600,
245044800,
294053760,
367567200
};

int main() {
	int n;
	scanf("%d", &n);
	int m = sizeof(a)/4;

	if(n==1) {
		printf("1\n");
		return 0;
	}
	FORD(i,m-1,0) {
		if(a[i]<=n || i==m) {
			printf("%d\n", a[i]);
			return 0;
		}
	}

	return 0;
}

