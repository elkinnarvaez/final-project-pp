# Final Project Parallel Programming

1. Possible Projects to work on:
    - https://github.com/topics/image-processing?l=matlab&o=asc&s=forks
    - https://github.com/topics/image-encryption
    - https://github.com/topics/numerical-methods?l=c%2B%2B&o=asc&s=forks
    - https://github.com/topics/numerical-analysis?l=c%2B%2B
2. Execution
    - export OMP_NUM_THREADS=8
    - g++ fft_polynomial_multiplication.cpp -fopenmp -o fft_polynomial_multiplication.out
    - nvcc test_cuda.cu -Xcompiler -fopenmp -o test_cuda.out
    - nvcc fft_polynomial_multiplication_cuda.cu -Xcompiler -fopenmp -o fft_polynomial_multiplication_cuda.out
3. Data races detection
    - export PATH=~/Programs/coderrect-linux-hpc-1.0.0/bin:$PATH
    - coderrect -t g++ -fopenmp -g fft_polynomial_multiplication.cpp