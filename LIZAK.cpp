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
const int MAXN = 2000005;
int res[MAXN][2];
char w[MAXN];
int n, m;

int get_value(char x) {
	if(x == 'W') return 1;
	return 2;
}

void mem(int a, int b, int sum) {
	int len = b-a+1;
	if(len < 1) return;

	if(res[sum][0] == INF) {
		res[sum][0] = a+1;
		res[sum][1] = b+1;
	}
	if(len < 2) return;

	if(w[a] == 'T') mem(a+1, b, sum-2);
	else if(w[b] == 'T') mem(a, b-1, sum-2);
	else mem(a+1, b-1, sum-2);
}

int get_sum(int a, int b) {
	int ret = 0;
	FOR(i,a,b) ret += get_value(w[i]);
	return ret;
}

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", w);

	REP(i,MAXN) res[i][0] = res[i][1] = INF;

	int sum = 0;
	REP(i,n) sum += get_value(w[i]);

	mem(0,n-1,sum);

	int a = 0, b = n-1;
	REP(i,n) if(w[i] == 'W') {
		a = i+1;
		break;
	}
	FORD(i,n-1,0) if(w[i] == 'W') {
		b = i-1;
		break;
	}

	if(n-a >= b+1) mem(a,n-1,get_sum(a,n-1));
	else mem(0,b,get_sum(0,b));

	REP(i,m) {
		int k;
		scanf("%d", &k);
		if(res[k][0] != INF) printf("%d %d\n", res[k][0], res[k][1]);
		else printf("NIE\n");
	}

	return 0;
}
