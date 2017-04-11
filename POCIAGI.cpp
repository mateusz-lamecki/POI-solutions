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
const int MOD = 1000000007;
const int HMOD = 1000003;
const int MAXN = 1005;
const int MAXL = 105;
const int MAXM = 100005;
char s[MAXN][MAXL];
int h[MAXN][MAXL];
int res[MAXN];
int p[MAXL];
int n, l, m;
map<int,set<int> > M;

void recalculate_hash(int x, int p=1) {
	FOR(i,p,l) h[x][i] = h[x][i-1] * MOD + s[x][i];
}

void scan(int &x) {
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = 10*x + c - '0';
		c = gc();
	}
}

void erase(int v) {
	int q = h[v][l];
	if(M[q].find(v) == M[q].end()) {
		return;
	}
	M[q].erase(M[q].find(v));
}

int main() {
	scanf("%d %d %d", &n, &l, &m);
	FOR(i,1,n) scanf("%s", s[i]+1); 

	p[0] = 1;
	FOR(i,1,l) p[i] = p[i-1] * MOD;

	FOR(i,1,n) recalculate_hash(i);
	FOR(i,1,n) {
		M[h[i][l]].insert(i);
	}

	FOR(i,1,n) res[i] = SIZE(M[h[i][l]]);

	REP(i,m) {
		int p1, w1, p2, w2;
		scan(p1);
		scan(w1);
		scan(p2);
		scan(w2);
		swap(s[p1][w1],s[p2][w2]);

		if(p1 != p2) erase(p1);
		erase(p2);
		recalculate_hash(p1,w1);
		if(p1 != p2) recalculate_hash(p2,w2);
		M[h[p1][l]].insert(p1);
		if(p1 != p2) M[h[p2][l]].insert(p2);

		int s1 = SIZE(M[h[p1][l]]);
		int s2 = SIZE(M[h[p2][l]]);
		FOREACH(it,M[h[p1][l]]) res[*it] = max(res[*it], s1);
		if(p1 != p2) FOREACH(it,M[h[p2][l]]) res[*it] = max(res[*it], s2);
	}

	FOR(i,1,n) printf("%d\n", res[i]);

	return 0;
}
