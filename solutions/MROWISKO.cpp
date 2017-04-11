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
int m[MAXN];
VI f[MAXN];
LL l[MAXN];
int siz[MAXN];
bool vis[MAXN];
PII edge;
int n, g, k;

void dfs(int u) {
	vis[u] = 1;
	//printf("dfs(%d)\n", u);
	FOREACH(it,f[u]) if(!vis[*it]) {
		l[*it] = min((LL)INT_MAX, l[u] * (siz[u]-1));
		//printf("l[%d] = min(inf, %lld * %d\n", *it, l[u], siz[u]-1);
		dfs(*it);
	}
}

int low(int n, int k) {
	int lo = 1, hi = n;
	int res = 0;
	while(lo <= hi) {
		int mid = lo+(hi-lo)/2;
		if(n/mid == k) res = mid;
		if(n/mid > k) lo = mid+1;
		else hi = mid-1;
	}
	return res;
}

int high(int n, int k) {
	int lo = 1, hi = n;
	int res = 0;
	while(lo <= hi) {
		int mid = lo+(hi-lo)/2;
		if(n/mid == k) res = mid;
		if(n/mid >= k) lo = mid+1;
		else hi = mid-1;
	}
	return res;
}

void fast_io(int &x) {
#define gc getchar_unlocked
	char c = gc();
	while(c<'0' || c>'9') c = gc();
	x = 0;
	while(c>='0' && c<='9') {
		x = 10*x+c-48;
		c = gc();
	}
}

int main() {
	fast_io(n);
	fast_io(g);
	fast_io(k);
	FOR(i,1,g) fast_io(m[i]);
	REP(i,n-1) {
		int a = 0, b = 0;
		fast_io(a);
		fast_io(b);
		if(i == 0) edge = MP(a,b);
		else {
			f[a].PB(b);
			f[b].PB(a);
		}
		siz[a]++;
		siz[b]++;
	}

	l[edge.ST] = l[edge.ND] = 1;

	dfs(edge.ST);
	dfs(edge.ND);

	vector<LL> V;
	FOR(i,1,n) if(siz[i] == 1) V.PB(l[i]);

	V.PB(INT_MIN);
	V.PB(INT_MAX);

	sort(ALL(V));

	LL res = 0;

	FOR(i,1,g) {
		LL a = low(m[i],k);
		LL b = high(m[i],k);
		if(a == 0 || b == 0) continue;

		//printf("Dla %d-tej mrówki: <%lld,%lld>\n", i, a, b);

		vector<LL>::iterator lw = lower_bound(ALL(V), a);
		vector<LL>::iterator hg = upper_bound(ALL(V), b);
		if(lw == V.end() || hg == V.begin()) continue;
		if(hg != V.begin()) --hg;

		LL dis = (hg-V.begin()) - (lw-V.begin()) + 1;

		res += dis * k;
	}

	//FOREACH(it,V) printf("%lld ", *it);
	//NL;

	printf("%lld\n", res);

	return 0;
}
