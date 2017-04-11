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
const int MOD = 1000000007;
const int MAXN = 2000005;
VI p;
vector<string> S;
char s[MAXN];
int n;

int get_hash1(VI &h1, int a, int b) {
	if(a>b) return 0;
	int len = b-a+1;
	return h1[b] - (a ? h1[a-1]*p[len] : 0);
}
		
int get_hash2(VI &h2, int a, int b) {
	int m = SIZE(h2);
	if(a>b) return 0;
	a = m-a-1;
	b = m-b-1;
	if(a > b) swap(a,b);
	int len = b-a+1;
	return h2[b] - (a ? h2[a-1]*p[len] : 0);
}

int main() {
	scanf("%d", &n);
	int mx_len = 0;
	REP(i,n) {
		int l;
		scanf("%d", &l);
		scanf("%s", s);

		mx_len = max(mx_len, l+1);

		string q;
		REP(i,l) q += s[i];
		S.PB(q);
	}

	p.resize(mx_len+5);
	p[0] = 1;
	FOR(i,1,mx_len) p[i] = p[i-1] * MOD;

	map<int,int> M;

	REP(i,n) {
		int hsh = S[i][0];
		FOR(j,1,SIZE(S[i])-1) hsh = hsh * MOD + S[i][j];
		M[hsh]++;
	}

	int res = 0;

	REP(i,n) {
		int m = SIZE(S[i]);

		VI h1(m), h2(m);
		h1[0] = S[i][0];
		FOR(j,1,m-1) h1[j] = h1[j-1] * MOD + S[i][j];
		h2[0] = S[i][m-1];
		FOR(j,1,m-1) h2[j] = h2[j-1] * MOD + S[i][m-j-1];

		//printf("Analizuję słowo %s\n", S[i].c_str());

		FORD(i,m-1,0) {
			int q1 = get_hash1(h1,0,i);
			int q2 = get_hash2(h2,0,i);
			//printf(" %d..%d: %d %d, %d\n", 0, i, q1, q2, q1==q2);
			if(q1 == q2) {
				//printf(" słowo w na [%d..%d]\n", 0, i);
				int q = 0;
				map<int,int>::iterator it = M.find(get_hash2(h2,i+1,m-1));
				if(it != M.end()) q = it->ND;
				//if(q) printf("  dodaję %d słów\n", q);
				res += q;
			}
		}

		REP(i,m) {
			int q1 = get_hash1(h1,i,m-1);
			int q2 = get_hash2(h2,i,m-1);
			if(q1 == q2) {
				//printf(" słowo w na [%d..%d], reverse\n", i, m-1);
				int q = 0;
				map<int,int>::iterator it = M.find(get_hash2(h2,0,i-1));
				if(it != M.end()) q = it->ND;
				//if(q) printf("  dodaję %d słów\n", q);
				res += q;
			}
		}

		int q = 0;
		map<int,int>::iterator it = M.find(get_hash2(h2,0,m-1));
		if (it != M.end()) q = it->ND;
		//printf("  dodaję %d słów, end\n", q);
		res += q;
		//NL;
	}

	printf("%d\n", res);

	return 0;
}
