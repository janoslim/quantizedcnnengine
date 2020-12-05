#include "dense_layer.h"

DENSE_LAYER::DENSE_LAYER(IOPool* iopool): ILayer(iopool), paramW(-1, 0), paramB(-1, 0)
{
    
}

DENSE_LAYER::DENSE_LAYER(IOPool* iopool, int lid, int iid, int type, int wsize, int bsize) : ILayer(iopool), paramW(type, wsize), paramB(type, bsize)
{
    this->layerid = lid;
    this->layertype = DENSE;
    this->ioid = iid;
    this->ty = (Tinfo)type;
}

void DENSE_LAYER::setupLayer()
{
    this->layerid = this->id;
    this->layertype = DENSE;
    this->ioid = this->input_id[0];
    this->ty = this->Dtype;
    // set param size
    
    this->n = this->units;
    this->paramW.set_size(this->ty, this->shape[0] * this->units);
    this->paramB.set_size(this->ty, this->units);
}


DENSE_LAYER::~DENSE_LAYER()
{

}

void DENSE_LAYER::make()
{
    
    this->n = this->units;

    switch (this->ty)
    {
        case INT:
            this->paramW.set_param_i(weightIptr);
            this->paramB.set_param_i(biasIptr);
            break;
        case INT8:
            this->paramW.set_param_i8(weightI8ptr);
            this->paramB.set_param_i8(biasI8ptr);
            break;
        case INT16:
            this->paramW.set_param_i16(weightI16ptr);
            this->paramB.set_param_i16(biasI16ptr);
            break;
        case FLOAT:
            this->paramW.set_param_fp(weightFptr);
            this->paramB.set_param_fp(biasFptr);
            break;
        default:
            std::cout << "Not handled data Type Error" << std::endl;
            exit(-1);
        // case 4:
        //     this->paramW.set_param_dp((int *)weights);
        //     this->paramB.set_param_dp((int *)bias);
    }
}

void DENSE_LAYER::forward()
{
    std::cout << "dense forward" << std::endl;

    this->preset_forward();

    IO* input = this->iopool->getIO(this->ioid);
    IO* output = this->iopool->getIO(this->layerid);
    
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

    output->set_value(n, 1, 1, ty, tc);

    // inform output finished
    iopool->finish_input(this->layerid);

    for(Network* net : this->child_networks)
	{
		net->wait_thread();
	}
}

void DENSE_LAYER::type()
{

}

void DENSE_LAYER::quant()
{

}

