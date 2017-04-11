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
const int MAXN = 3000;
PII a[MAXN+5];
PII b[MAXN+5];
VI p[MAXN+5];
VI q[MAXN+5];
int d[MAXN+5];
PII ans[MAXN+5];
int n;

int find(int x) {
	FOR(i,x,MAXN) if(d[i] == 0) return i;
	return INF;
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d %d %d %d", &a[i].ST, &a[i].ND, &b[i].ST, &b[i].ND);

	FOR(i,1,n) p[a[i].ST].PB(i);
	FOR(i,1,n) q[b[i].ST].PB(i);

	bool res = 1;

	set<int> u;
	FOR(i,1,n) {
		FOREACH(it,p[i]) u.insert(*it);

		for(int x: u) {
			int c = find(a[x].ND);
			printf("Szukam c >= %d && <= %d\n", a[x].ND, b[x].ND);
			printf(" c = %d\n", c);
			if(c > b[x].ND) {
				printf("Przerywam!\n");
				res = 0;
				break;
			} else {
				u.erase(u.find(x));
				ans[x] = MP(i,c);
				d[c] = 1;
			}
		}

		if(!res) break;
		FOREACH(it,q[i]) if(u.find(*it) != u.end()) {
			printf("W zbiorze znajduje się %d, przerywam!\n", *it);
			res = 0;
			break;
		}
	}

	FOR(i,1,n) printf("%d %d\n", ans[i].ST, ans[i].ND);



	return 0;
}
