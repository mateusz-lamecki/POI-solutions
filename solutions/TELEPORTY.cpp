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
const int MAXN = 1000005;
VI g[MAXN];
int t1[MAXN];
int t2[MAXN];
bool vis[MAXN];
int n, m;

void calc_dis(int x, int *T) {
	FOR(i,1,n) vis[i] = 0;
	vis[x] = 1;

	T[x] = 0;

	queue<int> Q;
	Q.push(x);

	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		FOREACH(it,g[u]) if(!vis[*it]) {
			T[*it] = T[u] + 1;
			vis[*it] = true;
			Q.push(*it);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);

	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].PB(b);
		g[b].PB(a);
	}

	calc_dis(1,t1);
	calc_dis(2,t2);

	int a = 0, b = 0, c = 0, d = 0;
	FOR(i,1,n) {
		if(t1[i] == 1) a++;
		else if(t1[i] == 2) b++;
		if(t2[i] == 1) c++;
		else if(t2[i] == 2) d++;
	}

	int e = n-1-a-b-1-c-d;

	LL res = LL(n)*(n-1)/2 - m - (n-1-a) - LL(a)*(1+c+d) - b*(1+c) - d - e*(1+min(a,c));

	printf("%lld\n", res);
	

	return 0;
}
