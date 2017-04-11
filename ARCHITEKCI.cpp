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
deque<int> res;

int inicjuj() {
	res.PB(12);
	res.PB(5);
	res.PB(8);
	res.PB(3);
	res.PB(15);
	res.PB(8);
	res.PB(0);
	return 3;

}

int wczytaj() {
	int u = res.front();
	res.pop_front();
	return u;
}

int main() {
	int k = inicjuj();

	set<PII> S;
	set<PII> T;

	FOR(i,1,k) {
		int x = wczytaj();
		S.insert(MP(x,i));
		T.insert(MP(i,x));
	}

	int i = k;
	while(true) {
		int x = wczytaj();
		if(x == 0) break;
		++i;

		PII u = *S.begin();

		if(u.ND < (--T.end())->ST) {
			S.erase(S.find(u));
			T.erase(T.find(MP(u.ND,u.ST)));

			S.insert(MP(x,i));
			T.insert(MP(i,x));
		} else if(x >= u.ST) {
			S.erase(S.find(u));
			T.erase(T.find(MP(u.ND,u.ST)));
			S.insert(MP(x,i));
			T.insert(MP(i,x));
		}

	}

	FOREACH(it,T) printf("%d ", it->ND);
	NL;

	return 0;
}
