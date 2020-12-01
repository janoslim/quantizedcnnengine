#include <iostream>
#include "../network/network.h"
#include "../type/io.h"
#include "../type/iopool.h"
#include "../jsonparser/jsonValue.h"
#include "../jsonparser/jsonParser.h"
#include "../model/model.h"
#include "../layer/activation_layer.h"
#include "../layer/convolutional_layer.h"
#include "../layer/dense_layer.h"
#include "../layer/gemm.h"
#include "../layer/maxpool_layer.h"
#include "../layer/softmax_layer.h"

using namespace _json_parser_qt;

int main()
{
	ILayer** layers = new ILayer*[5];

	CONVOLUTIONAL_LAYER* conv = new CONVOLUTIONAL_LAYER(1,0,3,10,10);
	int* size = new int[2];
	int* stride = new int[2];
	int* padding = new int[2];
	float* weights = new float[10];
	float* bias = new float[10];
	conv->make(1, size, stride, padding, weights, bias);
	layers[0] = (ILayer *)conv;

	ACTIVATION_LAYER* actv1 = new ACTIVATION_LAYER(2,1,3);
	actv1->make(3);
	layers[1] = (ILayer *)actv1;

	MAXPOOL_LAYER* maxp = new MAXPOOL_LAYER(3,2,3);
	maxp->make(size, stride, padding);
	layers[2] = (ILayer *)maxp;

	DENSE_LAYER* dense = new DENSE_LAYER(4,3,3,10,10);
	dense->make(10, weights, bias);
	layers[3] = (ILayer *)dense;

	ACTIVATION_LAYER* actv2 = new ACTIVATION_LAYER(5,4,3);
	actv2->make(0);
	layers[4] = (ILayer *)actv2;

	for(int i=0; i<5; i++) {
		//layers[i]->forward(input);
	}
}
