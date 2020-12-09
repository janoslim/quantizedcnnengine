#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H

#include "layer.h"
#include "gemm.h"

class DENSE_LAYER : public ILayer 
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

public:
    float* weightFptr;
    float* biasFptr;
    int* weightIptr;
    int* biasIptr;
    int8_t* weightI8ptr;
    int8_t* biasI8ptr;
    int16_t* weightI16ptr;
    int16_t* biasI16ptr;
    DENSE_LAYER(IOPool*);
    ~DENSE_LAYER();
    void setupLayer();
    void forward();
    void type();
    void quant();
};

#endif