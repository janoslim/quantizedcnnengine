#ifndef PARAM_H
#define PARAM_H

#include <iostream>
#include <string>
#include "type.h"

class PARAM
{
private:
    int type;
    int* param_i, bias_i;
	int8_t* param_i8, bias_i8;
    int16_t* param_i16, bias_i16;
    float* param_fp, bias_fp;
    //dp param_dp, bias_dp;
    
public:	
	PARAM(int type, int size);
	~PARAM();

	int* get_param_i();
    int8_t* get_param_i8();
    int16_t* get_param_i16();
    float* get_param_fp();
    //dp* get_param_dp();

    void set_param_i(int* weights);
    void set_param_i8(int8_t* weights);
    void set_param_i16(int16_t* weights);
    void set_param_fp(float* weights);
    //void set_param_dp(dp* weights);
};

#endif
