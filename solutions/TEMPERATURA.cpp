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
int x[MAXN];
int y[MAXN];
int n;

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d %d", &x[i], &y[i]);

	deque<int> P, Q;
	P.PB(1);
	Q.PB(1);

	int i = 1, j = 1;
	int res = 1;

	while(j <= n) {
		int pos = x[P.front()];

		/*printf("%d..%d, pos = %d\n", i, j, pos);
		FOREACH(it, P) printf(" %d", x[*it]); NL;
		FOREACH(it, Q) printf(" %d", y[*it]); NL;*/

		if(pos <= y[j+1]) {
			j++;
			while(!P.empty() && x[P.back()] <= x[j]) P.pop_back();
			while(!Q.empty() && y[Q.back()] >= y[j]) Q.pop_back();
			P.PB(j);
			Q.PB(j);
		} else {
			if(!P.empty() && P.front() == i) P.pop_front();
			if(!Q.empty() && Q.front() == i) Q.pop_front();
			i++;

			if(i > j) {
				j = i;
				while(!P.empty() && x[P.back()] <= x[j]) P.pop_back();
				while(!Q.empty() && y[Q.back()] >= y[j]) Q.pop_back();
				P.PB(j);
				Q.PB(j);
			}

		}

		if(j <= n) res = max(res, j-i+1);
	}
	
	printf("%d\n", res);

	return 0;
}
