#ifndef MAXPOOL_LAYER_H
#define MAXPOOL_LAYER_H

#include "layer.h"
#include "float.h"

class MAXPOOL_LAYER : public ILayer
{
private:
    int layerid;
    Linfo layertype;
    int ioid;
    Tinfo ty;

    int h,w,c;
    int* shape;

    int* size;
    int* stride;
    int* padding;

public:
    MAXPOOL_LAYER(int lid, int iid, int type);
    ~MAXPOOL_LAYER();
    void make(int* size, int* stride, int* padding);
    IO forward(IO* input);
    void type();
    void quant();
};

#endif