#include "./convolutional_layer.h"

CONVOLUTIONAL_LAYER::CONVOLUTIONAL_LAYER(int lid, int iid, int type, int wsize, int bsize) : paramW(type, wsize), paramB(type, bsize)
{
    this->layerid = lid;
    this->layertype = CONVOLUTION;
    this->ioid = iid;
    this->ty = (Tinfo)type;
}

CONVOLUTIONAL_LAYER::~CONVOLUTIONAL_LAYER()
{
    delete this->size;
    delete this->shape;
    delete this->stride;
    delete this->padding;
}

void CONVOLUTIONAL_LAYER::make(int n, int* size, int* stride, int* padding, void* weights, void* bias)
{
    this->n = n;
    this->size = size;
    this->stride = stride;
    this->padding = padding;

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

IO* CONVOLUTIONAL_LAYER::forward(IO* input)
{
    IO* output = new IO(input->get_ID()+1);
    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();

    int out_w = (w + 2*padding[0] - size[0]) / stride[0] + 1;
    int out_h = (h + 2*padding[1] - size[1]) / stride[1] + 1;

    int m = this->n;
    int k = this->size[0]*this->size[1]*this->c;
    int n = out_h*out_w;

    float *ta = paramW.get_param_fp();
    float *tb = new float[out_h * out_w * size[0] * size[1] * c];
    float *tc = new float[out_h * out_w * c];

    float *im = input->get_value_fp();
    if (size[0] == 1 && size[1] == 1)
    {
        tb = im;
    }
    else
    {
        //im2col_cpu(im, l.c / l.groups, l.h, l.w, l.size, l.stride, l.pad, b);
        im2col_cpu_ext(im,                     // input
                       c,                      // input channels
                       h, w,                   // input size (h, w)
                       size[1], size[0],       // kernel size (h, w)
                       padding[1], padding[0], // padding (h, w)
                       stride[1], stride[0],   // stride (h, w)
                       1, 1,                   // dilation (h, w)
                       tb);                    // output
    }
    gemm(0, 0, m, n, k, 1, ta, k, tb, n, 1, tc, n);
    add_bias(tc, paramB.get_param_fp(), 1, this->c, out_h * out_w);

    output->set_value(out_h, out_w, this->n, ty, tc);

    return output;
}

void CONVOLUTIONAL_LAYER::type()
{

}

void CONVOLUTIONAL_LAYER::quant()
{

}