#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1);
#define MAXN (int)pow(10, 5)

int mod = 7340033;
int root = 5; // (1 << 20)-th root of unity 
int root_1 = 4404020; // inverse of root modulo mod
int root_pw = 1 << 20;

vector<int> fact(MAXN + 1);
vector<int> fact_inv(MAXN + 1);
vector<int> inv(MAXN + 1);

vector<int> a((int)pow(2, 17), 0);
vector<int> b((int)pow(2, 17), 0);
int na;
int nb;
int n;

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

// void ntt(vector<int> &p, const bool &invert, const int n){
//     int i = 1, j = 0;
//     while(i < n){
//         int bit = n >> 1;
//         while(j & bit){
//             j = j ^ bit;
//             bit = bit >> 1;
//         }
//         j = j ^ bit;
//         if(i < j){
//             swap(p[i], p[j]);
//         }
//         i++;
//     }
//     int length = 2;
//     while(length <= n){
//         int wlen = invert ? root_1 : root;
//         int i = length;
//         while(i < root_pw){
//             wlen = (int)(1LL * wlen * wlen % mod);
//             i = i << 1;
//         }
//         for(i = 0; i < n; i += length){
//             int w = 1;
//             for(j = 0; j < length/2; j++){
//                 int u = p[i + j], v = (int)(1LL * p[i+j+length/2] * w % mod);
//                 p[i + j] = u + v < mod ? u + v : u + v - mod;
//                 p[i + j + length/2] = u - v >= 0 ? u - v : u - v + mod;
//                 w = (int)(1LL * w * wlen % mod);
//             }
//         }
//         length = length << 1;
//     }
//     if(invert){
//         int n_1 = inv[n];
//         for(i = 0; i < n; i++){
//             p[i] = p[i] * n_1 % mod;
//         }
//     }
// }

void ntt(vector<int> &p, const bool invert, const int n){
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(p[i], p[j]);
    }
    print_vector_int(p);

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = p[i+j], v = (int)(1LL * p[i+j+len/2] * w % mod);
                p[i+j] = u + v < mod ? u + v : u + v - mod;
                p[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = invmod(n);
        for (int & x : p)
            x = (int)(1LL * x * n_1 % mod);
    }
}

void multiply(vector<int> &a, vector<int> &b){
    n = 1;
    while(n < na + nb){
        n = n << 1;
    }
    for(int i = na; i < n + 1; i++){
        a[i] = 0;
    }
    for(int i = nb; i < n + 1; i++){
        b[i] = 0;
    }
    ntt(a, false, n);
    ntt(b, false, n);
    for(int i = 0; i < n; i++){
        a[i] = a[i]*b[i];
    }
    ntt(a, true, n);
}

int C(int n, int k){
    return fact[n] * fact_inv[k] * fact_inv[n - k] % mod;
}

void construct_polynomial(int c1, int c2, vector<int> &p, bool flag){
    int K = min(c1, c2);
    if(flag){
        na = K + 1;
    }
    else{
        nb = K + 1;
    }
    for(int k = 0; k < K + 1; k++){
        p[k] = (C(c1, k)*C(c2, k));
    }
}

vector<int> solve(const int coords[], int num_coords){
    vector<int> ans;
    construct_polynomial(coords[0], coords[2], a, true);
    construct_polynomial(coords[1], coords[3], b, false);
    multiply(a, b);
    for(int i = 1; i < num_coords/2 + 1; i++){
        ans.push_back(a[i] % mod);
    }
    return ans;
}

// int main(){
//     prec_fact();
//     int ntc, tc = 0, num_coords, x, y, i, j;
//     vector<int> ans;
//     scanf("%d", &ntc);
//     while(tc < ntc){
//         scanf("%d", &num_coords);
//         int coords[4] = {0, 0, 0, 0};
//         for(i = 0; i < num_coords; i++){
//             scanf("%d %d", &x, &y);
//             if(x > 0 && y > 0){
//                 coords[0] += 1;
//             }
//             else if(x < 0 && y > 0){
//                 coords[1] += 1;
//             }
//             else if(x < 0 && y < 0){
//                 coords[2] += 1;
//             }
//             else{
//                 coords[3] += 1;
//             }
//         }
//         ans = solve(coords, num_coords);
//         printf("Case %d:\n", tc + 1);
//         printf("%d", 0);
//         i = 0;
//         for(j = 1; j < num_coords; j++){
//             if(j % 2 == 0){
//                 printf(" %d", 0);
//             }
//             else{
//                 printf(" %d", ans[i]);
//                 i++;
//             }
//         }
//         printf("\n");
//         tc++;
//     }
//     return 0;
// }

void ntt_test(){
    int n = 8;
 	vector<int> a = {3, 2, 1, 8, 15, 27, 1, 13};
	ntt(a, false, n);
    print_vector_int(a);
    ntt(a, true, n);
    print_vector_int(a);   
}

void multiply_test(){
    prec_fact();
    na = 3;
    nb = 3;
	vector<int> a = {1, 6, 3, 6, 8, 17, -9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> b = {1, 4, 1, -3, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    multiply(a, b);
    print_vector_int(a);
}

int main(){
    ntt_test();
    return 0;
}