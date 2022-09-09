
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5+1;
const int MxK = 1e9;
const int inf = INT_MAX;
#define REP0(i,n) for(int i=0; i<n; i++)
#define REP1(i,n) for(int i=1; i<=n; i++)
#define REP(i,a,b) for(int i=a; i<=b; i++)
#define pb push_back
#define fi first
#define se second
#define reset(X) memset(X, 0, sizeof(X))
#define pii pair<int, int>
#define endl "\n"
#define vint vector<int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define LOG 18 //enough for 10^5
//M_PI, M_E


typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = (int)a.size();
    if (n == 1)            //Base Case:n=1
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];   //짝수항
        a1[i] = a[2*i+1];   //홀수항
    }
    //recursion to base case
    fft(a0, invert);
    fft(a1, invert);

    //합치기, wn=e^(2pi/n)
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            //2^log(n) = n 으로 나누는 결과가 됨.
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}


vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    
    // 가장 가까운 2^k 꼴의 n으로 크기를 정해줌.
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // fft : coefficient rep to value rep : O(nlogn)
    fft(fa, false);
    fft(fb, false);
    // value rep에서 곱하기 : O(n)
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    //Inverse FFT : value rep to coefficeint rep :O(nlogn)
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}




int main()
{
    vint a = {1,2,3};
    vint b={1,1,1};
    vint result = multiply(a,b);
    REP0(i, result.size())cout<<result[i]<<" ";
}

