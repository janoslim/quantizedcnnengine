#include "./activation_layer.h"

ACTIVATION_LAYER::ACTIVATION_LAYER(IOPool* ioPool) : ILayer(ioPool)
{
}

ACTIVATION_LAYER::ACTIVATION_LAYER(IOPool* ioPool, int lid, int iid, int type) : ILayer(ioPool)
{
    this->layerid = lid;
    this->layertype = ACTIVATION;
    this->ioid = iid;
    this->ty = (Tinfo)type;
}


void ACTIVATION_LAYER::setupLayer()
{
    this->layerid = this->id;
    this->layertype = ACTIVATION;
    this->ioid = this->input_id[0];
    this->ty = this->Dtype;
}


ACTIVATION_LAYER::~ACTIVATION_LAYER()
{

}

void ACTIVATION_LAYER::make(int atype)
{
    this->atype = (Ainfo)atype;
}

void ACTIVATION_LAYER::forward()
{
    IO* input = iopool->getIO(this->ioid);
    IO* output = iopool->getIO(this->layerid);
    this->h = input->get_h();
    this->w = input->get_w();
    this->c = input->get_c();
    this->ty = (Tinfo)input->get_ty();

    float* outp = input->get_value_fp();

    activate_array_cpu_custom(outp, h*w*c, this->atype);
    
    output->set_value(h, w, c, ty, outp);

    iopool->finish_input(this->layerid);

}

void ACTIVATION_LAYER::type()
{

}

void ACTIVATION_LAYER::quant()
{

}

float activate(float x, Ainfo a)
{
    switch(a){
        case LINEAR:
            return linear_activate(x);
        case LOGISTIC:
            return logistic_activate(x);
        case LOGGY:
            return loggy_activate(x);
        case RELU:
            return relu_activate(x);
        case ELU:
            return elu_activate(x);
        case SELU:
            return selu_activate(x);
        case GELU:
            return gelu_activate(x);
        case RELIE:
            return relie_activate(x);
        case RAMP:
            return ramp_activate(x);
        case LEAKY:
            return leaky_activate(x);
        case TANH:
            return tanh_activate(x);
        case PLSE:
            return plse_activate(x);
        case STAIR:
            return stair_activate(x);
        case HARDTAN:
            return hardtan_activate(x);
        case LHTAN:
            return lhtan_activate(x);
        default:
            std::cout << "No Activation type error!" << std::endl;
    }
    return 0;
}

void activate_array_cpu_custom(float *x, const int n, const Ainfo a)
{
    int i;
    if (a == LINEAR)
    {
    }
    else if (a == LEAKY)
    {
        for (i = 0; i < n; ++i) {
            x[i] = (x[i]>0) ? x[i] : .1*x[i];
        }
    }
    else {
        for (i = 0; i < n; ++i) {
            x[i] = activate(x[i], a);
        }
    }
}

void activate_array_swish(float *x, const int n, float * output_sigmoid, float * output)
{
    int i;
    for (i = 0; i < n; ++i) {
        float x_val = x[i];
        float sigmoid = logistic_activate(x_val);
        output_sigmoid[i] = sigmoid;
        output[i] = x_val * sigmoid;
    }
}

// https://github.com/digantamisra98/Mish
void activate_array_mish(float *x, const int n, float * activation_input, float * output)
{
    const float MISH_THRESHOLD = 20;
    int i;
    for (i = 0; i < n; ++i) {
        float x_val = x[i];
        activation_input[i] = x_val;    // store value before activation
        output[i] = x_val * tanh_activate( softplus_activate(x_val, MISH_THRESHOLD) );
    }
}

float gradient(float x, Ainfo a)
{
    switch(a){
        case LINEAR:
            return linear_gradient(x);
        case LOGISTIC:
            return logistic_gradient(x);
        case LOGGY:
            return loggy_gradient(x);
        case RELU:
            return relu_gradient(x);
        case RELU6:
            return relu6_gradient(x);
        case ELU:
            return elu_gradient(x);
        case SELU:
            return selu_gradient(x);
        case GELU:
            return gelu_gradient(x);
        case RELIE:
            return relie_gradient(x);
        case RAMP:
            return ramp_gradient(x);
        case LEAKY:
            return leaky_gradient(x);
        case TANH:
            return tanh_gradient(x);
        case PLSE:
            return plse_gradient(x);
        case STAIR:
            return stair_gradient(x);
        case HARDTAN:
            return hardtan_gradient(x);
        case LHTAN:
            return lhtan_gradient(x);
    }
    return 0;
}

void gradient_array(const float *x, const int n, const Ainfo a, float *delta)
{
    int i;
    for(i = 0; i < n; ++i){
        delta[i] *= gradient(x[i], a);
    }
}

// https://github.com/BVLC/caffe/blob/04ab089db018a292ae48d51732dd6c66766b36b6/src/caffe/layers/swish_layer.cpp#L54-L56
void gradient_array_swish(const float *x, const int n, const float * sigmoid, float * delta)
{
    int i;
    for (i = 0; i < n; ++i) {
        float swish = x[i];
        delta[i] *= swish + sigmoid[i]*(1 - swish);
    }
}

// https://github.com/digantamisra98/Mish
void gradient_array_mish(const int n, const float * activation_input, float * delta)
{
    int i;
    for (i = 0; i < n; ++i) {
        const float MISH_THRESHOLD = 20.0f;

        // implementation from TensorFlow: https://github.com/tensorflow/addons/commit/093cdfa85d334cbe19a37624c33198f3140109ed
        // implementation from Pytorch: https://github.com/thomasbrandon/mish-cuda/blob/master/csrc/mish.h#L26-L31
        float inp = activation_input[i];
        const float sp = softplus_activate(inp, MISH_THRESHOLD);
        const float grad_sp = 1 - exp(-sp);
        const float tsp = tanh(sp);
        const float grad_tsp = (1 - tsp*tsp) * grad_sp;
        const float grad = inp * grad_tsp + tsp;
        delta[i] *= grad;


        //float x = activation_input[i];
        //float d = 2 * expf(x) + expf(2 * x) + 2;
        //float w = 4 * (x + 1) + 4 * expf(2 * x) + expf(3 * x) + expf(x)*(4 * x + 6);
        //float derivative = expf(x) * w / (d * d);
        //delta[i] *= derivative;
    }
}

