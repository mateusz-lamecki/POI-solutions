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
//include <unordered_set>
//include <unordered_map>
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
const int MAXM = 256;
VI G[MAXM];
char s[MAXN];
int n;

int main() {
	scanf("%d", &n);
	scanf("%s", s+1);

	FOR(i,1,n) G[(int)s[i]].PB(i);
	FOR(i,'a','z') reverse(ALL(G[i]));


	int res = 0;

	FOR(i,'a','z') {
		//printf("i = %c\n", i);

		FOR(j,'a','z') if(i != j && !G[i].empty() && !G[j].empty()) {
			//printf("%c %c\n", i, j);

			int pos = 0;
			int len = 0;
			bool is = 0;

			VI A, B;
			A.insert(A.end(),ALL(G[i]));//VI A = G[i];
			B.insert(B.end(),ALL(G[j]));//VI B = G[j];

			while(true) {
				while(!A.empty() && A.back() <= pos) A.pop_back();
				while(!B.empty() && B.back() <= pos) B.pop_back();

				if(A.empty() && B.empty()) break;
				
				int p = n+1;
				int q = n+1;

				if(!A.empty()) p = A.back();
				if(!B.empty()) q = B.back();

				//printf(" pos = %d, p = %d, q = %d\n", pos, p, q);

				if(p < q) {
					len++;
				} else {
					if(len == 0) {
						len = 0;
						is = 0;
					} else {
						len--;
						is = 1;
					}
				}

				pos = min(p,q);
				res = max(res, len-(is?0:1));
			}
		}
	}
	
	printf("%d\n", res);

	return 0;
}
