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
int n, m, k;

struct FAU {
	int *p, *w;
	FAU(int n) {
		p = new int[n];
		w = new int[n];
		REP(i,n) p[i] = w[i] = -1;
	}
	~FAU() {
		delete[] p;
		delete[] w;
	}
	int query(int x) {
		return (p[x] < 0) ? x : p[x] = query(p[x]);
	}
	void merge(int x, int y) {
		if((x = query(x)) == (y = query(y))) return;
		if(w[x] > w[y]) p[y] = x;
		else p[x] = y;
		if(w[x] == w[y]) w[y]++;
	}
};

int main() {
	scanf("%d %d %d", &n, &m, &k);

	FAU fau(n+1);
	set<PII> W;

	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		if(a>k) fau.merge(a,b);
		else W.insert(MP(a,b));
	}

	vector<PII> res;
	FOREACH(it,W) {
		if(fau.query(it->ST) != fau.query(it->ND)) fau.merge(it->ST, it->ND);
		else res.PB(MP(it->ST, it->ND));
	}

	printf("%d\n", SIZE(res));
	FOREACH(it,res) printf("%d %d\n", it->ST, it->ND);

	return 0;
}
