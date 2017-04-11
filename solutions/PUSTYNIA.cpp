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
const int MAXN = 2000005;
VI G[MAXN];
VI R[MAXN];
int h[MAXN];
bool fix[MAXN];
int out[MAXN];
int n, s, m;

int main() {
	scanf("%d %d %d", &n, &s, &m);
	REP(i,s) {
		int p, d;
		scanf("%d %d", &p, &d);
		fix[p] = 1;
		h[p] = d;
	}

	REP(i,m) {
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		set<int> X;
		REP(i,k) {
			int x;
			scanf("%d", &x);
			X.insert(x);
		}
		set<int> Y;
		FOR(i,l,r) if(X.find(i) == X.end()) Y.insert(i);
		FOREACH(it,X) FOREACH(itt,Y) {
			G[*it].PB(*itt);
			R[*itt].PB(*it);
		}
	}

	FOR(i,1,n) out[i] = SIZE(G[i]);

	FOR(i,1,n) if(out[i] == 0 && h[i] == 0) h[i] = 1;

	//FOR(i,1,n) printf("%d ", h[i]);
	//NL;

	bool valid = 1;
	queue<int> Q;
	FOR(i,1,n) if(out[i] == 0) Q.push(i);
	int p = 0;

	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		p++;
		//printf("u = %d, h[u] = %d\n", u, h[u]);
		FOREACH(it,R[u]) {
			out[*it]--;
			if(!fix[*it]) h[*it] = max(h[*it], h[u]+1);
			if(h[*it] <= h[u]) {
				//printf("Przerywam przez krawędź (%d,%d)\n", *it, u);
				valid = 0;
			}
			if(out[*it] == 0) Q.push(*it);
		}
	}

	if(p < n) valid = 0;
	FOR(i,1,n) if(h[i] > 1000000000) valid = 0;

	if(valid) {
		printf("TAK\n");
		FOR(i,1,n) printf("%d ", h[i]);
		NL;
	} else {
		printf("NIE\n");
	}

	//FOR(i,1,n) FOREACH(it,G[i]) printf("h[%d] > h[%d]\n", i, *it);

	return 0;
}
