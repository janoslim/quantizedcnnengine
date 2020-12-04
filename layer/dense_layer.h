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
    DENSE_LAYER(IOPool*);
    DENSE_LAYER(IOPool*, int lid, int iid, int type, int wsize, int bsize);
    ~DENSE_LAYER();
    void make(void* weights, void* bias);
    void forward();
    void type();
    void quant();
    void setupLayer();
};

#endif