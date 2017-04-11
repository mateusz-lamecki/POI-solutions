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
vector<VI> G;
int s[MAXN];
int h[MAXN];
VI g[MAXN];
bool dead[MAXN];
bool vis[MAXN];
int wrong[MAXN];
int u;
int n;

void mark(int x, VI& P) {
	vis[x] = 1;
	P.PB(x);
	if(!vis[s[x]]) mark(s[x], P);
	FOREACH(it,g[x]) if(!vis[*it]) mark(*it, P);
}

void dfs(int x, int wrong, VI& post) {
	vis[x] = 1;
	FOREACH(it,g[x]) if(!vis[*it]) dfs(*it, wrong, post);
	post.PB(x);
}

int simulate(VI& order) {
	int ret = 0;
	FOREACH(it,order) if(!dead[*it] && !dead[s[*it]]) {
		dead[s[*it]] = 1;
		ret++;
	}
	return ret;
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) {
		scanf("%d", &s[i]);
		//g[i].PB(s[i]);
		g[s[i]].PB(i);
		h[s[i]]++;
	}

	FOR(i,1,n) if(!vis[i]) {
		G.PB(VI());
		mark(i,G.back());
	}

	FOR(i,1,n) vis[i] = 0;

	int k = SIZE(G);
	REP(i,k) {
		int u = G[i].front();
		vis[u] = 1;
		while(!vis[s[u]]) {
			u = s[u];
			vis[u] = 1;
		}
		// incorrect edge: (u, s[u])
		wrong[i] = u;
		//h[s[u]]--;
	}

	FOR(i,1,n) vis[i] = 0;

	int res1 = 0, res2 = 0;

	REP(i,k) {
		VI post;
		dfs(wrong[i], wrong[i], post);
		FOREACH(it,G[i]) dead[*it] = 0;
		int d1 = simulate(post);
		post.insert(post.begin(),post.back());
		post.pop_back();
		FOREACH(it,G[i]) dead[*it] = 0;
		int d2 = simulate(post);

		int leaves = 0;
		FOREACH(it,G[i]) if(h[*it] == 0) leaves++;

		res1 += min(d1, d2);
		res2 += max(1, min(SIZE(G[i])-leaves, SIZE(G[i])-1));

	}

	printf("%d %d\n", res1, res2);

	return 0;
}
