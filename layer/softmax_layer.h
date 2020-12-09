#ifndef SOFTMAX_LAYER_H
#define SOFTMAX_LAYER_H

#include "layer.h"
#include <float.h>
#include <math.h>

class SOFTMAX_LAYER : public ILayer
{
private:
    int layerid;
    Linfo layertype;
    int ioid;
    Tinfo ty;

    int h,w,c;

public:
    SOFTMAX_LAYER(IOPool*);
    ~SOFTMAX_LAYER();
    void setupLayer();
    void forward();
    void type();
    void quant();    
};

void softmax(float *input, int n, float temp, float *output, int stride);

#endif