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

struct Point {
	int x, y;
	Point() { };
	Point(int x, int y) : x(x), y(y) { };
	bool operator <(const Point& rhs) const {
		if(x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}
};

const int INF = 2147483640;
const int MAXN = 605;
const int MAXM = 10005;
Point p[MAXN];
Point f[MAXM];
int c[MAXM];
int g[MAXN][MAXN];
int n, m;

int sgn(LL x) {
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

int dot(Point x, Point y, Point z) {
	Point vec1(y.x-x.x, y.y-x.y);
	Point vec2(z.x-y.x, z.y-y.y);
	LL p = LL(vec1.x)*vec2.y - LL(vec2.x)*vec1.y;
	return sgn(p);
}

void calc(int x) {
	REP(i,m) {
		if(dot(p[x], p[(x-1+n)%n], f[i]) == 0) continue;
		int lo = 1;
		int hi = n - 1;
		while(lo+1 < hi) {
			int mid = (lo+hi) / 2;
			if(dot(p[x], p[(x+mid)%n], f[i]) > 0) hi = mid;
			else lo = mid;
		}
		g[x][(x+lo+1)%n] += c[i];
	}
	FOR(j,1,n-2) g[x][(x+j+1)%n] += g[x][(x+j)%n];
}

int main() {
	scanf("%d", &n);
	REP(i,n) scanf("%d %d", &p[i].x, &p[i].y);
	scanf("%d", &m);
	REP(i,m) scanf("%d %d %d", &f[i].x, &f[i].y, &c[i]);

	REP(i,n) calc(i);

	int sum = 0;
	REP(i,m) sum += c[i];

	int res = INT_MIN;
	REP(i,n) REP(j,i) REP(k,j) res = max(res, sum-g[j][i]-g[k][j]-g[i][k]);

	printf("%d\n", res);

	return 0;
}
