#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include <climits>
#include <functional>
#define SIZE(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define REP(i,b) for(int i=0; i<(b); ++i)
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define FORD(i,a,b) for(int i=(a); i>=(b); --i)
#define NL printf("\n")
#define PB push_back
#define ST first
#define ND second

/*
*	MATEUSZ LAMECKI
*	XXII OLIMPIADA INFORMATYCZNA
*	II ETAP
*/

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int INF = 1000000007;
const int MAXN = 1000005;
int w[MAXN*8]; // ile kty kierowca może przejechać kilometrów
int n, m;
LL sum;

struct UpperTree {
	int *e, s;
	UpperTree(int size) {
		s = (1 << size);
		e = new int[2*s];
		REP(i,2*s) e[i] = 0;
	}
	~UpperTree() {
		delete[] e;
	}
	void insert(int x, int v) {
		x += s;
		while(x > 0) {
			e[x] += v;
			x /= 2;
		}
	}
	LL query(int a, int b) {
		LL ret = 0;
		a += s;
		b += s;
		while(a < b) {
			if(a&1) ret += e[a++];
			if(!(b&1)) ret += e[b--];
			a /= 2;
			b /= 2;
		}
		if(a == b) ret += e[a];
		return ret;
	};
	int lower(int x) {
		return (int)query(x,s-1);
	}
};

UpperTree tree(23);
UpperTree tree2(23);

inline void t(int x) { };

bool possible(int c, int s) {
	int d = tree.lower(s);
	if(d >= c) return true;
	LL r = tree2.query(1,s-1);
	if(r >= (c-d)*s) return true;
	return false;
}
pair<char,PII > P[MAXN];

int main() {
	t(scanf("%d %d", &n, &m));

	REP(i,m) {
		char tmp[5];
		scanf("%s", tmp);
		P[i].ST = tmp[0];
		scanf("%d %d", &P[i].ND.ST, &P[i].ND.ND);
	}

	REP(i,m) {
		if(P[i].ST == 'U') {
			int k = P[i].ND.ST, a = P[i].ND.ND;
			if(w[k] != 0) {
				tree.insert(w[k],-1);
				tree2.insert(w[k],-w[k]);
				sum -= w[k];
			}
			w[k] = a;
			tree.insert(a,1);
			tree2.insert(a,a);
		} else {
			int c = P[i].ND.ST, s = P[i].ND.ND;
			printf("%s\n", possible(c,s) ? "TAK" : "NIE");
		}
	}
	return 0;
}
