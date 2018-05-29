/*
	Number of described N length permutations equals to n-th Fibonacci numbers.
	And first part of ordered set is F(N-1) N-1 length permutations and after
	F(N - 2) N-1 length permutations. According to that we can implement solution
	to create permutation by given number.
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

ll F[1000];
vi GetPerm(int n, ll x) {
	F[0] = 1;
	F[1] = 1;
	F[2] = 2;

	// Fibonacci calc
	rep (i, 3, n) {
		F[i] = F[i - 1] + F[i - 2];
	}
	vi p(n, 0);
	int i = 1; 
	while (i <= n) {
		int k = i - 1;
		if (x < F[n - i]) {
			p[k] = i;
			++i;			
		} else {
			p[k] = i + 1;
			p[k + 1] = i;
			i += 2;
			x -= F[n - i];
		}
	}
	return p;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	int n;
	ll x;
	cin >> n >> x;
	--x;
	vi p = GetPerm(n, x);
	rep (i, 0, n-1) {
		cout << p[i] << " ";			
	}
	cout << endl;
	return 0;
}
