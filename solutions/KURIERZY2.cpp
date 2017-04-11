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

struct Node {
	int v, c;
	Node(int v=0, int c=0) : v(v), c(c) { }
	Node operator +(const Node& b) {
		if(this->v != b.v && this->c - b.c == 0) return Node(0,0);
		if(this->v == b.v) return Node(this->v,this->c + b.c);
		if(this->c > b.c) return Node(this->v, this->c - b.c);
		else return Node(b.v, b.c - this->c);
	}
};

const int INF = 214748360;
const int MAXN = 500005;
int p[MAXN];
Node t[1<<20];
map<int,int> R[MAXN];
int n, m;
int s;

void build_tree() {
	int u = s / 2;
	while(u>=1) {
		FOR(i,u,2*u-1) t[i] = t[2*i] + t[2*i+1];
		u /= 2;
	}
}

void search(VI& A, int i, int j, int node=1, int a=0, int b=s-1) {
	if(a>b || a>j || b<i) return;

	//printf("search(%d, %d, %d, %d, %d)\n", i, j, node, a, b);

	if(a>=i && b<=j) {
		A.PB(node);
		return;
	}
	search(A, i, j, node*2, a, (a+b)/2);
	search(A, i, j, node*2+1, 1+(a+b)/2, b);
}

vector<Node> find_nodes(int i, int j) {
	if(i==j) {
		vector<Node> ret;
		ret.PB(t[s+i]);
		return ret;
	}
	VI nodes;
	search(nodes,i,j);
	//for(int x: nodes) printf("%d ", x); NL;
	vector<Node> ret;
	REP(i,SIZE(nodes)) ret.PB(t[nodes[i]]);
	return ret;
}

bool valid(int i, int j, int x) {
	map<int,int>::iterator it1 = R[x].lower_bound(i);
	map<int,int>::iterator it2 = R[x].upper_bound(j);
	//if(it1 == R[x].end()) return false;
	//printf("Sprawdzam, i = %d, j = %d, x = %d\n", i, j, x);
	if(R[x].empty()) return false;
	--it2;
	int hm = it2->ND - it1->ND + 1;
	//printf("%d: dla przedziaÅ‚u (%d,%d) iloÅ›Ä‡: %d\n", x, i, j, hm);
	int dis = (j-i+1);
	if(hm*2 > dis) return true;
	return false;
}


int main() {
	scanf("%d%d", &n, &m);
	REP(i,n) scanf("%d", &p[i]);

	s = 1;
	while(s <= n) s *= 2;

	REP(i,n) t[i+s] = Node(p[i],1);
	REP(i,n) R[p[i]].insert(MP(i,SIZE(R[p[i]])));


	build_tree();

	/*REP(i,2*s) {
		printf("%d:%d ", t[i].v, t[i].c);
		if(((i+1)&(i))==0) NL;
	}*/

	REP(i,m) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a; --b;
		vector<Node> r = find_nodes(a,b);
		//for(Node x: r) printf("(%d,%d) ", x.v, x.c); NL;
		Node w = r.front();
		FOR(i,1,SIZE(r)-1) w = w + r[i];
		//printf("Kandydat na lidera: (%d,%d)\n", w.v, w.c);
		printf("%d\n", valid(a,b,w.v) ? w.v : 0);
		//NL;NL;
	}

	//for(Node x: find_nodes(1,3)) printf("(%d,%d) ", x.v, x.c); NL;

	/*REP(i,n+1) {
		for(auto x: R[i]) printf("%d:%d ", x.ST, x.ND);
		NL;
	}*/

	return 0;
}
