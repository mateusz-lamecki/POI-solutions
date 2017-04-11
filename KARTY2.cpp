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
#include <unordered_set>
#include <unordered_map>
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
	PII x, y;
	Node() {};
	Node(PII x, PII y) {
		this->x = x;
		this->y = y;
		if(x.ST > x.ND) swap(x.ST, x.ND);
		if(y.ST > y.ND) swap(y.ST, y.ND);
	}
	void set(Node a, Node b) {
		
	}
};

const int INF = 2147483640;
const int MAXN = 1000005;
const int SIZE = (1 << 3);
vector<Node> tree(2*SIZE);
int x[MAXN];
int y[MAXN];
int n, m;

void update(int u) {
	u += SIZE;
	u /= 2;
	while(u > 0) {
		Node x = tree[2*u];
		Node y = tree[2*u+1];

		Node p;
		if(x.x.ND <= y.x.ST) p.x = MP(x.x.ST, min(y.x.ND, y.y.ND));
		if(x.y.ND <= y.x.ST) p.y = MP(x.y.ST, min(y.x.ND, y.y.ND));

		tree[u] = p;
		u /= 2;
	}
}

void tprint() {
	FOR(i,1,2*SIZE-1) {
		if((i&(i-1))==0) printf("\n");
		printf("(%d,%d):(%d,%d) ", tree[i].x.ST, tree[i].x.ND, tree[i].y.ST, tree[i].y.ND);
	}
}

int main() {
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d %d", &x[i], &y[i]);

	FOR(i,1,n) tree[i+SIZE] = Node(MP(x[i],y[i]), MP(x[i],y[i]));
	FOR(i,1,n) update(i);

	tprint();

	scanf("%d", &m);
	REP(i,m) {
		int a, b;
		scanf("%d %d", &a, &b);
	}
	return 0;
}
