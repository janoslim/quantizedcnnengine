#include "maxpool_layer.h"

MAXPOOL_LAYER::MAXPOOL_LAYER(IOPool* iopool) : ILayer(iopool)
{
}

MAXPOOL_LAYER::~MAXPOOL_LAYER()
{
}

void MAXPOOL_LAYER::setupLayer()
{
    this->layerid = this->net_id;
    this->layertype = MAXPOOL;
    this->ioid = this->input_id[0];
    this->ty = this->Dtype;

    this->kernel_padding.push_back(0);
    this->kernel_padding.push_back(0);
}

void MAXPOOL_LAYER::forward()
{
    std::cout << "maxpool forward" << std::endl;

    this->preset_forward();

    IO* input = this->iopool->getIO(this->ioid);
    IO* output = this->iopool->getIO(this->layerid);


    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();
    float* inp = input->get_value_fp();
    int out_w = (w + kernel_padding[0] - pool_size[0]) / stride[0] + 1;
    int out_h = (h + kernel_padding[1] - pool_size[1]) / stride[1] + 1;
    int out_c = c;
    int outputs = out_w*out_h*out_c;
    int i, j, k, m, n;
    int w_offset = -kernel_padding[0] / 2;
    int h_offset = -kernel_padding[1] / 2;
    float* outp = new float[outputs];
    int* indexes = new int[outputs];
    
    for (k = 0; k < out_c; ++k)
    {
        for (i = 0; i < out_h; ++i)
        {
            for (j = 0; j < out_w; ++j)
            {
                int out_index = j + out_w * (i + out_h * k);
                float max = -FLT_MAX;
                int max_i = -1;
                for (n = 0; n < pool_size[1]; ++n)
                {
                    for (m = 0; m < pool_size[0]; ++m)
                    {
                        int cur_h = h_offset + i * stride[0] + n;
                        int cur_w = w_offset + j * stride[1] + m;
                        int index = cur_w + w * (cur_h + h * k);
                        int valid = (cur_h >= 0 && cur_h < h &&
                                     cur_w >= 0 && cur_w < w);
                        float val = (valid != 0) ? inp[index] : -FLT_MAX;
                        max_i = (val > max) ? index : max_i;
                        max = (val > max) ? val : max;
                    }
                }
                outp[out_index] = max;
                if (indexes)
                    indexes[out_index] = max_i;
            }
        }
    }
    output->set_value(out_h, out_w, out_c, ty, outp);
    iopool->finish_input(this->layerid);

    for(Network* net : this->child_networks)
	{
		net->wait_thread();
	}
}

void MAXPOOL_LAYER::type()
{

}

void MAXPOOL_LAYER::quant()
{

}
