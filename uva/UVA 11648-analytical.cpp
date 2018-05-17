/*
	Analytical solution: 
		alpha * h * alpha * x / 2 + alpha * h * b + alpha * h * alpha * y / 2 = s / 2
		s = (a + b) * h / 2
		x + y = a - b
	So need to solve quadratic equation:
		A * x * x + B * x + C = 0
		A = 2 * (a - b)
		B = 4 * b
		C = -(a + b)
*/
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
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii > vpii;
typedef vector<string > vs;
typedef vector<ll > vll;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdd;

void Solve(int tst) {
	ld a, b, c, d;
	cin >> a >> b >> c >> d;
	ld x = (sqrt(b*b + 0.5*(a*a-b*b)) - b) / (a - b);
	c *= (1-x);
	d *= (1-x);
	printf("Land #%d: %0.12Lf %0.12Lf\n", tst, c, d);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	int tst;
	cin >> tst;
	rep (i, 1, tst) {
		Solve(i);
	}
	return 0;
}
