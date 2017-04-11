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
#include <unordered_set>
#include <unordered_map>
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
const int MAXN = 2005;
int a[MAXN];
int f[MAXN];
int n;

void p_print(int x, int y) {
	if(x > 0) printf("%d%c ", x, 'a'+y);
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &a[i]);
	FOR(i,1,n) f[a[i]] = i;

	int inv = 0;
	FOR(i,1,n) FOR(j,1,n-1) if(a[j] > a[i]) inv++;

	bool sorted = 1;
	FOR(i,1,n) if(a[i] != i) sorted = 0;

	if(sorted) {
		printf("0\n");
		return 0;
	}

	if(n%2 && inv%2) {
		printf("NIE DA SIE\n");
		return 0;
	}

	FOR(i,1,n-2) {
		printf("i = %d, f[i] = %d\n", i, f[i]);
		if(f[i]-i >= 2) {
			REP(i,(f[i]-i)/2) {
				p_print(n-f[i]-1,0);
				p_print(2,1);
				p_print(f[i]-2,0);
			}
		} else if(f[i]-i == 1) {
			p_print(n-f[i]-1,0);
			p_print(1,1);
			p_print(f[i]-2,0);
		}
	}

	if(f[n-1] > f[n]) {
		p_print(1,0);
		p_print(2,1);
		REP(i,(n-4)/2) {
			p_print(n-2,0);
			p_print(2,1);
		}
		p_print(n-4,0);
	}

	return 0;
}
