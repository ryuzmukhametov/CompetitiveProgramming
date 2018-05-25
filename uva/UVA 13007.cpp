/*
*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define pout(p)  cout<<#p<<"=("<<(p.x)<<","<<p.y<<")\n"
#define vout(x) cout<<#x<<"={";for(auto v:x)cout<<v<<",";cout<<"}\n";
#define aout(x,lo,hi) cout<<#x<<"={";rep(i,lo,hi)cout<<x[i]<<",";cout<<"}\n";
#define mout(x) cout<<#x<<"={";for(auto v:x)cout<<v.first<<":"<<v.second<<","; cout<<"}\n";
#define LL "%lld" //%I64d 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef vector<string > vs;
typedef vector<ll > vll;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdd;

int B[1000];
int A[1000][1000];
int S[1000];
int D[5] = {1, 10, 100, 1000, 10000};
int M, N;

bool Solve() {
	int ans = 0;
	if (! (cin >> M >> N)) {
		return false;
	}
	rep(i,1,N) {
		cin >> B[i];
		S[i] = 0;
		rep (j,1,M) {
			cin >> A[i][j];
			S[i] += A[i][j];
		}
		if (S[i] == B[i]) {
			continue;
		}
		int cur = A[i][1];
		int p = -1;
		for (int k = 4; k >= 0; --k) {
			if (S[i] - cur + D[k] <= B[i]) {
				p = k;
				break;
			}
		}
		if (p == -1) {
			continue;
		}
		if (S[i] < B[i]) {
			if (D[p] > cur) {
				ans += D[p] - cur;
			}
		} else if (S[i] > B[i]) {
			ans += D[p];
		}
	}
	cout << ans << endl;
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	while (Solve());

	return 0;
}
