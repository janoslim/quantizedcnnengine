#include <iostream>
#include <fstream>
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

int main(int argc, char **argv)
{
	if (argc<3) 
	{
		fprintf(stderr, "usage: %s [modelpath] [weightpath] [inputpath]", argv[0]);
		return 0;
	}
	char *model = argv[1];
	std::string weight = argv[2];
	char *input = argv[3];

	JsonParser* jsonParser = new JsonParser();
	jsonParser->readJsonFile(model);
	//jsonParser->printResult();


	IOPool* iopool = new IOPool();
	Model mainModel;

	// prepare model
	mainModel.makeObject(*jsonParser, *iopool);
	std::cout << "makeObject set done." << std::endl;

	// set weight path
	mainModel.setWeightPath(weight);
	std::cout << "Weight set done." << std::endl;

	// setup input file
	FILE* input_file = fopen(input, "rb");
	float* inp = new float[28*28];
	fread(inp, 28*28, sizeof(float), input_file);

	iopool->getIO(-1)->set_value(28, 28, 1, 3, inp);
	iopool->finish_input(-1);
	// run model


	mainModel.geRootNetwork()->forward();

/* 	// Layer 예시 코드
	IOPool* iopool = new IOPool();


	FILE* inpfi = fopen("./data/input2.bin", "rb");
	float* inp = new float[28*28];
	fread(inp, 28*28, sizeof(float), inpfi);

	IO* input = new IO(0);
	input->set_value(28, 28, 1, 3, inp);
	input->print_io();


	ILayer** layers = new ILayer*[5];



	FILE* wb = fopen("./data/weightsFloat.weights", "rb");

	int filter = 5;
	int* size = new int[2];
	size[0] = 2;
	size[1] = 2;
	int* stride = new int[2];
	stride[0] = 1;
	stride[1] = 1;
	int* padding = new int[2];
	padding[0] = 0;
	padding[0] = 0;

	int weightC = size[0]*size[1]*filter;
	int biasC = filter;

	float* weight = new float[weightC];
	float* bias = new float[biasC];

	fprintf(stderr, "\nconv > w, b정보\n");
	fread(weight, weightC, sizeof(float), wb);
	for(int i=0; i<weightC; i++)
	{
		fprintf(stderr, "%f ", weight[i]);
	}
	fprintf(stderr, "\n");
	fread(bias, biasC, sizeof(float), wb);
	for(int i=0; i<biasC; i++)
	{
		fprintf(stderr, "%f ", bias[i]);
	}
	fprintf(stderr, "\n\n\n");

	CONVOLUTIONAL_LAYER* conv = new CONVOLUTIONAL_LAYER(1, 0, 3, weightC, biasC);
	conv->setupLayer(filter, size, stride, padding, weight, bias);
	layers[0] = (ILayer *)conv;

	IO* output = layers[0]->forward(input);
	output->print_io();





	ACTIVATION_LAYER* actv1 = new ACTIVATION_LAYER(2, 1, 3);
	actv1->setupLayer(3);
	layers[1] = (ILayer *)actv1;
	
	IO* output1 = layers[1]->forward(output);
	output1->print_io();




	
	MAXPOOL_LAYER* maxp = new MAXPOOL_LAYER(3, 2, 3);
	size[0] = 2;
	size[1] = 2;
	stride[0] = 2;
	stride[1] = 2;
	padding[0] = 0;
	padding[1] = 0;
	maxp->setupLayer(size, stride, padding);
	layers[2] = (ILayer *)maxp;

	IO* output2 = layers[2]->forward(output1);
	output2->print_io();



	int n = 10;
	int shape = 845;

	free(weight);
	weight = new float[n*shape];
	free(bias);
	bias = new float[n];

	fread(weight, shape*n, sizeof(float), wb);
	fread(bias, n, sizeof(float), wb);

	fprintf(stderr, "\ndense > w, b정보\n");
	for(int i=0; i<n; i++)
	{
		fprintf(stderr, "%f ", weight[i]);
	}
	fprintf(stderr, "\n");
	for(int i=0; i<n; i++)
	{
		fprintf(stderr, "%f ", bias[i]);
	}
	fprintf(stderr, "\n\n\n");
	
	DENSE_LAYER* dense = new DENSE_LAYER(4, 3, 3, shape*n, n);
	dense->setupLayer(10, weight, bias);
	layers[3] = (ILayer *)dense;

	IO* output3 = layers[3]->forward(output2);
	output3->print_io(); */

	// ACTIVATION_LAYER* actv2 = new ACTIVATION_LAYER(5,4,3);
	// actv2->setupLayer(0);
	// layers[4] = (ILayer *)actv2;

	// for(int i=0; i<5; i++) {
	// 	//layers[i]->forward(input);
	// }
}
