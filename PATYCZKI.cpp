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
const int MAXK = 55;
int last[MAXK];

int main() {
	vector<PII> P;

	int k;
	scanf("%d", &k);
	FOR(i,1,k) {
		int n;
		scanf("%d", &n);
		REP(j,n) {
			int x;
			scanf("%d", &x);
			P.PB(MP(x,i));
		}
	}

	sort(ALL(P));

	set<PII> S;

	REP(i,SIZE(P)) {
		PII v(last[P[i].ND], P[i].ND);
		if(S.find(v) != S.end()) S.erase(S.find(v));

		S.insert(P[i]);
		if(SIZE(S) > 3) S.erase(S.begin());

		if(SIZE(S) == 3) {
			set<PII> T = S;
			PII a = *T.begin();
			T.erase(T.begin());
			PII b = *T.begin();
			T.erase(T.begin());
			PII c = *T.begin();
			T.erase(T.begin());
			if(a.ST + b.ST > c.ST) {
				printf("%d %d %d %d %d %d\n", a.ND, a.ST, b.ND, b.ST, c.ND, c.ST);
				return 0;
			}
		}

		last[P[i].ND] = P[i].ST;
	}

	//FOREACH(it,P) printf("(%d,%d) ", it->ST, it->ND);
	//NL;
	
	printf("NIE\n");

	return 0;
}
