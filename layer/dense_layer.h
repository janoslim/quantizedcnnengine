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
    DENSE_LAYER(IOPool*, int lid, int iid, int type, int wsize, int bsize);
    ~DENSE_LAYER();
    void make();
    void forward();
    void type();
    void quant();
    void setupLayer();
};

#endif