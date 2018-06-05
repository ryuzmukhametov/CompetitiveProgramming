/*
	Let's denote F(x) is number of digits in sequence for numbers from 1 to x.
	Then we can use binary search approach and F function to get answer. 
*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,lo,hi) for(ll i=(lo);i<=(ll)(hi);++i)
#define rev(i,hi,lo) for(ll i=(hi);i>=(ll)(lo);--i)
#define pb push_back
#define mp make_pair
#define sz(x) ((x).size())
#define out(x)  cout<<#x<<"="<<(x)<<"\n"
#define pout(p)  cout<<#p<<"=("<<(p.first)<<","<<p.second<<")\n"
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
typedef pair<ll, int> plli;

ll Lo[1000];

void Init() {
	Lo[1] = 1;
	rep (i, 2, 20) {
		Lo[i] = Lo[i - 1] * 10;
	}
}

ll Count(int f, ll cnt, int len) {
	ll l = cnt / 4;
	ll res = cnt * len + l * 3;
	ll left = cnt - l * 4;
	while (left--) {
		if (f % 4) ++res;
		f = (f + 1) % 4;
	}
	return res;
}


int Len(ll x) {
	if (!x) return 1;
	int res = 0;
	while (x) {
		x /= 10;
		++res;
	}
	return res;
}

ll Count(ll x) {
	int lenx = Len(x);
	ll res = 0;
	rep (len, 1, lenx) {
		ll lo = Lo[len];
		ll hi = Lo[len + 1] - 1;
		if (len == lenx) hi = x;
		res += Count(lo % 4, hi - lo + 1, len);
	}
	return res;
}

ll Calc(ll x) {
	ll lo = 1, hi = 1LL << 50;
	while (lo < hi) {
		ll mid = (lo + hi) >> 1;
		ll c = Count(mid);
		if (x > c) lo = mid + 1;
		else hi = mid;
	}	
	ll cnt = Count(lo);
	if (lo % 4) {
		lo = lo * 10;
		while (lo%4)++lo;
	}
	ll d = cnt - x;
	ll t = lo;
	int ans = 0;
	rep (i, 1, d + 1) {
		ans = t % 10;
		t /= 10;
	}
	return ans;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	//freopen("out1", "w", stdout);
#endif		
	Init();
	while (1) {
		ll x;
		cin >> x;
		if (!x) break;
		cout << Calc(x) << endl;
	}
	return 0;
}
