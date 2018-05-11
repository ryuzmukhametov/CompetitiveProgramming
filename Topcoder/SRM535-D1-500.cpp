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
typedef pair<double,double> pdd;
int N, K;
int A[100], P[100];
double Total;

double Check(double alpha) {
	vector<double> v;
	rep(k, 1, N) {
		double t = A[k] * (P[k] - alpha);
		v.pb(t);
	}
	sort(v.begin(), v.end());
	double sum = 0;
	rep(i, 0, K - 1) {
		sum += v[i];
	}
	return sum + 3600 * K;
}

double Calc() {
	double lo = 0, hi = 1e30;
	rep (i, 1, 100000) {
		double mid = (lo + hi) / 2;
		if (Check(mid) < 0) hi = mid;
		else lo = mid;
	}
	return lo  * Total;
}

class FoxAndBusiness {
public:
	double minimumCost(int K, int totalWork, vector <int> a, vector <int> p) {
		::K = K;
		::Total = totalWork;
		::N = sz(a);
		rep(i,1,N) A[i] = a[i - 1];
		rep(i,1,N) P[i] = p[i - 1];
		return Calc();
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif

	return 0;
}