/*
	Usage of segment tree data structure with increasing and extracting 
	maximum on interval operations allows to solve that problem.
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

const int MAXN = 200*1000+10;
int N, A[MAXN];

const int MAXQ = 1 << 18;
ll Q[MAXQ * 2];
ll Add[MAXQ * 2];
ll q[MAXQ * 2];
const ll INF = 1LL << 60;

void add(ll &x, ll val) {
	if (x != -INF) x += val;
}

void AddVal(int lo, int hi, int p, int l, int r, ll val) {
	if (l > r) {
		return;
	}
	if (lo == l && hi == r) {
		Add[p] += val;
		add(Q[p], val);
		return;
	}
	int mid = (lo + hi) / 2;
	AddVal(lo, mid, p * 2, l, min(r, mid), val);
	AddVal(mid + 1, hi, p * 2 + 1, max(l, mid + 1), r, val);
	ll r1 = Q[p * 2];
	ll r2 = Q[p * 2 + 1];
	Q[p] = max(r1, r2);
	add(Q[p], Add[p]);
}

ll GetMax(int lo, int hi, int p, int l, int r) {
	if (l > r) {
		return -INF;
	}
	if (lo == l && hi == r) {
		return Q[p];
	}
	int mid = (lo + hi) / 2;
	ll r1 = GetMax(lo, mid, p * 2, l, min(r, mid));
	ll r2 = GetMax(mid + 1, hi, p * 2 + 1, max(l, mid + 1), r);
	ll res = max(r1, r2);
	add(res, Add[p]);
	return res;
}


void AddVal(int l, int r, ll val) {
	AddVal(0, MAXQ - 1, 1, l, r, val); 
}

ll GetMax(int l, int r) {
	return GetMax(0, MAXQ - 1, 1, l, r);
}

ll S[MAXN], F[MAXN];


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif	
	scanf("%d", &N);

	rep (i, 1, N) {
		scanf("%d", &A[i]);
		AddVal(i, i, -i);
		F[A[i]]++;
	}
	
	rep (i, 1, N) {
		S[i] = S[i - 1] + F[i];
		AddVal(i, i, S[i]);
	}

	int m;
	scanf("%d", &m);
	rep (step, 0, m) {		
		if (step) {
			int j, w;			
			scanf("%d %d", &j, &w);
			int prev = A[j];
			A[j] = w;
			AddVal(prev, N, -1);
			AddVal(w, N, 1);
		}
		ll val = GetMax(1, N);		
		if (val <= 0) puts("TAK");
		else puts("NIE");			
	}
	return 0;
}