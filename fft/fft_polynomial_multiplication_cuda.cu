#include <bits/stdc++.h>
#include <tgmath.h>
#include <omp.h>
#include <time.h>
#include <math.h>

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

void fft_parallel(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;
    vector<cd> a0(n / 2), a1(n / 2);

    // for (int i = 0; i < n/2; i++) {
    //     a0[i] = a[2*i];
    //     a1[i] = a[2*i+1];
    // }

    #pragma omp parallel sections
    {
        #pragma omp section
            fft_parallel(a0, invert);
        #pragma omp section
            fft_parallel(a1, invert);
    }

    // #pragma omp single nowait
    // {
    //     #pragma omp task
    //         fft_parallel(a0, invert);
    //     #pragma omp task
    //         fft_parallel(a1, invert);
    // }
    // #pragma omp taskwait

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2*i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply_parallel(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    #pragma omp parallel sections
    {
        #pragma omp section
            fft_parallel(fa, false);
        #pragma omp section
            fft_parallel(fb, false);
    }
    
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft_parallel(fa, true);

    vector<int> ans(n);
    
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        ans[i] = round(fa[i].real());
    return ans;
}

void fft_sequential(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft_sequential(a0, invert);
    fft_sequential(a1, invert);

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

vector<int> multiply_sequential(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft_sequential(fa, false);
    fft_sequential(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft_sequential(fa, true);

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = round(fa[i].real());
    return ans;
}

void running_time_multiple_cases(){
    int N = (int)pow(2, 20);
    double start, end, elapsed;
    for(int n = 2; n <= N; n *= 2){
        vector<int> a(n), b(n);
        srand (time(NULL));
        for(int i = 0; i < n; i++){
            a[i] = rand() % 10 + 1;
            b[i] = rand() % 10 + 1;
        }
        start = omp_get_wtime();
        multiply_parallel(a, b);
        end = omp_get_wtime();
        elapsed = end - start;
        printf("%d %f\n", n, elapsed);
    }
}

void fft_test(){
 	vector<cd> a{-3, 4, 1, 5};
	fft_parallel(a, false);
    print_vector_complex(a);
    fft_parallel(a, true);
    print_vector_complex(a);   
}

void multiply_test(){
	vector<int> a = {5, 6, -3, 6, 8, 17, -9, 1};
    vector<int> b = {7, 4, 8, -3, 7};
    vector<int> ans = multiply_parallel(a, b);
    print_vector_int(ans);
}

int main(){
    running_time_multiple_cases();
    return 0;
}