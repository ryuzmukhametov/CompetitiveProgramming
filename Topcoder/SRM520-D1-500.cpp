/*
	To solve problem we use two dp tables:
		d1[use][k][sum] - possible number to get sum points starting from k-th problem 
		where use is mask for solved problems
		d2[k][sum] - numbers of scoreboards from k-th user which has sum points
	To decrease complexity we prebuild array of partial sums for both tables.
	Total complexity: O(8*3*Hi)+O(MaxN * Hi)  where MaxN - max number of users (20) 
	and Hi max possible number of points (30000+60000+110000)
*/

#include <set>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef vector<string> vs;
const lint MOD = 1000*1000*1000+7;

inline bool testBit(int use, int p) {
	return (use >> p) & 1;
}

inline int calcMask(string &s) {
	int res = 0;
	for (int i = 0; i < 3; ++i) {
		res = res * 2 + (s[i] == 'Y');
	}
	return res;
}

vi buildSum(vi &v) {
	int n = v.size();
	vi s(n, 0);
	s[0] = v[0];
	for (int i = 1; i < n; ++i) {
		s[i] = s[i - 1] + v[i];
		s[i] %= MOD;
	}
	return s;
}

int calcSum(vi &s, int l, int r) {
	if (l > r) return 0;
	int res = 0;
	if (l > 0) {
		res = s[r] - s[l - 1];
		res %= MOD;
		if (res < 0) res += MOD;
	} else {
		res = s[r];
	}
	return res;
}

int countWays(vector <int> points, vector <string> description) {
	int n = description.size();
	int hi = points[0] + points[1] + points[2];
	
	vector<vector<vi> > d1(8);
	for (int use = 0; use < 8; ++use) {
		vector<vi> d(4, vi(hi + 1, 0));
		d[3][0] = 1;
		for (int k = 2; k >= 0; --k) {
			bool has = testBit(use, k);
			vi s = buildSum(d[k + 1]);

			for (int i = 0; i <= hi; ++i) {
				lint sum = 0; 
				int l = 1, r = points[2 - k];
				if (!has) l = r = 0;
				int t = min(r, i);
				sum = calcSum(s, i - t, i - l);
				d[k][i] = sum;
			}			
		}
		d1[use] = d;
	}

	vector<vi> d2(n + 1, vi(hi + 1, 0));
	for (int i = 0; i <= hi; ++i) {
		int mask = calcMask(description[n - 1]);
		d2[n - 1][i] = d1[mask][0][i];
	}

	for (int k = n - 2; k >= 0; --k) {
		int mask = calcMask(description[k]);

		vi s = buildSum(d2[k + 1]);

		for (int i = 0; i <= hi; ++i) {
			lint sum = 0;
			sum = calcSum(s, 0, i - 1);
			sum *= d1[mask][0][i];
			sum %= MOD;
			d2[k][i] = sum;
		}
	}
	lint ans = 0;
	for (int i = 0; i <= hi; ++i) {
		ans += d2[0][i];
		ans %= MOD;
	}
	return ans;
}

class SRMIntermissionPhase {
public:
	int countWays(vector <int> points, vector <string> description) {
		return ::countWays(points, description);
	}	
};

