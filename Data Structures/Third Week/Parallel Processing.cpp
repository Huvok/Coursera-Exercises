#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <functional>
#include <queue>
#include <bitset>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;

//															//AUTHOR: Hugo Garcia
//															//PURPOSE: Competitive programming template

//======================================================================================================================
#define rep(i,j,k) for (ll (i)=(j);(i)<=(k);++(i))

using namespace std;

typedef long long ll;

const double pi = acos(-1);
const ll N = (ll)3e5, base = (ll)3e5 + 1;

double f[N + 10];
ll rev[N * 40 + 10];
char s[N + 10], t[N + 10];

struct complex {
	double re, im;
	complex(double _re = 0, double _im = 0) :
		re(_re), im(_im) {
	}
	inline complex operator +(const complex &t) {
		return complex(re + t.re, im + t.im);
	}
	inline complex operator -(const complex &t) {
		return complex(re - t.re, im - t.im);
	}
	inline complex operator *(const complex &t) {
		return complex(re*t.re - im*t.im, re*t.im + im*t.re);
	}
}a[N * 4 + 10] = { 0 }, b[N * 4 + 10] = { 0 }, a2[N * 4 + 10] = { 0 }, b2[N * 4 + 10] = { 0 },
a3[N * 4 + 10] = { 0 }, b3[N * 4 + 10] = { 0 }, a4[N * 4 + 10] = { 0 }, b4[N * 4 + 10] = { 0 };

inline double sqr(double x) {
	return x*x;
}

void FFT(complex a[], ll f, ll n) {
	rep(i, 0, n - 1) if (i<rev[i]) swap(a[i], a[rev[i]]);
	for (ll i = 2; i <= n; i <<= 1) {
		complex wn(cos(2 * pi / i), f*sin(2 * pi / i));
		for (ll k = 0; k<n; k += i) {
			complex w(1);
			rep(j, 0, i / 2 - 1) {
				complex x = a[k + j], y = w*a[k + j + i / 2];
				a[k + j] = x + y;
				a[k + j + i / 2] = x - y;
				w = w*wn;
			}
		}
	}
	if (f == -1) rep(i, 0, n - 1) a[i].re /= n;
}

char c1[100005], c2[100005];
ll c[1000000];
//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN, intM;
	cin >> intN >> intM;
	vector<ll> v(intM);
	priority_queue<pair<ll, ll>> pq;

	for (ll intI = 0; intI < intM; ++intI)
	{
		cin >> v[intI];
	}

	for (ll intI = 0; intI < intN; ++intI)
	{
		pq.push(make_pair(0, intI * -1));
	}

	ll intAux1, intAux2;
	for (ll intI = 0; intI < intM; ++intI)
	{
		cout << pq.top().second * - 1 << " " << pq.top().first * -1 << endl;
		intAux1 = pq.top().second;
		intAux2 = pq.top().first;
		pq.pop();
		pq.push(make_pair(intAux2 - v[intI], intAux1));
	}

	return 0;
}
//======================================================================================================================