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
const int MOD = 1000000009;
const int MAXN = 2000005;
map<int,int> M;
char w[MAXN];

string min_period(string x) {
	x = "#" + x;
	VI p(SIZE(x));

	int t = p[1] = 0;
	FOR(i,2,SIZE(x)-1) {
		while(t>0 && x[t+1] != x[i]) t = p[t];
		if(x[t+1] == x[i]) t++;
		p[i] = t;
	}

	int s = 0;
	int u = SIZE(x)-1 - p[SIZE(x)-1];
	if((SIZE(x)-1)%u == 0) s = u;
	else s = SIZE(x)-1;

	string res;
	FOR(i,1,s) res += x[i];
	return res;
}

int get_hash(string x) {
	int s = SIZE(x);
	vector<int> h(s);
	h[0] = x[0];
	FOR(i,1,s-1) h[i] = h[i-1] * MOD + x[i];
	return h[SIZE(x)-1];
}

int main() {
	vector<int> P;

	int n;
	scanf("%d", &n);

	REP(i,n) {
		int s;
		scanf("%d %s", &s, w);
		string e(min_period(w));
		int h = get_hash(e);
		M[h]++;
	}

	LL res = 0;
	FOREACH(it,M) res += LL(it->ND) * LL(it->ND);

	printf("%lld\n", res);

	return 0;
}
