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
const int CADD = 31000;
int s, w;
int n;

struct CountTree {
	int *el, *pref, s;
	CountTree(int size) {
		s = (1 << size);
		el = new int[2*s];
		pref = new int[2*s];
		REP(i,2*s) el[i] = pref[i] = 0;
	}
	~CountTree() {
		delete[] el;
		delete[] pref;
	}
	void insert(int x, int v) {
		//el[x+s] += v;
		/*while(x > 0) {
			el[x] += v;//el[2*x] + el[2*x+1];
			x /= 2;
		}*/
		x += s;
		el[x] += v;
		pref[x] = 0;
		x /= 2;

		while(x > 0) {
			el[x] += v;
			pref[x] = max(pref[2*x], el[2*x]+pref[2*x+1]);
			x /= 2;
		}

		//for(x+=s; x; x>>=1) el[x] += v;
	}
	int query(int a, int b) {
		int ret = 0;
		a += s;
		b += s;
		while(a < b) {
			if(a&1) ret += el[a++];
			if(!(b&1)) ret += el[b--];
			a /= 2;
			b /= 2;
		}
		if(a==b) ret += el[a];
		return ret;
	}
	int get_top() {
		return pref[1];
	}
	void add(int x, int v) {
		assert(x>=0);
		insert(x,v);
	}
	void print(int t=n) {
		REP(i,t) printf("%d ", query(i,i));
		NL;
	}
};

struct Point {
	int x,y,z;
	Point(int x, int y, int z) : x(x), y(y), z(z) { };
	inline bool operator <(const Point& rhs) const {
		if(this->y == rhs.y) {
			if(this->z == rhs.z) return this->x < rhs.x;
			else return this->z < rhs.z;
		} else return this->y < rhs.y;
	}
};

int main() {
	CountTree tree(17);
	multiset<Point> points;

	scanf("%d%d", &s, &w);
	scanf("%d", &n);
	REP(i,n) {
		int x, y;
		scanf("%d%d", &x, &y);
		x += CADD;
		y += CADD;
		points.insert(Point(x,y,1));
		points.insert(Point(x,y+w+1,-1));
	}

	int res = 0;
	FOREACH(it,points) {
		Point point = *it;

		tree.add(point.x,point.z);
		tree.add(point.x+s+1,-point.z);

		int r = tree.get_top(); //tree.query(0,point.x);
		//int r = tree.query(point.x,point.x+s+1);

		//printf("(%d,%d,%d), query(%d,%d) = %d\n   ", point.x, point.y, point.z, 0, point.x, r);
		//tree.print();
		//printf("r = %d\n", tree.get_top());

		res = max(res, r);
	}

	printf("%d\n", res);

	return 0;
}
