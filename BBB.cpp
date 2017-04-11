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
const int MAXN = 1000005;
char w[MAXN];
int s[2*MAXN];
int n, p, q, x, y;

int main() {
	scanf("%d %d %d %d %d", &n, &p, &q, &x, &y);
	scanf("%s", w);
	REP(i,2*n) s[i] = ((i>0) ? s[i-1] : 0) + (w[i-n<0?i:i-n]=='+' ? 1 : -1);

	int res = INF;
	deque<int> L;

	FORD(i,2*n-1,n) {
		while(!L.empty() && s[L.back()] >= s[i]) L.pop_back();
		L.PB(i);
	}

	FORD(i,n,1) {
		int dif = s[L.front()] - (i>0 ? s[i-1] : 0) + p;

		int w = 0;
		if(dif < 0) w = ceil(-dif/2.0);

		int W = 0;
		if(q-p<s[n-1]+2*w) W = w + (s[n-1] + 2*w - q + p) / 2;
		else W = w + (q-p-s[n-1]-2*w) / 2;

		res = min(res, x*W + (n-i)*y);

		while(!L.empty() && L.front() >= i+n) L.pop_front();
		while(!L.empty() && s[L.back()] >= s[i-1]) L.pop_back();
		L.PB(i-1);
	}

	printf("%d\n", res);
	return 0;
}

