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

struct SumTree {
	LL *e, s;
	SumTree(int size) {
		s = (1 << size);
		e = new LL[2*s];
		REP(i,2*s) e[i] = 0;
	}
	~SumTree() {
		delete[] e;
	}
	void insert(int x, int v) {
		x += s;
		while(x > 0) {
			e[x] += v;
			x /= 2;
		}
	}
	LL sum(int a, int b) {
		a += s;
		b += s;
		LL res = 0;
		while(a < b) {
			if(a&1) res += e[a++];
			if(!(b&1)) res += e[b--];
			a /= 2;
			b /= 2;
		}
		if(a == b) res += e[a];
		return res;
	}
	int query(int x) {
		return sum(x,s-1);
	}
};

const int INF = 2147483640;
const int MAXN = 1000005;
vector<pair<char,PII> > T;
map<LL,LL> H;
map<LL,LL> R;
int dis[MAXN];
int n, m;

void scan(int &x) {
#define gc getchar_unlocked
	x = 0;
	char c = gc();
	while(c < '0' || c > '9') c = gc();
	while(c >= '0' && c <= '9') {
		x = 10*x + c - '0';
		c = gc();
	}
}

void read() {
	VI S;
	REP(i,m) {
		char s[5];
		int a, b;
		scanf("%s", s);
		scan(a);
		scan(b);
		T.PB(MP(s[0],MP(a,b)));
		S.PB(b);
	}
	sort(ALL(S));
	int t = 1;
	FOREACH(it,S) {
		H[*it] = t;
		R[t] = *it;
		++t;
	}
	REP(i,m) T[i].ND.ND = H[T[i].ND.ND];
}

int main() {
	scan(n);
	scan(m);
	read();

	SumTree sum_tree(20);
	SumTree dis_tree(20);

	REP(i,MAXN) dis[i] = INT_MAX;
	int available = 0;

	REP(i,m) {
		char s = T[i].ST;
		int p = T[i].ND.ST;
		int q = T[i].ND.ND;
		if(s == 'U') {
			if(dis[p] != INT_MAX) {
				sum_tree.insert(dis[p],-1);
				dis_tree.insert(dis[p],-R[dis[p]]);
			} else available++;
			dis[p] = q;
			sum_tree.insert(dis[p],1);
			dis_tree.insert(dis[p],R[dis[p]]);
		} else {
			int t = sum_tree.query(q);
			int rem = max(0,p-t);
			if(rem && dis_tree.sum(0,q-1)/rem >= R[q]) {
				rem = 0;
			}
			printf("%s\n", rem==0 ? "TAK" : "NIE");
		}
	}

	return 0;
}
