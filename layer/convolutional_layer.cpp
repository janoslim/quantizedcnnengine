#include "./convolutional_layer.h"

CONVOLUTIONAL_LAYER::CONVOLUTIONAL_LAYER(IOPool* iopool) : ILayer(iopool), paramW(-1, 0), paramB(-1, 0)
{
}

CONVOLUTIONAL_LAYER::CONVOLUTIONAL_LAYER(IOPool* iopool, int lid, int iid, int Dtype, int wsize, int bsize) : ILayer(iopool), paramW(Dtype, wsize), paramB(Dtype, bsize)
{
    this->layerid = lid;
    this->layertype = CONVOLUTION;
    this->ioid = iid;
    this->ty = (Tinfo)Dtype;
}

void CONVOLUTIONAL_LAYER::setupLayer()
{
    this->layerid = this->id;
    this->layertype = CONVOLUTION;
    this->ioid = this->input_id[0];
    this->ty = this->Dtype;
    this->n = this->filters;
    // temporary kernel setting
    this->kernel_padding.push_back(0);
    this->kernel_padding.push_back(0);
    // set param size
    this->paramW.set_size(this->ty, this->size[0]* this->size[1] * this->filters);
    this->paramB.set_size(this->ty, this->filters);
    
}

CONVOLUTIONAL_LAYER::~CONVOLUTIONAL_LAYER()
{
    /* delete this->size;
    delete this->shape;
    delete this->stride;
    delete this->padding; */
}

void CONVOLUTIONAL_LAYER::make(void* weights, void* bias)
{
    /* this->n = n; >>  this->filters;
    this->size = size;  >> this->size;
    this->stride = stride; >> this->stride;
    this->padding = padding; >> this->kernel_padding*/
    this->n = this->filters;   
    
    switch (this->ty)
    {
        case INT:
            this->paramW.set_param_i((int *)weights);
            this->paramB.set_param_i((int *)bias);
            break;
        case INT8:
            this->paramW.set_param_i8((int8_t *)weights);
            this->paramB.set_param_i8((int8_t *)bias);
            break;
        case INT16:
            this->paramW.set_param_i16((int16_t *)weights);
            this->paramB.set_param_i16((int16_t *)bias);
            break;
        case FLOAT:
            this->paramW.set_param_fp((float *)weights);
            this->paramB.set_param_fp((float *)bias);
            break;
        default:
            std::cout << "Data Type not handled" << std::endl;
        // case 4:
        //     this->paramW.set_param_dp((int *)weights);
        //     this->paramB.set_param_dp((int *)bias);
    }
}

void CONVOLUTIONAL_LAYER::forward()
{
    IO* input = this->iopool->getIO(this->ioid);
    IO* output = this->iopool->getIO(this->layerid);
    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();

    int out_w = (w + 2*(this->kernel_padding[0]) - this->size[0]) / this->stride[0] + 1;
    int out_h = (h + 2*(this->kernel_padding[1]) - this->size[1]) / this->stride[1] + 1;

    int m = this->n;
    int k = this->size[0]*this->size[1]*this->c;
    int n = out_h*out_w;

    float *ta = paramW.get_param_fp();
    float *tb = new float[out_h * out_w * this->size[0] * this->size[1] * this->c];
    float *tc = new float[out_h * out_w * this->c];

    float *im = input->get_value_fp();
    if (this->size[0] == 1 && this->size[1] == 1)
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
                       this->kernel_padding[1], this->kernel_padding[0], // padding (h, w)
                       stride[1], stride[0],   // stride (h, w)
                       1, 1,                   // dilation (h, w)
                       tb);                    // output
    }
    gemm(0, 0, m, n, k, 1, ta, k, tb, n, 1, tc, n);
    add_bias(tc, paramB.get_param_fp(), 1, this->c, out_h * out_w);

    output->set_value(out_h, out_w, this->n, ty, tc);
    // inform output finished
    iopool->finish_input(this->layerid);
}

void CONVOLUTIONAL_LAYER::type()
{

}

void CONVOLUTIONAL_LAYER::quant()
{

}

