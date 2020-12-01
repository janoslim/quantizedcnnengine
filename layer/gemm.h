#ifndef GEMM_H
#define GEMM_H

void im2col_cpu_ext(const float* data_im, const int channels,
    const int height, const int width, const int kernel_h, const int kernel_w,
    const int pad_h, const int pad_w,
    const int stride_h, const int stride_w,
    const int dilation_h, const int dilation_w,
    float* data_col);

void gemm(int TA, int TB, int M, int N, int K, float ALPHA,
                    float *A, int lda,
                    float *B, int ldb,
                    float BETA,
                    float *C, int ldc);

void add_bias(float *output, float *biases, int batch, int n, int size);
void axpy_cpu(int N, float ALPHA, float *X, int INCX, float *Y, int INCY);

#endif