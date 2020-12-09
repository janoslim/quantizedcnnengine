#ifndef CONVOLUTIONAL_LAYER_H
#define CONVOLUTIONAL_LAYER_H

#include "layer.h"
#include "gemm.h"
#include "../network/network.h"

class CONVOLUTIONAL_LAYER : public ILayer
{
private:
    int layerid;
    Linfo layertype;
    int ioid;
    Tinfo ty;

    PARAM paramW;
    PARAM paramB;

    int h,w,c;

    int n;
    std::vector<int> kernel_padding;

public:
    float* weightFptr;
    float* biasFptr;
    int* weightIptr;
    int* biasIptr;
    int8_t* weightI8ptr;
    int8_t* biasI8ptr;
    int16_t* weightI16ptr;
    int16_t* biasI16ptr;
    CONVOLUTIONAL_LAYER(IOPool*);
    ~CONVOLUTIONAL_LAYER();
    void setupLayer();
    void forward();
    void type();
    void quant();
};

#endif