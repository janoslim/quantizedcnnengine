#include "maxpool_layer.h"

MAXPOOL_LAYER::MAXPOOL_LAYER(int lid, int iid, int type)
{
    this->layerid = lid;
    this->layertype = MAXPOOL;
    this->ioid = iid;
    this->ty = (Tinfo)type;
}

MAXPOOL_LAYER::~MAXPOOL_LAYER()
{
    delete this->size;
    delete this->shape;
    delete this->stride;
    delete this->padding;
}

void MAXPOOL_LAYER::make(int* size, int* stride, int* padding)
{
    this->size = size;
    this->stride = stride;
    this->padding = padding;
}

IO MAXPOOL_LAYER::forward(IO* input)
{
    IO output(input->get_ID()+1);
    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();

    float* inp = input->get_value_fp();

    int out_w = (w + padding - size) / stride[0] + 1;
    int out_h = (h + padding - size) / stride[1] + 1;
    int out_c = c;
    int outputs = out_w*out_h*out_c;

    int i, j, k, m, n;
    int w_offset = -padding[0] / 2;
    int h_offset = -padding[1] / 2;

    int h = out_h;
    int w = out_w;
    int c = c;
    float* outp = new float[outputs];
    int* indexes = new int[outputs];

    for (k = 0; k < c; ++k)
    {
        for (i = 0; i < h; ++i)
        {
            for (j = 0; j < w; ++j)
            {
                int out_index = j + w * (i + h * k);
                float max = -FLT_MAX;
                int max_i = -1;
                for (n = 0; n < size[1]; ++n)
                {
                    for (m = 0; m < size[0]; ++m)
                    {
                        int cur_h = h_offset + i * stride[1] + n;
                        int cur_w = w_offset + j * stride[0] + m;
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

    output.set_value(h, w, c, ty, outp);

    return output;
}

void MAXPOOL_LAYER::type()
{

}

void MAXPOOL_LAYER::quant()
{

}