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
VI B[2], S[2], C[2];
int sumB[MAXN], sumS[MAXN], sumC[MAXN];
char s[MAXN];
int n;

int calc(int *A, int a, int b) {
	return A[b] - A[a-1];
}

int main() {
	scanf("%d", &n);
	scanf("%s", s+1);

	int lo = 1, hi = n;
	FOR(i,1,n-2) {
		vector<char> o;
		REP(j,3) o.PB(s[i+j]);
		sort(ALL(o));
		if(o[0] == 'B' && o[1] == 'C' && o[2] == 'S') lo = i+3;
		else break;
	}

	FORD(i,n,3) {
		vector<char> o;
		REP(j,3) o.PB(s[i-j]);
		sort(ALL(o));
		if(o[0] == 'B' && o[1] == 'C' && o[2] == 'S') hi = i-3;
		else break;
	}

	printf("%d %d\n", lo, hi);

	FOR(i,lo,hi) if(s[i] == 'B') {
		B[0].PB(i);
		if(SIZE(B[0]) == 3) break;
	}
	FOR(i,lo,hi) if(s[i] == 'S') {
		S[0].PB(i);
		if(SIZE(S[0]) == 3) break;
	}
	FOR(i,lo,hi) if(s[i] == 'C') {
		C[0].PB(i);
		if(SIZE(C[0]) == 3) break;
	}

	FORD(i,hi,lo) if(s[i] == 'B') {
		B[1].PB(i);
		if(SIZE(B[1]) == 3) break;
	}
	FORD(i,hi,lo) if(s[i] == 'S') {
		S[1].PB(i);
		if(SIZE(S[1]) == 3) break;
	}
	FORD(i,hi,lo) if(s[i] == 'C') {
		C[1].PB(i);
		if(SIZE(C[1]) == 3) break;
	}

	FOR(i,lo,hi) {
		sumB[i] = sumB[i-1];
		sumS[i] = sumS[i-1];
		sumC[i] = sumC[i-1];
		if(s[i] == 'B') sumB[i]++;
		if(s[i] == 'S') sumS[i]++;
		if(s[i] == 'C') sumC[i]++;
	}

	VI P, Q;
	FOREACH(it,B[0]) P.PB(*it);
	FOREACH(it,S[0]) P.PB(*it);
	FOREACH(it,C[0]) P.PB(*it);
	FOREACH(it,B[1]) Q.PB(*it);
	FOREACH(it,S[1]) Q.PB(*it);
	FOREACH(it,C[1]) Q.PB(*it);

	int res = 0;

	FOREACH(it,P) FOREACH(jt,Q) if(*it <= *jt) {
		VI t;
		t.PB(calc(sumB,*it,*jt));
		t.PB(calc(sumS,*it,*jt));
		t.PB(calc(sumC,*it,*jt));

		sort(ALL(t));
		while(t.front() == 0) t.erase(t.begin());

		int p = SIZE(t);
		t.erase(unique(ALL(t)), t.end());

		if(p == SIZE(t)) {
			res = max(res, *jt-*it+1);
		}
	}

	res = max(res, 1);

	printf("%d\n", res);


	return 0;
}
