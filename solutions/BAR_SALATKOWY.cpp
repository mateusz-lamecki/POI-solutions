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

const int INF = 2147483640;
const int MAXN = 1000005;
char s[MAXN];
int l[MAXN];
int r[MAXN];
int n;

int main() {
	scanf("%d", &n);
	scanf("%s", s+1);

	int orange = 0, apple = 0;
	if(s[1] == 'p') orange++;
	else apple++;

	int i = 1;
	for(int j = 1; j<=n; j++) {
		while(i<n) {
			if(orange>apple || (orange==apple && s[i+1]=='p')) i++;
			else break;
			if(s[i] == 'p') orange++;
			else apple++;
		}
		if(j > i) {
			i++;
			if(s[i] == 'p') orange++;
			else apple++;
		}

		if(orange >= apple) printf("%d..%d, %d %d\n", j, i, orange, apple);
		if(orange >= apple) l[j] = i;
		else l[j] = 0;

		if(s[j] == 'p') orange--;
		else apple--;
	}

	NL;

	i = n;
	orange = apple = 0;
	if(s[n] == 'p') orange++;
	else apple++;

	for(int j = n; j>=1; j--) {
		while(i>1) {
			if(orange>apple || (orange==apple && s[i-1]=='p')) i--;
			else break;
			if(s[i] == 'p') orange++;
			else apple++;
		}
		if(j < i) {
			i--;
			if(s[i] == 'p') orange++;
			else apple++;
		}

		if(1 || orange >= apple) printf("%d..%d, %d %d\n", j, i, orange, apple);
		if(orange >= apple) r[j] = i;
		else r[j] = 0;

		if(s[j] == 'p') orange--;
		else apple--;
	}

	FOR(i,1,n) printf("%d ", l[i]);
	NL;
	FOR(i,1,n) printf("%d ", r[i]);
	NL;

	return 0;
}
