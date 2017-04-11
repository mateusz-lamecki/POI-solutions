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

const int INF = 2147483640;
const int MAXN = 1000005;
const int MAXM = 1<<18;
const PII NONE(INF,INF);
PII a[2*MAXM];
PII b[2*MAXM];

bool power2(int x) {
	if(x == 1) return true;
	return (x&(x-1)) == 0;
}

void insert(int x) {
	x += MAXM;
	x /= 2;
	while(x > 0) {
		PII u1 = a[2*x], u2 = b[2*x];
		PII v1 = a[2*x+1], v2 = b[2*x+1];

		if((u1 == NONE && u2 == NONE) || (v1 == NONE && v2 == NONE)) {
			a[x] = NONE;
			b[x] = NONE;
		} else {
			if(u1.ST < u2.ST) swap(u1,u2); // u1.ST >= u2.ST
			if(v1.ND > v2.ND) swap(v1, v2); // v1.ND <= v2.ND

			if(u1.ND <= v1.ST && u1!=NONE && v1!=NONE) a[x] = MP(u1.ST,v1.ND);
			else if(u1.ND <= v2.ST && u1!=NONE && v2!=NONE) a[x] = MP(u1.ST,v2.ND);
			else a[x] = NONE;

			if(u2.ND <= v1.ST && u2!=NONE && v1!=NONE) b[x] = MP(u2.ST,v1.ND);
			else if(u2.ND <= v2.ST && u2!=NONE && v2!=NONE) b[x] = MP(u2.ST,v2.ND);
			else b[x] = NONE;
		}

		if(a[x] > b[x]) swap(a[x],b[x]);
		if(b[x] == NONE) b[x] = a[x];

		x /= 2;
	}
}

void print() {
	FOR(i,1,2*MAXM-1) {
		if((i&(i-1)) == 0) NL;
		printf("((%d,%d),(%d,%d)) ", a[i].ST, a[i].ND, b[i].ST, b[i].ND);
	}
	NL;
}

bool query() {
	if(a[1] != NONE || b[1] != NONE) return true;
	return false;
}

int main() {
	int n;
	scanf("%d", &n);
	REP(i,n) {
		int p, q;
		scanf("%d %d", &p, &q);
		if(p > q) swap(p,q);

		a[i+MAXM] = MP(p,p);
		b[i+MAXM] = MP(q,q);

		//insert(i);
	}
	FOR(i,n,MAXM-1) {
		a[i+MAXM] = b[i+MAXM] = MP(INF-10,INF-10);
	}

	REP(i,MAXM) insert(i);

	int m;
	scanf("%d", &m);
	REP(i,m) {
		int p, q;
		scanf("%d %d", &p, &q);
		--p; --q;

		swap(a[p+MAXM],a[q+MAXM]);
		swap(b[p+MAXM],b[q+MAXM]);

		insert(p);
		insert(q);

		printf("%s\n", query() ? "TAK" : "NIE");
	}

	return 0;
}
