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
typedef long long LL;
typedef pair<LL,LL> PII;
typedef vector<LL> VI;

struct SumTree {
	LL *e;
	int s;
	SumTree(int size) {
		s = (1 << size);
		e = new LL[2*s];
		REP(i,2*s) e[i] = 0;
	}
	~SumTree() {
		delete[] e;
	}
	void update(int x, LL v) {
		x += s;
		while(x > 0) {
			e[x] += v;
			x /= 2;
		}
	}
	void insert(int a, int b, LL v) {
		update(a,v);
		update(b+1,-v);
	}
	LL sum(int a, int b) {
		a += s;
		b += s;
		LL res = 0;
		while(a < b) {
			if(a&1) res += e[a++];
			if(!(b&1)) res += e[b--];
			a /= 2;
			b /= 2;
		}
		if(a == b) res += e[a];
		return res;
	}
	LL query(int x) {
		return sum(0,x);
	}
	void clear() {
		REP(i,2*s) e[i] = 0;
	}
};


const int INF = 2147483640;
const int MAXN = 1000005;
LL o[MAXN], p[MAXN];
LL l[MAXN], r[MAXN];
LL lo[MAXN], hi[MAXN];
LL a[MAXN];
LL res[MAXN];
VI pos[MAXN];
int n, m;
int k;

int main() {
	scanf("%d %d", &n, &m);
	FOR(i,1,m) scanf("%lld", &o[i]);
	FOR(i,1,n) scanf("%lld", &p[i]);
	scanf("%d", &k);
	FOR(i,1,k) scanf("%lld %lld %lld", &l[i], &r[i], &a[i]);

	FOR(i,1,m) pos[o[i]].PB(i);

	SumTree tree(19);

	int q = 1;
	while(q < k) q *= 2;

	FOR(i,1,n) {
		lo[i] = 1;
		hi[i] = k;
		res[i] = k+1;
	}

	while(true) {
		int cnt = 0;
		FOR(i,1,n) if(lo[i] <= hi[i]) cnt++;
		if(cnt == 0) break;

		vector<PII> Q;
		FOR(i,1,n) {
			LL mid = lo[i] + (hi[i]-lo[i])/2;
			Q.PB(MP(mid,i));
		}
		sort(ALL(Q));
		reverse(ALL(Q));

		FOR(i,1,k) {
			if(l[i] <= r[i]) tree.insert(l[i],r[i],a[i]);
			else {
				tree.insert(l[i],m,a[i]);
				tree.insert(1,r[i],a[i]);
			}

			while(!Q.empty() && Q.back().ST == i) {
				LL mid = Q.back().ST;
				LL id = Q.back().ND;
				Q.pop_back();
				LL sum = 0;
				FOREACH(it,pos[id]) sum += tree.query(*it);
				if(sum >= p[id]) {
					res[id] = i;
					hi[id] = mid-1;
				} else {
					lo[id] = mid+1;
				}
			}
		}

		tree.clear();
	}

	FOR(i,1,n) {
		if(res[i] <= k) printf("%lld\n", res[i]);
		else printf("NIE\n");
	}

	return 0;
}
