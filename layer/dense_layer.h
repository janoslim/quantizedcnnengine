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
    DENSE_LAYER(int lid, int iid, int type, int wsize, int bsize);
    ~DENSE_LAYER();
    void make(int n, void* weights, void* bias);
    IO* forward(IO* input);
    void type();
    void quant();
};

#endif