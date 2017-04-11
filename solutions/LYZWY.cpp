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

struct Psoms {
	LL *max_psoms, *max_pref, *max_suf, *sum;
	int s;
	Psoms(int size) {
		s = (1 << size);
		max_psoms = new LL[2*s];
		max_pref = new LL[2*s];
		max_suf = new LL[2*s];
		sum = new LL[2*s];
		REP(i,2*s) max_psoms[i] = max_pref[i] = max_suf[i] = sum[i] = 0;
	}
	~Psoms() {
		delete[] max_psoms;
		delete[] max_pref;
		delete[] max_suf;
		delete[] sum;
	}
	void insert(int u, LL x) {
		u += s;
		max_psoms[u] = max_pref[u] = max_suf[u] = max(x, 0ll);
		sum[u] = x;
		u /= 2;
		while(u > 0) {
			max_psoms[u] = max(max_suf[2*u] + max_pref[2*u+1], max(max_psoms[2*u], max_psoms[2*u+1]));
			max_pref[u] = max(max_pref[2*u], sum[2*u] + max_pref[2*u+1]);
			max_suf[u] = max(max_suf[2*u+1], sum[2*u+1] + max_suf[2*u]);
			sum[u] = sum[2*u] + sum[2*u+1];
			u /= 2;
		}
	}
	LL top() {
		return max_psoms[1];
	}
};

const int INF = 214748360;
const int MAXN = 200005;
LL l[MAXN];
int n, m, k, d;


int main() {
	scanf("%d %d %d %d", &n, &m, &k, &d);
	Psoms tree(18);
	FOR(i,1,n-d) tree.insert(i,-k);

	REP(i,m) {
		int r, x;
		scanf("%d %d", &r, &x);
		l[r] += x;
		tree.insert(r, -k + l[r]);

		LL p = tree.top();
		if(p <= LL(k)*LL(d)) printf("TAK\n");
		else printf("NIE\n");
	}

	return 0;
}
