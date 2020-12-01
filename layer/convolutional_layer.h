#ifndef CONVOLUTIONAL_LAYER_H
#define CONVOLUTIONAL_LAYER_H

#include "layer.h"
#include "gemm.h"

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
    int* shape;

    int n;
    int* size;
    int* stride;
    int* padding;

public:
    CONVOLUTIONAL_LAYER(int lid, int iid, int type, int wsize, int bsize);
    ~CONVOLUTIONAL_LAYER();
    void make(int n, int* size, int* stride, int* padding, void* weights, void* bias);
    IO forward(IO* input);
    void type();
    void quant();
};

#endif