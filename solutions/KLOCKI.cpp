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

const int INF = 214748360;
const int MAXK = 1000005;
int a[MAXK];
int r[MAXK];
int k, p, q;
int n;

struct Block {
	int s, v;
	Block(int s, int v) : s(s), v(v) { }
	inline bool operator <(const Block& b) const {
		if(this->s == b.s) {
			if(this->v == q) return false;
			if(b.v == q) return true;
			return this->v < b.v;
		}
		return this->s < b.s;
	}
};

#define gc getchar_unlocked
#define pc putchar_unlocked

inline void read_int(int &x) {
	register int c = gc();
	x = 0;
	for(;(c<48 || c>57); c = gc());
	for(; c>47 && c<58; c = gc()) { x = (x<<1) + (x<<3) + c - 48; }
}

inline void write_int(int n) {
	int N = n, rev, count = 0;
	rev = N;
	if (N == 0) { pc('0'); pc('\n'); return ;}
	while ((rev % 10) == 0) { count++; rev /= 10;}
	rev = 0;
	while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}
	while (rev != 0) { pc(rev % 10 + '0'); rev /= 10;}
	while (count--) pc('0');
	pc(' ');
	return ;
}

int main() {
	read_int(k);
	read_int(p);
	read_int(q);
	REP(i,k) read_int(a[i]);
	REP(i,k) n += a[i];

	a[p-1]--;
	a[q-1]--;

	set<Block> S;
	REP(i,k) if(a[i]>0) S.insert(Block(a[i],i+1));

	r[0] = p;
	r[n-1] = q;

	int i = 1;
	while(!S.empty() && i<n-1) {
		set<Block>::iterator it = --S.end();
		int prev = (i>0) ? r[i-1] : 0;
		int next = (i<n-1) ? r[i+1] : 0;
		if((it->v == prev || it->v == next) && SIZE(S)>1) --it;
		Block u = *(it);
		S.erase(it);
		r[i] = u.v;
		if(u.s > 1) S.insert(Block(u.s-1,u.v));
		++i;
	}

	bool valid = 1;
	REP(i,n-1) if(r[i] == r[i+1]) valid = 0;

	a[p-1]++;
	a[q-1]++;
	REP(i,n) a[r[i]-1]--;

	REP(i,k) if(a[i]!=0) valid = 0;

	if(valid) REP(i,n) write_int(r[i]); //printf("%d ", r[i]);
	else putchar_unlocked('0');

	putchar_unlocked('\n');

	return 0;
}

