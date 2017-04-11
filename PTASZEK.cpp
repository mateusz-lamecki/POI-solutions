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
int d[MAXN];
int w[MAXN];
int n, q;

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &d[i]);

	scanf("%d", &q);
	REP(i,q) {
		int k;
		scanf("%d", &k);

		deque<int> A, B;
		A.PB(1);
		w[1] = 0;

		FOR(i,2,n) {
			if(!A.empty() && A.front() == i-k-1) A.pop_front();
			if(!B.empty() && B.front() == i-k-1) B.pop_front();

			if(A.empty()) {
				FOREACH(it,B) A.PB(*it);
				B.clear();
			}

			if(d[A.front()] > d[i]) {
				w[i] = w[A.front()];
				while(!A.empty() && d[A.back()] <= d[i]) A.pop_back();
				A.PB(i);
			} else {
				w[i] = w[A.front()] + 1;
				while(!B.empty() && d[B.back()] <= d[i]) B.pop_back();
				B.PB(i);
			}
		}

		printf("%d\n", w[n]);
	}

	return 0;
}
