#include "softmax_layer.h"

SOFTMAX_LAYER::SOFTMAX_LAYER(int lid, int iid, int type)
{
    this->layerid = lid;
    this->layertype = SOFTMAX;
    this->ioid = iid;
    this->ty = (Tinfo)type;
}

SOFTMAX_LAYER::~SOFTMAX_LAYER()
{
}

void SOFTMAX_LAYER::make(int* size, int* stride, int* padding)
{
}

IO SOFTMAX_LAYER::forward(IO* input)
{
    IO output(input->get_ID()+1);
    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();

    int inputs = h*w*c;

    float* inp = input->get_value_fp();
    float* outp = new float[inputs];

    softmax(inp, inputs, 1, outp, 1);

    output.set_value(h, w, c, ty, outp);
}

void SOFTMAX_LAYER::type()
{

}

void SOFTMAX_LAYER::quant()
{

}

void softmax(float *input, int n, float temp, float *output, int stride)
{
    int i;
    float sum = 0;
    float largest = -FLT_MAX;
    for(i = 0; i < n; ++i){
        if(input[i*stride] > largest) largest = input[i*stride];
    }
    for(i = 0; i < n; ++i){
        float e = exp(input[i*stride]/temp - largest/temp);
        sum += e;
        output[i*stride] = e;
    }
    for(i = 0; i < n; ++i){
        output[i*stride] /= sum;
    }
}