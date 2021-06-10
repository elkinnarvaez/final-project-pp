#include <bits/stdc++.h>
#include <tgmath.h>

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void print_vector_complex(const vector<cd> &a){
    int n = a.size();
	for (int i = 0; i < n; i++) 
		cout << a[i] << " ";
    cout << endl;
}

void print_vector_int(const vector<int> &a){
    int n = a.size();
	for (int i = 0; i < n; i++) 
		cout << a[i] << " ";
    cout << endl;
}

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = round(fa[i].real());
    return ans;
}

void fft_test(){
 	vector<cd> a{-3, 4, 1, 5};
	fft(a, false);
    print_vector_complex(a);
    fft(a, true);
    print_vector_complex(a);   
}

void multiply_test(){
	vector<int> a = {5, 6, -3, 6, 8, 17, -9, 1};
    vector<int> b = {7, 4, 8, -3, 7};
    vector<int> ans = multiply(a, b);
    print_vector_int(ans);
}

int main(){
    multiply_test();
    return 0;
}