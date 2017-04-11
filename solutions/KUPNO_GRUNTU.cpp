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
const int MAXN = 2005;
int d[MAXN][MAXN];
LL s[MAXN][MAXN];
int b[MAXN][MAXN];
int k, n;

struct Point {
	int x, y;
	Point(int x=0, int y=0) : x(x), y(y) { }
};

LL sum(int a, int b, int c, int d) {
	return s[b+1][d+1] - s[a][d+1] - s[b+1][c] + s[a][c];
}

bool valid(int x) {
	return x <= 2*k;
}

int main() {
	scanf("%d %d", &k, &n);
	FOR(i,1,n) FOR(j,1,n) scanf("%d", &d[i][j]);

	REP(i,n+2) REP(j,n+2) s[i+1][j+1] = s[i][j+1] + s[i+1][j] - s[i][j] + d[i][j];

	FOR(i,0,n+2) FOR(j,0,n+2) b[i][j] = i;
	FOR(i,1,n) {
		int l = 0;
		FOR(j,1,n) {
			if(!valid(d[j][i])) l = j;
			b[j][i] = l;
		}
	}

	Point wx, wy;
	LL s = -INF;
	FOR(i,1,n) {
		stack<Point> S;
		FOR(j,1,n+1) {
			int xp = j;
			int yp = b[i][j];
			while(!S.empty() && S.top().y <= yp + 1) {
				Point u = S.top();
				if(sum(u.y,i,u.x,j-1) > s) {
					s = sum(u.y,i,u.x,j-1);
					wx = u;
					wy = Point(j-1,i);
				}
				xp = u.x;
				S.pop();
			}
			if(S.empty() || S.top().y > yp+1) S.push(Point(xp,yp+1));
		}
	}
	
	int a = wx.y, b = wy.y;
	int c = wx.x, d = wy.x;

	while(sum(a,b,c,d) >= 2*k) {
		if(b-a >= d-c && b-a > 0) { // horizontal
			int mid = (a+b) / 2; // a + (a+b) / 2;
			if(sum(a,mid,c,d) >= sum(mid+1,b,c,d)) {
				b = mid;
			} else {
				a = mid+1;
			}
		} else if(d-c > 0) { // vertical
			int mid = (c+d) / 2; //c + (c+d) / 2;
			if(sum(a,b,c,mid) >= sum(a,b,mid+1,d)) {
				d = mid;
			} else {
				c = mid+1;
			}
		} else {
			break;
		}
	}

	LL ss = sum(a,b,c,d);
	if(ss >= k && ss <= 2*k) {
		printf("%d %d %d %d\n", c, a, d, b);
	} else {
		printf("NIE\n");
	}

	return 0;
}
