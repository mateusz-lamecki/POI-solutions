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
const int MAXN = 3000005;
int a[MAXN];

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	FOR(i,1,q) scanf("%d", &a[i]);

	deque<int> D, E;

	int i = 1, j = 1;
	int res = 0;

	while(j <= q) {
		if(!D.empty() && D.front() == i-1) D.pop_front();
		if(!E.empty() && E.front() == i-1) E.pop_front();

		while(!D.empty() && a[D.back()] <= a[j]) D.pop_back();
		while(!E.empty() && a[E.back()] >= a[j]) E.pop_back();

		D.PB(j);
		E.PB(j);

		int mx = a[D.front()];
		int mn = a[E.front()];

		if(mx-mn <= n) {
			res = max(res, j-i+1);
			j++;
		} else {
			i++;
			if(i > j) j = i;
		}
	}

	printf("%d\n", res);

	return 0;
}
