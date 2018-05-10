#include <bits/stdc++.h>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define vout(x) cout<<#x<<"={";for(auto v:x)cout<<v<<",";cout<<"}\n";
#define aout(x,lo,hi) cout<<#x<<"={";rep(i,lo,hi)cout<<x[i]<<",";cout<<"}\n";
#define pout(x) cout<<#x<<"={"<<x.first<<","<<x.second<<"}\n";
#define mout(x) cout<<#x<<"={";for(auto v:x)cout<<v.first<<":"<<v.second<<","; cout<<"}\n";
#define LL "%lld" //%I64d 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef vector<ll > vll;
typedef pair<ll,ll> pll;

/////////////////////////////////////////////////////////////////////
// Segment tree: support adding and extract maximum operations
const int MAXQ = 1 << 16;
int Q[MAXQ << 1], Add[MAXQ << 1];
int GetMax(int l, int r, int p = 1, int lo = 0, int hi = MAXQ - 1) {
	if (l > r) {
		return 0;
	}
	if (lo == l && hi == r) {
		return Q[p];
	}
	int mid = (lo + hi) >> 1;
	int r1 = GetMax(l, min(mid, r), p * 2, lo, mid);
	int r2 = GetMax(max(mid + 1, l), r, p * 2 + 1, mid + 1, hi);
	return max(r1, r2) + Add[p];
}

void AddVal(int val, int l, int r, int p = 1, int lo = 0, int hi = MAXQ - 1) {
	if (l > r) {
		return;
	}
	if (lo == l && hi == r) {
		Add[p] += val;
		Q[p] += val;
		return;
	}
	int mid = (lo + hi) >> 1;
	AddVal(val, l, min(mid, r), p * 2, lo, mid);
	AddVal(val, max(mid + 1, l), r, p * 2 + 1, mid + 1, hi);
	Q[p] = max(Q[p * 2], Q[p * 2 + 1]) + Add[p];
}
/////////////////////////////////////////////////////////////////////

const int MAXN = 35 * 1000 + 1;
int N, K;
int A[MAXN];
int dp[51][MAXN];
int Mark[MAXN];
int G[MAXN];

void BuildG() {
	vi pos(MAXN, -1);
	rev(i, N, 1) {
		int x = A[i];
		if (pos[x] == -1) {
			G[i] = N + 1;
		} else {
			G[i] = pos[x];
		}
		pos[x] = i;
	}
}

void Clear() {
	memset(Q, 0, sizeof(Q));
	memset(Add, 0, sizeof(Add));
}

int Build() {
	BuildG();
	int cnt = 0;
	int curMark = 1;
	// k = 1
	rev(p, N, 1) {
		int v = A[p];
		if (Mark[v] != curMark) {
			++cnt;
			Mark[v] = curMark;
		}
		dp[1][p] = cnt;
	}
	// k=[2..K]
	rep(k, 2, K) {
		int p = 1;
		Clear();
		++curMark;
		cnt = 0;		
		rep(i, p + 1, N) {
			int val = dp[k - 1][i];
			int v = A[i - 1];
			if (Mark[v] != curMark) {
				++cnt;
				Mark[v] = curMark;
			}
			val += cnt;
			AddVal(val, i, i);
		}
		dp[k][p] = GetMax(p+1, N);

		rep (p, 2, N) {
			int pos = G[p - 1]; // get next pos
			AddVal(-1, p, pos);
			dp[k][p] = GetMax(p + 1, N);
		}
	}
	return dp[K][1];
}

void Read() {
	scanf("%d %d", &N, &K);
	rep(i, 1, N) {
		scanf("%d", &A[i]);		
	}	
}

void Solve() {
	int ans = Build();
	cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	Read();
	Solve();
	return 0;
}