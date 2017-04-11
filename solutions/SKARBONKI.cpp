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
bool vis[MAXN];

struct FAU {
	VI p, w;
	FAU(int n) {
		p.resize(n,-1);
		w.resize(n,-1);
	}
	int query(int x) {
		return (p[x]<0) ? x : p[x] = query(p[x]);
	}
	void merge(int x, int y) {
		if((x = query(x)) == (y = query(y))) return;
		if(w[x] > w[y]) p[y] = x;
		else p[x] = y;
		if(w[x] == w[y]) w[y]++;
	}
};

int main() {
	int n;
	scanf("%d", &n);

	FAU fau(n+1);
	int res = 0;

	FOR(i,1,n) {
		int x;
		scanf("%d", &x);
		fau.merge(x,i);
	}

	FOR(i,1,n) {
		int d = fau.query(i);
		if(!vis[d]) res++;
		vis[d] = 1;
	}

	printf("%d\n", res);

	return 0;
}
