/* See http://codeforces.com/blog/entry/44754 - Levels and Regions editorial
 * To optimize dp it uses divide and conquer approach: http://codeforces.com/blog/entry/8192 Ciel and Gondolas
 */
#include <vector>
#include <map>
#include <set>
#include <string.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,lo,hi) for(int i=(lo);i<=(hi);++i)
#define rev(i,hi,lo) for(int i=(hi);i>=(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)((x).size()))
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define LL "%lld" //%I64d 
typedef long long ll;
typedef long long lint;
typedef long double ldouble;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<long long> vl;
typedef map<int, int> mii;
const lint MOD = 998244353;
const int INF = 1 << 30;
int a[100];

double dp[51][200*1000+1];
vd t, s, f, sf, it, si;

inline double calc_avg(int lo, int hi) {
	return sf[hi] - sf[lo - 1] - s[lo - 1] * (si[hi] - si[lo - 1]);
}

const double inf = 1e30;

void calc(int lo, int hi, int l, int r, double d1[], double d2[]) {
	if (lo > hi) return;
	int mid = (lo + hi) / 2;
	double res = inf;
	int jx = -1;
	for (int j = l; j <= r && j < mid; ++j) {
		if (d1[j] == inf) continue;
		double t = d1[j] + calc_avg(j + 1, mid);
		if (t < res) {
			res = t;
			jx = j;
		}
	}
	d2[mid] = res;
	calc(lo, mid - 1, l, jx, d1, d2);
	calc(mid + 1, hi, jx, r, d1, d2);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out2", "w", stdout);
#endif	
	int N, K;
	scanf("%d %d", &N, &K);
	t = s = f = sf = it = si = vd(N + 1, 0);

	for (int i = 1; i <= N; ++i) {
		int x = 1;
		scanf("%d", &x);
		t[i] = x;
		s[i] = s[i - 1] + t[i];
		f[i] = s[i] / t[i];
		sf[i] = sf[i - 1] + f[i];
		it[i] = 1 / t[i];
		si[i] = si[i - 1] + it[i];		
	}
	for (int k = 0; k <= K; ++k) {
		for (int i = 0; i <= N; ++i) {
			dp[k][i] = inf;
		}
	}
	dp[0][0] = 0;
	for (int k = 1; k <= K; ++k) {
		calc(0, N, 0, N, dp[k - 1], dp[k]);
	}
	printf("%.12lf\n", dp[K][N]);
	return 0;
}