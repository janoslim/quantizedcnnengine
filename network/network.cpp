#include "./network.h"
#include <iostream>
#include <chrono>

Network::Network(int id, int input_id, int output_id, IOPool* iopool)
{
	this->id = id;
	this->input_id = input_id;
	this->output_id = output_id;
	this->iopool = iopool;
	child_networks = new std::vector<Network*>;
}

Network::~Network()
{
	delete this->child_networks;
}

void Network::forward()
{
	std::thread::id this_id = std::this_thread::get_id();
	// check if input ready
	this->check_input();
	std::cout << "tid: " << this_id << " running network " << this->id << "." << std::endl;

	for(Network* net : *this->child_networks)
	{
		net->my_thread = new std::thread(&Network::forward, net);
	}
	for(Network* net : *this->child_networks)
	{
		net->wait_thread();
	}

	std::this_thread::sleep_for (std::chrono::seconds(2));
	this->iopool->finish_input(this->output_id);
}

void Network::check_input()
{
	this->iopool->get_access(this->input_id);
	//std::cout << "thread " << this->id << " check input." << std::endl;
}

void Network::wait_thread()
{
	this->my_thread->join();
}

void Network::add_network(Network* network)
{
	this->child_networks->push_back(network);
}