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
const int MAXN = 1000005;
int l[MAXN], c[MAXN];
int ll[MAXN];
int a[MAXN];
int n, m;

#define gc getchar_unlocked
int readInt() {
	char c = gc();
	while(c<'0' || c>'9') c = gc();
	int ret = 0;
	while(c>='0' && c<='9') {
		ret = 10*ret + c - 48;
		c = gc();
	}
	return ret;
}

int main() {
	scanf("%d %d", &n, &m);
	FOR(i,1,m) ll[i] = readInt();
	FOR(i,1,m) c[i] = readInt();
	FOR(i,1,m) l[c[i]] = ll[i];

	FOR(i,1,n) a[i] = readInt();

	LL k = 0;
	FOR(i,1,n) k += l[i];

	if(k > n) {
		printf("0\n");
		return 0;
	}

	int rem = k;
	int res = 0;

	FOR(i,1,k) {
		if(l[a[i]] > 0) rem--;
		else rem++;
		l[a[i]]--;
	}

	FOR(i,1,n-k+1) {
		if(i > 1) {
			if(l[a[i-1]] < 0) rem--;
			else rem++;
			l[a[i-1]]++;
		}

		if(rem == 0) res++;

		if(l[a[i+k]] > 0) rem--;
		else rem++;
		l[a[i+k]]--;
	}
	
	printf("%d\n", res);
	
	return 0;
}
