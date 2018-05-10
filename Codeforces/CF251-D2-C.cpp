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
const int MAXN = 100 * 1000 + 10;
int N, K, P;
int A[MAXN];

void Read() {
	scanf("%d %d %d", &N, &K, &P);
	rep(i, 1, N) {
		scanf("%d", &A[i]);
	}	
}


bool Solve() {
	vi odd, even;
	rep(i, 1, N) {
		if (A[i] & 1) {
			odd.pb(A[i]);
		} else {
			even.pb(A[i]);
		}
	}	
	int L = K - P;
	if (sz(odd) < L) {
		return false;
	}
	int left = sz(odd) - L;
	if (left & 1) {
		return false;
	}
	if (left / 2 + sz(even) < P) {
		return false;
	}
	puts("YES");
	int p = 0;
	vvi ans;
	rep(i, 1, L) {
		ans.pb(vi(1, odd[p++]));		
	}
	int e = 0;
	rep(i, 1, P) {		
		if (p < sz(odd)) {
			//ans.pb(vi(odd.begin() + p, odd.begin() + p + 2));
			vi t;
			t.pb(odd[p]);
			t.pb(odd[p + 1]);
			p += 2;
			ans.pb(t);
		} else {
			ans.pb(vi(1, even[e++]));
			//printf("1 %d\n", even[e++]);
		}
	}
	vi v = ans.back();
	ans.pop_back();

	while (e < sz(even)) {
		v.pb(even[e++]);
		//printf(" %d", even[e++]);
	}
	while (p < sz(odd)) {
		v.pb(odd[p++]);
		//printf(" %d", odd[p++]);
	}
	//printf("\n");
	ans.pb(v);	

	rep(i, 0, K - 1) {
		int n = sz(ans[i]);
		printf("%d", n);
		rep(j, 0, n - 1) {
			printf(" %d", ans[i][j]);
		}
		printf("\n");
	}	

	return true;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	Read();
	if (!Solve()) {
		puts("NO");
	}
	return 0;
}