/*
	To solve problem we need fast calculate sum of elements in 2d array from regular rhomb shape (it comes from manhattan distance).
	If we make substitution:
		I = j + i
		J = j - i
	Then the rhomb becomes to rectangle and then it is easy to calculate sums using 2d array of partial sums.
 */
#include <vector>
#include <map>
#include <set>
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
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<long long> vl;
typedef map<int, int> mii;
const lint MOD = 1000*1000*1000+7;	

const int II = 200, JJ = 300;
int TT;
vvi sum;

inline vvi init(int N, int M, int pi, int pj) {
	vvi a(N + 1, vi(M + 1, 0));
	a[pi][pj] = 1;
	return a;
}

inline lint get_sum(int i, int j) {
	return sum[i + II][j + JJ];
}

inline void set_sum(int i, int j, int val) {
	sum[i + II][j + JJ] = val;
}

void correct(lint &val) {
	while (val >= MOD) val-=MOD;
	while (val < 0) val+=MOD;
}

inline void init_sum(int N, int M, vvi &a) {	
	// I = i + j;
	// J = j - i
	int mini = 1 - TT;
	int minj = 1 - TT;
	int maxi = N + TT;
	int maxj = M + TT;
	int minI = mini + minj, maxI = maxi + maxj;
	int minJ = minj - maxi, maxJ = maxj - minj;
	for (int I = minI; I <= maxI; ++I) {
		for (int J = minJ; J <= maxJ; J++) {
			int i = (I - J) / 2;
			int j = (I + J) / 2;
			int x = 0;
			if (((I + J) & 1) == 0 && 1 <= i && i <= N && 1 <= j && j <= M) {
				x = a[i][j];
			} 
			lint val = x
			+ get_sum(I - 1, J) 
			+ get_sum(I, J - 1) 
			- get_sum(I - 1, J - 1);
			correct(val);
			set_sum(I, J, val);
		}
	}
}

inline int calc_sum(int i, int j, int t) {
	int I1 = i + j - t - 1;
	int I2 = i + j + t;
	int J1 = j - i - t - 1;
	int J2 = j - i + t;
	lint res
	= get_sum(I2, J2) 
	- get_sum(I1, J2) 
	- get_sum(I2, J1) 
	+ get_sum(I1, J1);
	correct(res);
	return res;
}

void Solve(int tst) {
	int N, M, S, pi, pj;	
	scanf("%d%d%d%d%d", &N, &M, &S, &pi, &pj);
	TT = S;
	vvi G(N, vi(M, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &G[i][j]);			
		}
	}
	vvi a = init(N, M, pi, pj);	
	vvi b = a;		
	for (int t = S - 1; t >= 1; --t) {
		init_sum(N, M, a);
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				b[i][j] = calc_sum(i, j, t);
			}
		}
		a = b;
	}
	lint ans = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			lint x = G[i - 1][j - 1];
			x *= a[i][j];
			ans += x;
			ans %= MOD;
		}
	}
	printf("Case %d: %lld\n", tst, ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out2", "w", stdout);
#else
	freopen("treasures.in", "r", stdin);
#endif	
	sum = vvi(601, vi(601, 0));
	int tst;
	scanf("%d", &tst);
	for (int i = 1; i <= tst; ++i) {
		Solve(i);
	}
	return 0;
}
