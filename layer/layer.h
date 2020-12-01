#ifndef LAYER_H
#define LAYER_H

#include "../type/io.h"
#include "../type/param.h"

enum Linfo {
    ACTIVATION,
    CONVOLUTION,
    DENSE,
    MAXPOOL,
    SOFTMAX
};

class ILayer {
public:
    int layerid;
    Linfo layertype;
    int ioid;
    Tinfo ty;
    
    virtual IO forward(IO* input)=0;
    virtual void type()=0;
    virtual void quant()=0;
};

#endif