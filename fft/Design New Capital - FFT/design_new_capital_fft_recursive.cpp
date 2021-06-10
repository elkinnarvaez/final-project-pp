#include <bits/stdc++.h>
#include <tgmath.h>

using namespace std;
using cd = complex<double>;

#define MAXN (int)pow(10, 5)

const double PI = acos(-1);

int mod = 7340033;

vector<int> fact(MAXN + 1);
vector<int> fact_inv(MAXN + 1);
vector<int> inv(MAXN + 1);

void print_vector_cd(const vector<cd> &a){
    int n = a.size();
	for (int i = 0; i < n; i++) 
		cout << round(a[i].real()) << " ";
    cout << endl;
}

void print_vector_int(const vector<int> &a){
    int n = a.size();
	for (int i = 0; i < n; i++) 
		cout << a[i] << " ";
    cout << endl;
}

int expmod(int a, int b){
    int ans = 1;
    while(b > 0){
        if(b & 1){
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b = b >> 1;
    }
    return ans;
}

int invmod(const int &a){
    return expmod(a, mod - 2);
}

void prec_fact(){
    fact[0] = 1; fact[1] = 1;
    fact_inv[0] = 1; fact_inv[1] = 1;
    inv[1] = 1;
    for(int i = 2; i < MAXN + 1; i++){
        inv[i] = (mod - (mod/i) * inv[mod%i] % mod) % mod;
        fact[i] = fact[i - 1] * i % mod;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % mod;
    }
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

int C(int n, int k){
    return fact[n] * fact_inv[k] * fact_inv[n - k] % mod;
}

vector<int> construct_polynomial(int c1, int c2){
    int K = min(c1, c2);
    vector<int> p(K + 1);
    for(int k = 0; k < K + 1; k++){
        p[k] = (C(c1, k)*C(c2, k));
    }
    return p;
}

vector<int> solve(const int coords[], int num_coords){
    vector<int> ans;
    vector<int> a = construct_polynomial(coords[0], coords[2]);
    vector<int> b = construct_polynomial(coords[1], coords[3]);
    vector<int> c = multiply(a, b);
    for(int i = 1; i < num_coords/2 + 1; i++){
        ans.push_back(c[i] % mod);
    }
    return ans;
}

int main(){
    prec_fact();
    int ntc, tc = 0, num_coords, x, y, i, j;
    vector<int> ans;
    scanf("%d", &ntc);
    while(tc < ntc){
        scanf("%d", &num_coords);
        int coords[4] = {0, 0, 0, 0};
        for(i = 0; i < num_coords; i++){
            scanf("%d %d", &x, &y);
            if(x > 0 && y > 0){
                coords[0] += 1;
            }
            else if(x < 0 && y > 0){
                coords[1] += 1;
            }
            else if(x < 0 && y < 0){
                coords[2] += 1;
            }
            else{
                coords[3] += 1;
            }
        }
        ans = solve(coords, num_coords);
        printf("Case %d:\n", tc + 1);
        printf("%d", 0);
        i = 0;
        for(j = 1; j < num_coords; j++){
            if(j % 2 == 0){
                printf(" %d", 0);
            }
            else{
                printf(" %d", ans[i]);
                i++;
            }
        }
        printf("\n");
        tc++;
    }
    return 0;
}

// void fft_test(){
//     int n = 8;
//  	vector<cd> a = {3, 2, 1, 8, 15, 27, 1, 13};
// 	fft(a, false);
//     print_vector_cd(a);
//     fft(a, true);
//     print_vector_cd(a);   
// }

// void multiply_test(){
// 	vector<int> a = {5, 6, -3, 6, 8, 17, -9, 1};
//     vector<int> b = {7, 4, 8, -3, 7};
//     vector<int> c = multiply(a, b);
//     print_vector_int(c);
// }

// int main(){
//     multiply_test();
//     return 0;
// }