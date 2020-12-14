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

public:
    MAXPOOL_LAYER(IOPool*);
    ~MAXPOOL_LAYER();
    void setupLayer();
    void forward();
    void type();
    void quant();
};

#endif