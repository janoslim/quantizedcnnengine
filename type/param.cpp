#include "./param.h"

PARAM::PARAM(int type, int size)
{
    this->set_size(type, size);
}

//
void PARAM::set_size(int size, int type = 3)
{
    
    this->type = type;
    switch (type) {
        case -1:
        // do nothing
            break;
        case 0:
            this->param_i = new int[size];
            break;
        case 1:
            this->param_i8 = new int8_t[size];
            break;
        case 2:
            this->param_i16 = new int16_t[size];
            break;
        case 3:
            this->param_fp = new float[size];
            break;
        // case 4:
        //     this->param_dp = new dp[size];
        //     break;
    }
}


PARAM::~PARAM()
{
    switch (type) {
        case 0:
            delete this->param_i;
            break;
        case 1:
            delete this->param_i8;
            break;
        case 2:
            delete this->param_i16;
            break;
        case 3:
            delete this->param_fp;
            break;
        // case 4:
        //     delete this->param_dp;
        //     break;
    }
}

int* PARAM::get_param_i() {
    return this->param_i;
}

int8_t* PARAM::get_param_i8() {
    return this->param_i8;
}

int16_t* PARAM::get_param_i16() {
    return this->param_i16;
}

float* PARAM::get_param_fp() {
    return this->param_fp;
}

// dp* PARAM::get_param_dp() {
//     return this->param_dp;
// }

void PARAM::set_param_i(int* weights) {
    this->param_i = weights;
}

void PARAM::set_param_i8(int8_t* weights) {
    this->param_i8 = weights;
}

void PARAM::set_param_i16(int16_t* weights) {
    this->param_i16 = weights;
}

void PARAM::set_param_fp(float* weights) {
    this->param_fp = weights;
}

// void PARAM::set_param_dp(dp* weights) {
//     this->param_dp = weights;
// }

