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

#include "cgdzlib.h"

using namespace std;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef long long LL;

const int INF = 2147483640;
const int MAXN = 1000005;
int a[MAXN];
int n;

PII split(VI x, int h) {
	if(SIZE(x) == 1) return MP(x[0], x[0]);
	if(SIZE(x) == 2) return MP(x[0], x[1]);

	VI a, b;
	a.PB(x[0]);

	FOR(i,1,SIZE(x)-1) {
		if(f(x[0],x[i],1<<h)) a.PB(x[i]);
		else b.PB(x[i]);
	}

	PII u = split(a,h+1);
	PII v = split(b,h+1);

	PII ret;
	if(h == 1) {
		if(u.ST != u.ND && f(u.ST,u.ND,n-1)) ret = MP(u.ST,u.ND);
		if(v.ST != v.ND && f(v.ST,v.ND,n-1)) ret = MP(v.ST,v.ND);
		if(f(u.ST,v.ST,n-1)) ret = MP(u.ST,v.ST);
		if(f(u.ND,v.ND,n-1)) ret = MP(u.ND,v.ND);
		if(f(u.ST,v.ND,n-1)) ret = MP(u.ST,v.ND);
		if(f(u.ND,v.ST,n-1)) ret = MP(u.ND,v.ST);
	} else {
		int d = (1 << (h))/2 * (SIZE(x)-1);
		if(u.ST != u.ND && f(u.ST,u.ND,d)) ret = MP(u.ST,u.ND);
		if(v.ST != v.ND && f(v.ST,v.ND,d)) ret = MP(v.ST,v.ND);
		if(f(u.ST,v.ST,d)) ret = MP(u.ST,v.ST);
		if(f(u.ND,v.ND,d)) ret = MP(u.ND,v.ND);
		if(f(u.ST,v.ND,d)) ret = MP(u.ST,v.ND);
		if(f(u.ND,v.ST,d)) ret = MP(u.ND,v.ST);
	}

	return ret;
}

int main() {
	n = inicjuj();

	if(n == 1) {
		odpowiedz(1);
	} else {
		VI p;
		FOR(i,1,n) p.PB(i);
		PII r = split(p,1);
		if(g(r.ST,r.ND)) swap(r.ST, r.ND);
		odpowiedz(r.ST);
	}

	return 0;
}
