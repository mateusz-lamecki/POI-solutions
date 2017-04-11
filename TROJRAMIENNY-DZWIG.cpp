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

struct Answer {
	int x, y, z;
	Answer(int x, int y, int z) : x(x), y(y), z(z) { };
};

const int INF = 214748360;
const int MAXN = 1000005;
vector<Answer> answers;
bool d[MAXN];
int p, q, n;

bool f(int x) {
	//return (W.find(x) != W.end());
	return d[x];
}

int main() {
	scanf("%d %d %d", &p, &q, &n);
	if(p>q) swap(p,q);

	int u = 0;

	FOR(i,1,n) {
		if(u >= n) break;
		if(!f(i) && !f(i+p) && !f(i+p+q)) {
			//printf("%d %d %d\n", i, i+p, i+p+q);
			answers.PB(Answer(i,i+p,i+p+q));
			u++;
			if(i+p <= n) u++;
			if(i+p+q <= n) u++;
			d[i] = d[i+p] = d[i+p+q] = 1;
		} else if(!f(i) && !f(i+q) && !f(i+p+q)) {
			//printf("%d %d %d\n", i, i+q, i+p+q);
			answers.PB(Answer(i,i+q,i+p+q));
			u++;
			if(i+q <= n) u++;
			if(i+p+q <= n) u++;
			d[i] = d[i+q] = d[i+p+q] = 1;
		}
	}

	printf("%d\n", SIZE(answers));
	REP(i,SIZE(answers)) {
		printf("%d %d %d\n", answers[i].x, answers[i].y, answers[i].z);
	}

	return 0;
}
