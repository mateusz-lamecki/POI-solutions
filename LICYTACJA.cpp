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

const int INF = 2147483640;
const int MAXN = 1000007;
const int MOD = 349409;
vector<pair<PII,int> > H[MOD];
PII h[MAXN];
VI g[MAXN];
bool vis[MAXN];
bool win[MAXN];
int e[MAXN];
VI post;
int r;
int n;

int inicjuj() {
	return 3;
}

void alojzy(int x) {
}

int bajtazar() {
	return 2;
}

int get_hash(PII x) {
	return (x.ST*MOD + x.ND) % MOD;
}

int get_value(PII x) {
	FOREACH(it,H[get_hash(x)]) {
		if(it->ST == x) return it->ND;
	}
	return -1;
}

void insert(PII x, int v) {
	if(get_value(x) != -1) return;
	H[get_hash(x)].PB(MP(x,v));
}

bool is(PII x) {
	return get_value(x) != -1;
}


void build(int x, int y) {
	insert(MP(x,y),r);

	const int e = r;
	h[r] = MP(x,y);
	r++;

	if(x<n) {
		if(!is(MP(x+y,1))) build(x+y,1);
		g[e].PB(get_value(MP(x+y,1)));
	}

	if(x+y<n) {
		if(!is(MP(x,2*y))) build(x,2*y);
		g[e].PB(get_value(MP(x,2*y)));
	}

	if(x+y<n) {
		if(!is(MP(x,3*y))) build(x,3*y);
		g[e].PB(get_value(MP(x,3*y)));
	}
}

void topo(int x) {
	vis[x] = 1;
	FOREACH(it,g[x]) if(!vis[*it]) topo(*it);
	post.PB(x);
}

string pt(PII x) {
	return "("+to_string(x.ST)+","+to_string(x.ND)+")";
}

int main() {
	n = inicjuj();

	build(0,1);
	topo(0);

	FOREACH(it,post) {
		if(g[*it].empty()) win[*it] = 1;
		else {
			int winning = 0, losing = 0;
			FOREACH(itt,g[*it]) {
				if(win[*itt]) winning++;
				else losing++;
			}
			if(losing > 0) win[*it] = 1;
			if(winning == SIZE(g[*it])) win[*it] = 0;
		}
		if(h[*it].ST + h[*it].ND >= n) win[*it] = 1;
	}

	REP(i,r) {
		printf("%s %s\n", pt(h[i]).c_str(), win[i] ? "wygrywająca" : "przegrywająca");
	}

	PII pos(0,1);
	while(!g[get_value(pos)].empty()) {
		int d = get_value(pos);

		if(pos.ST+pos.ND >= n) {
			alojzy(1);
			break;
		}

		int res = 1;
		FOREACH(it,g[d]) if(win[*it]) {
			PII c = h[*it];
			if(c == MP(pos.ST+pos.ND,1)) {
				res = 1;
			}
			if(c == MP(pos.ST,2*pos.ND)) {
				res = 2;
			}
			if(c == MP(pos.ST,3*pos.ND)) {
				res = 3;
			}
			break;
		}

		if(res == 1) pos = MP(pos.ST+pos.ND,1);
		else if(res == 2) pos = MP(pos.ST,2*pos.ND);
		else if(res == 3) pos = MP(pos.ST,3*pos.ND);

		alojzy(res);


		if(pos.ST+pos.ND >= n) {
			bajtazar();
			break;
		}

		int e = bajtazar();
		if(e == 1) pos = MP(pos.ST+pos.ND,1);
		else if(e == 2) pos = MP(pos.ST,2*pos.ND);
		else if(e == 3) pos = MP(pos.ST,3*pos.ND);
	}

	return 0;
}
