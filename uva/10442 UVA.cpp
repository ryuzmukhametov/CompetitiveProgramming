/*
	Scan input string from left to right and check on each step need rules.
	On each iteration we are wating regexp: digit+ or #digit+# depends on is it first iteration or not.
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

char S[1000];

int Digit(char ch, int base) {
	int res = -1;
	if ('0' <= ch && ch <= '9') {
		res = ch - '0';
	}
	if ('a' <= ch && ch <= 'f') {
		res = ch - 'a' + 10;
	}
	return 0 <= res && res < base ? res : -1;
}

bool Solve() {
	scanf("%s", S);
	int n = strlen(S);
	int base = 10;
	int i = 0;
	bool first = true;
	ll inf = 1000*1000*1000;
	while (i < n) {		
		if (base < 2 || base > 16) return false;
		if (!first && S[i] != '#') return false;
		if (!first) ++i;
		int j = i;
		ll res = 0;
		while (j < n && S[j] != '#') {
			char ch = S[j];
			int d = Digit(ch, base);
			if (d == -1) return false;
			res = res * base + d;
			res = min(res, inf);
			j++;
		}
		if (i == j) return false;
		if (j == n) return first;
		i = j + (first ? 0 : 1);
		base = res;		
		first = false;
	}
	return true;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	int tst;
	cin >> tst;
	while (tst--) {
		if (Solve()) puts("yes");
		else puts("no");
	}
	return 0;
}
