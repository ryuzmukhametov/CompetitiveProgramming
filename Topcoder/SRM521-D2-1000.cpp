/*
	Any n square from solution can be shifted in such way, that some vertext will be in certain point.
	Such point can be got from input X, Y arrays.
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

vi X, Y;
vi OX, OY;
int L;

bool Inside(int x1, int x2, int y1, int y2, int x, int y) {
	return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}
set<vi> S;
void Check(int x1, int x2, int y1, int y2) {	
	int nx = sz(OX);
	vi v;
	rep (i, 0, nx - 1) {
		int x = OX[i];
		int y = OY[i];
		if (Inside(x1, x2, y1, y2, x, y)) {
			v.pb(i);
		}
	}
	if (sz(v) > 0) S.insert(v);
}

void Add(int x, vi &X) {
	X.pb(x);
}

void Add(vi &OX, vi &X) {
	for (auto x : OX) {
		Add(x, X);
		Add(x - L, X);
		Add(x + L, X);
		Add(x - 1, X);
		Add(x + 1, X);
	}
}

ll CountSubsets(int n, vi x, vi y) {
	L = n * 2;
	int nx = sz(x);
	rep (i,0,nx-1) {
		x[i] *= 2;
		y[i] *= 2;
	}
	OX = x;
	OY = y;

	Add(OX, X);
	Add(OY, Y);
	
	for (auto x : X) {
		for (auto y : Y) {
			Check(x, x + L, y, y + L);
			Check(x - L, x, y, y + L);
			Check(x, x + L, y - L, y);
			Check(x - L, x, y - L, y);
		}
	}
	return sz(S);
}

class SquaredSubsets {
public:
	ll countSubsets(int n, vi x, vi y) {
		return CountSubsets(n, x, y);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif	
	    	
	// 0: Returns: 5
	//int n = 5; int x[] = {-5,0,5}; int y[] = {0,0,0};

	// 1: rans=5
	//int n = 10; int x[] = {-5,0,5}; int y[] = {0,0,0};

	// 2: 21
	//int n = 100000000;   int x[] = {-1,-1,-1,0,1,1,1};  int y[] = {-1,0,1,1,-1,0,1};
	
	// 3: Returns: 66
	int n = 5; int x[] = {5,3,6,2,1,6,4,4,7,-1,-4,-7,2,-2,0}; int y[] = {0,-1,8,-5,2,5,-8,8,-6,4,3,2,7,3,5};

	// 4: Returns 3
	// int n = 1;
	// int x[] = {-1,0};
	// int y[] = {0,0};

	int nx = sizeof(x) / sizeof(int);
	vi vx(x, x + nx); vi vy(y, y + nx);

	// vi vx, vy;
	// rep (i,1,50) {
	// 	vx.pb(i);
	// 	vy.pb(i);
	// }
	// int n = 10000*10000;

	SquaredSubsets o;
	cout << o.countSubsets(n, vx, vy) << endl;
	return 0;
}
