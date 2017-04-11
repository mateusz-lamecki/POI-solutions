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
const int MAXN = 1<<19;

struct Point {
	int count;
	Point *left;
	Point *right;
};

struct DynamicTree {
	Point *root;
	int size;

	DynamicTree() {
		root = new Point();
		size = 0;
	}
	~DynamicTree() {
		destroy(root);
	}
	void insert(int c) {
		int u = 1, v = MAXN;
		Point *x = root;
		x->count++;
		while(u != v) {
			if(c <= (u+v)/2) {
				if(x->left == NULL) x->left = new Point();
				x = x->left;
				v = (u+v)/2;
			} else {
				if(x->right == NULL) x->right = new Point();
				x = x->right;
				u = (u+v)/2 + 1;
			}
			x->count++;
		}
		size++;
	}
	// O(lg n)
	int query(int c) {
		int ret = 0;
		dfs(root, c, ret);
		return ret;
	}
	void dfs(Point* x, int c, int &res, int u=1, int v=MAXN) {
		if(u >= c) {
			res += x->count;
			return;
		}
		if(x->left!=NULL && c<=(u+v)/2) dfs(x->left,c,res,u,(u+v)/2);
		if(x->right!=NULL) dfs(x->right,c,res,(u+v)/2+1,v);

	}
	// O(n lg n)
	VI get_nodes() {
		Point *x = root;
		VI ret;
		find_nodes(ret, x, 1, MAXN);
		return ret;
	}
	void find_nodes(VI& A, Point* x, int u, int v) {
		if(x->left == NULL && x->right == NULL) {
			REP(i,x->count) A.PB(u);
		}
		else {
			if(x->left != NULL) find_nodes(A, x->left, u, (u+v)/2);
			if(x->right != NULL) find_nodes(A, x->right, (u+v)/2+1, v);
		}
	}
	// O(n lg n)
	void destroy(Point *x) {
		if(x != NULL) {
			destroy(x->left);
			destroy(x->right);
			delete x;
		}
	}
};
DynamicTree *t[MAXN];
VI g[MAXN];
int v[MAXN];
int p, n;
LL res;

void read() {
	int x;
	scanf("%d", &x);
	if(x != 0) v[p] = x;
	const int e = p;
	p++;
	if(x == 0) {
		g[e].PB(p);
		read();
		g[e].PB(p);
		read();
	}
}

void dfs(int x) {
	if(g[x].empty()) {
		t[x] = new DynamicTree();
		t[x]->insert(v[x]);
	} else {
		int u = g[x][0];
		int v = g[x][1];

		dfs(u);
		dfs(v);

		DynamicTree *a = (t[u]->size<=t[v]->size) ? t[u] : t[v];
		DynamicTree *b = (t[u]->size>t[v]->size) ? t[u] : t[v];

		bool e = (t[u]->size > t[v]->size);
		LL inv = 0;

		VI p = a->get_nodes();
		REP(i,SIZE(p)) {
			int w = b->query(p[i]);
			if(!e) w = b->size - w;
			inv += w;
		}

		inv = min(inv, LL(t[u]->size)*LL(t[v]->size) - inv);

		res += inv;

		REP(i,SIZE(p)) b->insert(p[i]);
		t[x] = b;

		a->destroy(a->root);
	}


}

int main() {
	scanf("%d", &n);

	read();
	dfs(0);

	printf("%lld\n", res);

	return 0;
}
