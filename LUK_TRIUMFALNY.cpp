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
bool vis[MAXN];
int n;

int query(int x, int k) {
	vis[x] = 1;
	int sum = 0;
	FOREACH(it,g[x]) if(!vis[*it]) {
		sum += query(*it,k) + 1;
	}
	return max(0,sum-k);
}

int main() {
	scanf("%d", &n);
	REP(i,n-1) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}

	int lo = 0, hi = n;
	int res = 1;

	while(lo <= hi) {
		FOR(i,1,n) vis[i] = 0;
		int mid = lo+(hi-lo)/2;
		if(query(1,mid) == 0) {
			res = mid;
			hi = mid-1;
		} else {
			lo = mid+1;
		}
	}

	printf("%d\n", res);

	return 0;
}
