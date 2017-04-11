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

const int MOD = 1000000007;
const int INF = 2147483640;
const int MAXN = 2000005;
char w[MAXN];
vector<string> words;
VI h[MAXN];
int p[MAXN];
int n;

int get_hash(VI &H, int u, int b) {
	int len = b-u+1;
	if(u+len-1 >= SIZE(H)) return 0;
	int ret = H[u+len-1] - (u ? H[u-1]*p[len] : 0);
	return ret;
}

int main() {
	scanf("%d", &n);
	REP(i,n) {
		int a;
		scanf("%d", &a);
		scanf("%s", w);
		words.PB(string(w));
	}

	p[0] = 1;
	FOR(i,1,MAXN-1) p[i] = p[i-1] * MOD;

	REP(i,n) {
		h[i].resize(SIZE(words[i]));

		int m = SIZE(words[i]);

		h[i][0] = words[i][0];
		FOR(j,1,m-1) h[i][j] = h[i][j-1]*MOD + words[i][j];
	}

	int res = 0;
	REP(i,n) REP(j,n) {
		int k = i, l = j;
		if(SIZE(words[i]) < SIZE(words[j])) swap(k,l);

		// p >= q
		int p = SIZE(words[k]);
		int q = SIZE(words[l]);

		bool e = get_hash(h[k],0,q-1) == get_hash(h[l],0,q-1);
		bool f = ((get_hash(h[k],q,q+(p-q)/2) == get_hash(h[k],0,(p-q)/2)) || p==q);

		if(e && f) res++;
	}

	printf("%d\n", res);

	return 0;
}
