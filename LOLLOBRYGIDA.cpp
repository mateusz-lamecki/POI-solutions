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

const int INF = 214748360;
const int MAXN = 1000005;
int d;

inline int f(int x) {
	if(x%2==0) return x;
	return x+1;
}

int main() {
	scanf("%d", &d);
	REP(i,d) {
		int n;
		scanf("%d", &n);
		VI h(n);
		REP(i,n) scanf("%d", &h[i]);

		int leader = h[0], p = 1;
		FOR(i,1,n-1) {
			if(p>0) {
				if(h[i] == leader) p++;
				else p--;
			} else {
				p++;
				leader = h[i];
			}
		}
		
		int hm = 0;
		REP(i,n) if(h[i] == leader) hm++;

		bool smaller = false, greater = false;

		REP(i,n) {
			if(h[i] < leader) smaller = true;
			if(h[i] > leader) greater = true;
		}

		//printf("p = %d, leader = %d, hm = %d\n", p, leader, hm);

		printf("%s\n", (hm <= n/2 || ((hm == n/2+1 && n%2==1 && !(smaller && greater)))) ? "TAK" : "NIE");
	}
	return 0;
}
