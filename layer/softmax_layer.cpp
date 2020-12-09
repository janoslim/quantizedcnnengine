#include "softmax_layer.h"

SOFTMAX_LAYER::SOFTMAX_LAYER(IOPool* iopool) : ILayer(iopool)
{
}

SOFTMAX_LAYER::~SOFTMAX_LAYER()
{
}

void SOFTMAX_LAYER::setupLayer()
{
    this->layerid = this->net_id;
    this->layertype = SOFTMAX;
    this->ioid = this->input_id[0];
    this->ty = this->Dtype;
}

void SOFTMAX_LAYER::forward()
{
    this->preset_forward();

    IO* input = this->iopool->getIO(this->ioid);
    IO* output = this->iopool->getIO(this->layerid);

    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();

    int inputs = h*w*c;

    float* inp = input->get_value_fp();
    float* outp = new float[inputs];

    softmax(inp, inputs, 1, outp, 1);

    output->set_value(h, w, c, ty, outp);

    iopool->finish_input(this->layerid);

    // join threads
    for(Network* net : this->child_networks)
	{
		net->wait_thread();
	}
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