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
const int MAXN = 1000005;
VI g[MAXN];
int in[MAXN];
int n, m;

int main() {
	scanf("%d %d", &n, &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		in[b]++;
	}

	multiset<PII> S;
	FOR(i,1,n) S.insert(MP(in[i],i));

	VI res;

	while(!S.empty()) {
		PII u = *S.begin();
		S.erase(S.begin());
		res.PB(u.ND);
		while(!g[u.ND].empty()) {
			int v = g[u.ND].back();
			g[u.ND].pop_back();
			S.erase(S.find(MP(in[v],v)));
			in[v]--;
			S.insert(MP(in[v],v));
		}
	}

	FOREACH(it,res) printf("%d ", *it);
	NL;

	return 0;
}
