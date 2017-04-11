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
//#include <unordered_set>
//#include <unordered_map>
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
const int MAXN = 3005;

struct Interval {
	int a, b, id;
	Interval(int a=0, int b=0, int id=0) : a(a), b(b), id(id) { };
	bool operator <(const Interval &rhs) const {
		if(b == rhs.b) {
			if(a == rhs.a) return id < rhs.id;
			return a < rhs.a;
		}
		return b < rhs.b;
	}
};
set<int> idX[MAXN];
set<int> idY[MAXN];
PII res[MAXN];
PII p1[MAXN];
PII p2[MAXN];
bool exist = 1;
int n;

int main() {
	scanf("%d", &n);
	FOR(i,1,n) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		idX[a].insert(i);
		idY[b].insert(i);
		p1[i] = MP(a,b);
		p2[i] = MP(c,d);
	}

	multiset<Interval> X, Y;

	FOR(i,1,n) {
		FOREACH(it,idX[i]) X.insert(Interval(p1[*it].ST,p2[*it].ST,*it));
		if(!X.empty()) {
			Interval u = *X.begin();
			X.erase(X.begin());
			res[u.id].ST = i;

			if(!X.empty()) {
				Interval v = *X.begin();
				if(v.b <= i) exist = 0;
			}
		} else exist = 0;
	}

	FOR(i,1,n) {
		FOREACH(it,idY[i]) Y.insert(Interval(p1[*it].ND,p2[*it].ND,*it));
		if(!Y.empty()) {
			Interval u = *Y.begin();
			Y.erase(Y.begin());
			res[u.id].ND = i;

			if(!Y.empty()) {
				Interval v = *Y.begin();
				if(v.b <= i) exist = 0;
			}
		} else exist = 0;
	}

	if(exist) {
		FOR(i,1,n) printf("%d %d\n", res[i].ST, res[i].ND);
	} else {
		printf("NIE\n");
	}


	return 0;
}
