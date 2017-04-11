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

const int INF = 214748360;
const int MAXN = 1000005;
int s, w;
int n;

struct Point {
	int x, y;
	bool vert;
	Point(int x, int y, bool vert=true) : x(x), y(y), vert(vert) { };
	inline bool operator <(const Point &rhs) const {
		if(vert) {
			if(this->x == rhs.x) return this->y < rhs.y;
			return this->x < rhs.x;
		} else {
			if(this->y == rhs.y) return this->x < rhs.x;
			return this->y < rhs.y;
		}
	}
};

int main() {
	vector<Point> p;
	scanf("%d%d", &s, &w);
	scanf("%d", &n);
	REP(i,n) {
		int x, y;
		scanf("%d%d", &x, &y);
		p.PB(Point(x,y));
	}
	p.PB(Point(INF,INF));

	sort(ALL(p));

	map<Point,int> points;
	REP(i,n+1) points.insert(MP(p[i],i+1));

	int res = 0;
	FOREACH(it,points) {
		if(it == --points.end()) break;
		Point nxt = Point(it->ST.x + s, it->ST.y + w);
		map<Point,int>::iterator iit = points.upper_bound(nxt);

		printf("[(%d,%d),%d] - [(%d,%d),%d]\n", it->ST.x, it->ST.y, it->ND, iit->ST.x, iit->ST.y, iit->ND);

		res = max(res, iit->ND - it->ND);
	}

	printf("%d\n", res);

	for(auto x: points) {
		printf("(%d,%d) - %d\n", x.ST.x, x.ST.y, x.ND);
	}

	return 0;
}
