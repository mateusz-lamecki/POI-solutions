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
const int MAXN = 205;
VI g[MAXN];
char x[MAXN];
int hsh1[MAXN];
int hsh2[MAXN];
int dp[MAXN];
int who[MAXN];
bool vis[MAXN];
int p[MAXN];
int n;

int get_hash(int *hsh, int a, int b) {
	int len = b-a+1;
	return hsh[b] - (a ? hsh[a-1]*p[len] : 0);
}

bool is_palindrome(int a, int b) {
	return get_hash(hsh1,a,b) == get_hash(hsh2,n-b+1,n-a+1);
}

int main() {
	scanf("%s", x+1);
	n = strlen(x+1);

	p[0] = 1;
	FOR(i,1,MAXN-1) p[i] = p[i-1] * MOD;

	hsh1[1] = x[1];
	FOR(i,2,n) hsh1[i] = hsh1[i-1] * MOD + x[i];
	hsh2[1] = x[n];
	FOR(i,2,n) hsh2[i] = hsh2[i-1] * MOD + x[n-i+1];

	FOR(i,1,n) FOR(j,i,n) if(is_palindrome(i,j) && (j-i+1)%2==0) g[i].PB(j+1);

	bool res = 1;

	vector<PII> res1;
	vector<PII> res2;

	int t = 1;
	while(t < n) {
		sort(ALL(g[t]));
		if(g[t].empty()) {
			res = 0;
			break;
		}
		//printf("1: %d..%d\n", t, g[t].front()-1);
		res1.PB(MP(t,g[t].front()-1));
		t = g[t].front();
	}

	if(res && n%2==0) {
		FOR(i,1,n+1) dp[i] = INF;
		queue<int> Q;
		Q.push(1);
		vis[1] = 1;
		dp[1] = 0;
		while(!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = 1;
			FOREACH(it,g[u]) {
				if(dp[*it] >= dp[u]+1) {
					who[*it] = u;
					dp[*it] = dp[u]+1;
				}
				if(!vis[*it]) {
					vis[*it] = 1;
					Q.push(*it);
				}
			}
		}

		int t = n+1;
		while(t > 1) {
			res2.PB(MP(who[t],t-1));
			//printf("2: %d..%d\n", who[t], t-1);
			t = who[t];
		}
		reverse(ALL(res2));

		FOREACH(it,res2) {
			FOR(i,it->ST, it->ND) printf("%c", x[i]);
			if(*it != res2.back()) printf(" ");
		}
		NL;

		FOREACH(it,res1) {
			FOR(i,it->ST, it->ND) printf("%c", x[i]);
			if(*it != res1.back()) printf(" ");
		}
		NL;
	} else {
		printf("NIE\n");
	}

	return 0;
}
