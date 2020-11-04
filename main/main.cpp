#include <iostream>
#include "../network/network.h"
#include "../io/io.h"
#include "../io/iopool.h"


int main()
{
	IOPool* iopool = new IOPool();

	IO* io[10];

	for(int i = 1; i < 10; i++)
	{
		io[i] = new IO(i);
		iopool->add_IO(io[i]);
	}

	Network* net0 = new Network(0, 1, 9, iopool);
	Network* net1 = new Network(1, 1, 2, iopool);
	Network* net2 = new Network(2, 2, 3, iopool);
	Network* net3 = new Network(3, 2, 4, iopool);
	Network* net4 = new Network(4, 2, 5, iopool);
	Network* net5 = new Network(5, 5, 6, iopool);
	Network* net6 = new Network(6, 5, 7, iopool);
	Network* net7 = new Network(7, 7, 8, iopool);
	Network* net8 = new Network(8, 7, 9, iopool);
	
	net0->add_network(net1);
	net0->add_network(net2);
	net0->add_network(net3);
	net0->add_network(net4);
	net0->add_network(net5);
	net0->add_network(net6);
	net0->add_network(net7);
	net0->add_network(net8);

	iopool->finish_input(1);

	net0->forward();


	std::cout << "all finished!" << std::endl;
	delete iopool;
	for(int i = 1; i < 10; i++)
	{
		delete io[i];
	}
	
	delete net1;
	delete net2;
	delete net3;
	delete net4;
	delete net5;
	delete net6;
	delete net7;
	delete net8;
}
