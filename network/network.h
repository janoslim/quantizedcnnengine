#ifndef NETWORK_H
#define NETWORK_H

#include "../io/io.h"
#include "../io/iopool.h"
#include <vector>
#include <thread>

class Network
{
private:
	IOPool* iopool;
	int id;
	int input_id;
	int output_id;
	std::thread* my_thread;
	std::vector<Network*>* child_networks;
	void check_input();
public:
	Network(int id, int input_id, int output_id, IOPool* iopool);
	~Network();
	void forward();
	void wait_thread();
	void add_network(Network* network);
};


#endif
