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

// int reverse(int num, int lg_n) {
//     int res = 0;
//     for (int i = 0; i < lg_n; i++) {
//         if (num & (1 << i))
//             res |= 1 << (lg_n - 1 - i);
//     }
//     return res;
// }

// void fft(vector<cd> & a, bool invert) {
//     int n = a.size();
//     int lg_n = 0;
//     while ((1 << lg_n) < n)
//         lg_n++;

//     for (int i = 0; i < n; i++) {
//         if (i < reverse(i, lg_n))
//             swap(a[i], a[reverse(i, lg_n)]);
//     }

//     for (int len = 2; len <= n; len <<= 1) {
//         double ang = 2 * PI / len * (invert ? -1 : 1);
//         cd wlen(cos(ang), sin(ang));
//         for (int i = 0; i < n; i += len) {
//             cd w(1);
//             for (int j = 0; j < len / 2; j++) {
//                 cd u = a[i+j], v = a[i+j+len/2] * w;
//                 a[i+j] = u + v;
//                 a[i+j+len/2] = u - v;
//                 w *= wlen;
//             }
//         }
//     }
//     if (invert) {
//         for (cd & x : a)
//             x /= n;
//     }
// }

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd & x : a)
            x /= n;
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
 	vector<cd> a{3, 2, 1, 8, -3, 4, 9, -5};
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