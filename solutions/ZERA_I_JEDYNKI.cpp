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

string bfs(LL n) {
	if(n == 1) return "1";

	queue<pair<string,LL> > Q;
	Q.push(MP("1",1));

	while(!Q.empty()) {
		pair<string,LL> u = Q.front();
		Q.pop();
		string s = u.ST;
		LL rem = u.ND;

		if(rem == 0) return s;

		int next = (rem*10)%n;
		if(next == 0) return s+"0";
		else Q.push(MP(s+"0", next));

		next = (rem*10+1)%n;
		if(next == 0) return s+"1";
		else Q.push(MP(s+"1", next));
	}
	return "0";
}

int main() {
	int k;
	scanf("%d", &k);
	REP(i,k) {
		int n;
		scanf("%d", &n);
		printf("%s\n", bfs(n).c_str());
	}
	return 0;
}
