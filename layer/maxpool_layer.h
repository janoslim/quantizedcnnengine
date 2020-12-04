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

    std::vector<int> kernel_padding;
/*     int* size;
    int* stride;
    int* padding; */

public:
    MAXPOOL_LAYER(IOPool*);
    MAXPOOL_LAYER(IOPool*, int lid, int iid, int type);
    ~MAXPOOL_LAYER();
    void make();
    void forward();
    void type();
    void quant();
    void setupLayer();
};

#endif