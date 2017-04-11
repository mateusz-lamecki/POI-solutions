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
int s[MAXN];
int e[MAXN];
int n, l;

int main() {
	scanf("%d %d", &n, &l);
	REP(i,n-1) {
		int a, b;
		scanf("%d %d", &a, &b);
		s[a]++; e[a] += b;
		s[b]++; e[b] += a;
	}

	int res = 0;
	VI layer;

	FOR(i,1,n) if(s[i]==1) layer.PB(i);

	while(!layer.empty()) {
		res += min(2*l, SIZE(layer));
		VI r;
		FOREACH(it,layer) {
			e[e[*it]] -= *it;
			if(--s[e[*it]] == 1) r.PB(e[*it]);
		}
		layer = r;
	}

	printf("%d\n", res);
	return 0;
}
