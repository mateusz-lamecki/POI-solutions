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
int p[MAXN];
int h[MAXN];
int n;

int get_hash(int a, int b) {
	return h[b] - h[a-1]*p[b-a+1];
}

bool valid(int p) {
	int q = get_hash(1,p);
	int last = p;
	FOR(i,1,n) {
		if(i+p-1 > n) break;
		if(get_hash(i,i+p-1) == q) {
			last = i+p-1;
		}
		if(last < i) return false;
	}
	return true;
}

int main() {
	scanf("%s", s+1);
	n = strlen(s+1);
	
	p[0] = 1;
	FOR(i,1,n) p[i] = p[i-1] * MOD;

	FOR(i,1,n) h[i] = h[i-1] * MOD + s[i];

	VI p(n+1);
	int t = 0;

	FOR(i,2,n) {
		while(t>0 && s[t+1] != s[i]) t = p[t];
		if(s[t+1] == s[i]) t++;
		p[i] = t;
	}

	VI q;
	t = n;
	while(t > 0) {
		q.PB(t);
		t = p[t];
	}

	reverse(ALL(q));

	int res = n;
	int e = q[0];

	while(true) {
		VI::iterator it = lower_bound(ALL(q),e);
		int pos = it-q.begin();
		if(pos == SIZE(q)) break;
		if(valid(*it)) {
			res = *it;
			break;
		} else e *= 2;
	}

	printf("%d\n", res);


	return 0;
}
