#ifndef LAYER_H
#define LAYER_H

#include "../type/io.h"
#include "../type/param.h"
#include "../network/network.h"

enum Linfo {
    ACTIVATION,
    CONVOLUTION,
    DENSE,
    MAXPOOL,
    SOFTMAX
};

class ILayer : public Network 
{
public:
    ILayer(IOPool* iopool);
    virtual ~ILayer();
    virtual void setupLayer()=0;
    virtual void forward()=0;
    virtual void type()=0;
    virtual void quant()=0;
};

#endif