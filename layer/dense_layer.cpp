#include "dense_layer.h"

DENSE_LAYER::DENSE_LAYER(int lid, int iid, int type, int wsize, int bsize) : paramW(type, wsize), paramB(type, bsize)
{
    this->layerid = lid;
    this->layertype = DENSE;
    this->ioid = iid;
    this->ty = (Tinfo)type;
}

DENSE_LAYER::~DENSE_LAYER()
{

}

void DENSE_LAYER::make(int n, void* weights, void* bias)
{
    this->n = n;

    switch (this->ty)
    {
        case INT:
            this->paramW.set_param_i((int *)weights);
            this->paramB.set_param_i((int *)bias);
        case INT8:
            this->paramW.set_param_i8((int8_t *)weights);
            this->paramB.set_param_i8((int8_t *)bias);
        case INT16:
            this->paramW.set_param_i16((int16_t *)weights);
            this->paramB.set_param_i16((int16_t *)bias);
        case FLOAT:
            this->paramW.set_param_fp((float *)weights);
            this->paramB.set_param_fp((float *)bias);
        // case 4:
        //     this->paramW.set_param_dp((int *)weights);
        //     this->paramB.set_param_dp((int *)bias);
    }
}

IO DENSE_LAYER::forward(IO* input)
{
    IO output(input->get_ID()+1);
    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();


    int m = 1;
    int k = h*w*c;
    int n = this->n;

    float* ta = input->get_value_fp();
    float* tb = this->paramW.get_param_fp();
    float* tc = new float[this->n];

    gemm(0,1,m,n,k,1,ta,k,tb,k,1,tc,n);
    axpy_cpu(n, 1, this->paramB.get_param_fp(), 1, tc, 1);

    output.set_value(h, w, c, ty, tc);

    return output;
}

void DENSE_LAYER::type()
{

}

void DENSE_LAYER::quant()
{

}