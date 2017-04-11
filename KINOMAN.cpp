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

const LL CST = 9223372036854775807LL;
const int INF = 1047483640;
const int MAXN = 1000005;

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

int f[MAXN];
int w[MAXN];
int a[MAXN];
int cnt[MAXN];
int next[MAXN];
int pos[MAXN];
int n, m;

int main() {
	scanf("%d %d", &n, &m);
	FOR(i,1,n) scanf("%d", &f[i]);
	FOR(i,1,m) scanf("%d", &w[i]);

	FORD(i,n,1) {
		next[i] = pos[f[i]];
		pos[f[i]] = i;
	}

	Psoms tree(20);

	FOR(i,1,n) {
		cnt[f[i]]++;
		if(cnt[f[i]] == 1) a[i] = w[f[i]];
		else if(cnt[f[i]] == 2) a[i] = -w[f[i]];
		else a[i] = 0;
	}

	FOR(i,1,n) tree.insert(i,a[i]);

	LL res = 0;

	FOR(i,1,n) {
		LL q = tree.top();
		res = max(res, q);

		a[i] = 0;
		tree.insert(i, 0);
		if(next[i]) {
			a[next[i]] = w[f[i]];
			tree.insert(next[i], w[f[i]]);
		}
		if(next[next[i]]) {
			a[next[next[i]]] = -w[f[i]];
			tree.insert(next[next[i]], -w[f[i]]);
		}
	}

	printf("%lld\n", res);

	return 0;
}
