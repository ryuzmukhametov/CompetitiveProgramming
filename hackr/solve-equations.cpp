/*
	Usage extended euclidean algorithm to find out such x, y that
	a * x + b * y = d, where d is gcd of a and b
	then multiple to t=c/d
	a * x1 + b * y1 = c, where x1=x*(c/d), y1=y*(c/d)
	Then just need to shift x1 to correct range.
	Note: some test cases are wrong
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

ll GCD(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll r = GCD(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return r;
}

void Correct(ll &a, ll &b, ll &c) {
	ll x, y;
	ll d = GCD(a, b, x, y);
	d = GCD(d, c, x, y);
	a /= d;
	b /= d;
	c /= d;
}

void Solve() {
	ll a, b, c;
	cin >> a >> b >> c;
	Correct(a, b, c);
	ll x, y;
	ll d = GCD(a, b, x, y);
	x *= c / d;
	y *= c / d;
	x %= b; 
	if (x < 0) x += b;
	if (x == 0) x = b;
	y = (c - a * x) / b;
	cout << x << " " << y << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	int tst;
	cin >> tst;
	while (tst--) Solve();
	return 0;
}
