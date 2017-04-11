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
const int MAXN = 500005;
char s[MAXN];
char r[MAXN];
int p[MAXN];
int h1[MAXN];
int h2[MAXN];
int n;

int get_hash1(int a, int b) {
	if(a > b) return 0;
	int len = b-a+1;
	return h1[b] - h1[a-1]*p[len];
}

int get_hash2(int a, int b) {
	if(a > b) return 0;
	a = n-a+1;
	b = n-b+1;
	if(a > b) swap(a,b);
	int len = b-a+1;
	return h2[b] - h2[a-1]*p[len];
}

int main() {
	scanf("%d", &n);
	scanf("%s", s+1);

	FOR(i,1,n) r[i] = (s[i]=='0') ? '1' : '0';

	p[0] = 1;
	FOR(i,1,MAXN-1) p[i] = p[i-1] * MOD;

	FOR(i,1,n) h1[i] = h1[i-1] * MOD + s[i];
	FOR(i,1,n) h2[i] = h2[i-1] * MOD + r[n-i+1];

	LL res = 0;

	FOR(i,2,n) {
		int lo = 0, hi = min(n-i,i-1);
		int longest = 0;
		//printf("Sprawdzam w i=%d\n", i);
		while(lo <= hi) {
			int mid = lo+(hi-lo)/2;
			//printf(" [%d..%d] %d %d\n", i-mid-1, i+mid, get_hash1(i-mid-1,i+mid), get_hash2(i-mid-1,i+mid));
			if(get_hash1(i-mid-1,i+mid) == get_hash2(i-mid-1,i+mid)) {
				longest = 2*mid+2;
				lo = mid+1;
			} else {
				hi = mid-1;
			}
		}
		//printf(" Najdłuższy antypalindrom: %d\n", longest);
		res += longest/2;
	}

	printf("%lld\n", res);

	return 0;
}
