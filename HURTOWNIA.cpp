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
const int MAXS = 1<<18;
int a[MAXN];
int b[MAXN];
int e[2*MAXS];
LL sm[2*MAXS];
int n;

void insert(int x, int v=1) {
	x += MAXS;
	while(x > 0) {
		e[x] += v;
		x /= 2;
	}
}

void insert_sum(int x, LL sum) {
	x += MAXS;
	while(x > 0) {
		sm[x] += sum;
		x /= 2;
	}
}

void divide(VI &X, int i, int j, int node, int a, int b) {
	if(a>b || a>j || b<i) return;
	if(a>=i && b<=j) {
		X.PB(node);
		return;
	}
	divide(X,i,j,node*2,a,(a+b)/2);
	divide(X,i,j,node*2+1,(a+b)/2+1,b);
}

int find(int x, int node) {
	if(node >= MAXS) return node-MAXS;
	if(e[node*2+1]) return find(x,node*2+1);
	return find(x,node*2);
}

LL sum(int a, int b) {
	a += MAXS;
	b += MAXS;
	LL res = 0;
	while(a < b) {
		if(a&1) res += sm[a++];
		if(!(b&1)) res += sm[b--];
		a /= 2;
		b /= 2;
	}
	if(a == b) res += sm[a];
	return res;
}

int greatest_nogreater(int x) {
	VI X;
	divide(X,1,x,1,0,MAXS-1);
	FORD(i,SIZE(X)-1,0) {
		int y = X[i];
		if(e[y] > 0) return find(x,y);
	}
	return 0;
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d", &a[i]);
	FOR(i,1,n) scanf("%d", &b[i]);

	FOR(i,1,n) if(a[i] > 0) insert(i);
	FOR(i,1,n) insert_sum(i,a[i]);

	vector<PII> V;
	FOR(i,1,n) V.PB(MP(b[i],i));

	sort(ALL(V));

	VI res;

	FOREACH(it,V) {
		if(sum(1,it->ND) >= it->ST) {
			res.PB(it->ND);
			int pos = it->ND;
			while(it->ST > 0) {
				pos = greatest_nogreater(pos);
				int v = sum(pos,pos);
				assert(v != 0);
				int diff = it->ST - max(0, it->ST-v);
				insert_sum(pos, -diff);
				it->ST -= diff;
				if(sum(pos,pos) == 0) insert(pos,-1);
			}
		}
	}

	sort(ALL(res));

	printf("%d\n", SIZE(res));
	FOREACH(it,res) printf("%d ", *it);
	NL;

	return 0;
}
