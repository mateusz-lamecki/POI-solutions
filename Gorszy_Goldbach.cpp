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
const int MAXM = 1185961131;
const int MAXN = 1000005;
vector<pair<PII,int> > S;
VI d[50];
int n;

bool is_prime(int x) {
	if(x == 0) return true;
	if(x % 2 == 0) return false;
	for(int i=3; i*i<=x; i+=2) if(x%i==0) return false;
	return true;
}

int find_prime(int x) {
	FORD(i,x,2) if(is_prime(i)) return i;
	return 0;
}

VI get_result(int x) {
	VI ret;
	FORD(i,SIZE(S)-1,0) {
		if(x > 46 && S[i].ST.ST <= x && S[i].ST.ND >= x) {
			ret.PB(S[i].ND);
			x -= S[i].ND;
		}
	}
	FOREACH(it,d[x]) ret.PB(*it);
	return ret;
}

int main() {
	VI p;
	int arr[] = { 3, 5, 7, 11, 13, 17 };
	REP(i,6) p.PB(arr[i]);
	int s = 1 << SIZE(p);
	REP(i,s) {
		VI v;
		int bitmask = i;
		int pos = SIZE(p)-1;
		while(bitmask > 0) {
			if((bitmask&1)==1) {
				v.PB(p[pos]);
			}
			bitmask >>= 1;
			pos--;
		}
		int sum = 0;
		FOREACH(it,v) sum += *it;
		if(sum >= 10 && sum <= 46) d[sum] = v;
	}

	S.PB(MP(MP(10,46),17));

	while(S.back().ST.ND < MAXM) {
		int v = S.back().ST.ND;
		int u = find_prime(v-9);
		S.PB(MP(MP(v+1, v+u), u));
	}

	S.PB(MP(MP(S.back().ST.ND+1, 2000000000), find_prime(S.back().ST.ND-9)));

	scanf("%d", &n);
	REP(i,n) {
		int x;
		scanf("%d", &x);
		VI res = get_result(x);
		sort(ALL(res));
		printf("%d\n", SIZE(res));
		FOREACH(it,res) printf("%d ", *it);
		NL;
	}

	return 0;
}
