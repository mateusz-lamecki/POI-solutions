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
set<int> H[MAXN];
int p1[MAXN];
int p2[MAXN];
bool vis[MAXN];
vector<VI> res;
int n, m;

int main() {
	scanf("%d %d", &n, &m);

	FOR(i,1,n) p1[i] = p2[i] = 1;

	REP(i,m) {
		int a, b, s, t;
		scanf("%d %d %d %d", &a, &b, &s, &t);
		if(s == 0) s = -1;
		if(t == 0) t = -1;
		if(s != t) {
			H[a].insert(b);
			H[b].insert(a);			
		}
		p1[a] *= s;
		p1[b] *= s;
		p2[a] *= t;
		p2[b] *= t;
	}

	FOR(i,1,n) if(p1[i] != p2[i]) {
		printf("NIE\n");
		return 0;
	}


	FOR(i,1,n) {	
		VI S;
		S.PB(i);
		vis[i] = 1;
		while(!H[i].empty()) {
			int u = S.back();
			int v = *H[u].begin();
			H[u].erase(H[u].begin());
			H[v].erase(H[v].find(u));
			//printf("Usuwam (%d,%d)\n", u, v);
			S.PB(v);
			res.PB(VI());
			if(vis[v]) {
				//printf("Przeszukuję w S elementu %d\n", v);
				//FOREACH(it,S) printf(" %d", *it);
				//NL;

				res.back().PB(S.back());
				S.pop_back();

				while(!S.empty() && S.back() != v) {
					vis[S.back()] = 0;
					res.back().PB(S.back());
					S.pop_back();
				}

				res.back().PB(S.back());
			} else vis[v] = 1;
		}
	}

	int d = 0;
	FOREACH(it,res) if(!it->empty()) d++;

	printf("%d\n", d);
	FOREACH(it,res) if(!it->empty()) {
		printf("%d ", SIZE(*it)-1);
		FOREACH(itt,*it) printf("%d ", *itt);
		NL;
	}

	return 0;
}
