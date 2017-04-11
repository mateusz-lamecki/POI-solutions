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
#include <unordered_set>
#include <unordered_map>
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
const int MAXN = 5005;
VI g[MAXN];
int parent[MAXN];
bool vis[MAXN];
bool occ[MAXN];
int res[MAXN];
int p[MAXN];
int n, k, l;

void dfs(int u) {
	vis[u] = 1;
	FOREACH(it,g[u]) if(!vis[*it]) {
		parent[*it] = u;
		if(occ[u]) occ[*it] = 1;
		dfs(*it);
	}
}

int main() {
	scanf("%d", &n);
	REP(i,n-1) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}

	scanf("%d", &k);
	FOR(i,1,k) scanf("%d", &p[i]);

	scanf("%d", &l);
	REP(i,l) {
		printf("%d-ta mrówka\n", i+1);
		int x;
		scanf("%d", &x);
		FOR(i,1,n) vis[i] = occ[i] = 0;
		FOR(i,1,k) occ[p[i]] = 1;

		dfs(x);

		while(true) {
			bool found = 0;
			FOR(i,1,k) {
				if(p[i] == x) {
					res[i]++;
					printf(" Zdjęła ją %d!\n", i);
					found = 1;
					break;
				}
				if(!occ[parent[i]]) {
					p[i] = parent[i];
					occ[p[i]] = 1;
				}
			}
			if(found) break;
		}
	}

	FOR(i,1,k) printf("%d %d\n", p[i], res[i]);

	return 0;
}
