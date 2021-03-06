#include "./network.h"
#include <iostream>
#include <chrono>


Network::Network(IOPool* iopool)
{
	this->iopool = iopool;
}

Network::~Network()
{
}

void Network::forward()
{
	std::thread::id this_id = std::this_thread::get_id();
	// check if input ready
	this->check_input();
	//std::cout << "tid: " << this_id << " running network " << this->id << "." << static_cast<std::underlying_type<NETWORKTYPE>::type>(this->network_type) << std::endl;

	for(Network* net : this->child_networks)
	{
		net->my_thread = new std::thread(&Network::forward, net);
	}
	for(Network* net : this->child_networks)
	{
		net->wait_thread();
	}

	//std::this_thread::sleep_for (std::chrono::seconds(2));
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
	this->child_networks.push_back(network);
}

void Network::setNetworkType(Ninfo t)
{
	this->network_type = t;
}
void Network::setActType(Ainfo at)
{
	this->act_type = at;
}
void Network::setShape(std::vector<int>& shape_vec)
{
	for(int& i : shape_vec)
	{
		this->shape.push_back(i);
	}
}
void Network::setUnits(int unit)
{
	this->units = unit;
}

void Network::setId(int id)
{
	this->net_id = id;
}

void Network::setInputId(std::vector<int>& id_vec)
{
	for(int& i : id_vec)
	{
		this->input_id.push_back(i);
	}
}

void Network::setOutputId(int id)
{
	this->output_id = id;
}

void Network::setPoolSize(std::vector<int>& pool_vec)
{
	for(int& i : pool_vec)
	{
		this->pool_size.push_back(i);
	}
}
void Network::setStride(std::vector<int>& stride_vec)
{
	for(int& i : stride_vec)
	{
		this->stride.push_back(i);
	}
}

void Network::setSize(std::vector<int>& filter_vec)
{
	for(int& i : filter_vec)
	{
		this->size.push_back(i);
	}
}

void Network::setFilter(int f)
{
	this->filters = f;
}

IOPool* Network::getIOPool()
{
	return this->iopool;
}

void Network::setIOPool(IOPool* iopool)
{
	this->iopool = iopool;
}

void Network::setPadding(std::vector<int>& padding_vec)
{
	for(int& i : padding_vec)
	{
		this->padding.push_back(i);
	}
}

int Network::getID()
{
	return this->net_id;
}

void Network::setupLayer()
{
}

void Network::setDType(Tinfo t)
{
	this->Dtype = t;
}

void Network::setMyThead(std::thread* t)
{
	this->my_thread = t;
}

void Network::preset_forward()
{
	this->check_input();
    
	// run child
    for(Network* net : this->child_networks)
	{
		net->setMyThead(new std::thread(&Network::forward, net));
	}
}

Ninfo Network::getNetworkType()
{
	return this->network_type;
}


std::vector<int>& Network::getPoolSizeVec()
{
	return this->pool_size;
}

std::vector<int>& Network::getStrideVec()
{
	return this->stride;
}

std::vector<int>& Network::getSizeVec()
{
	return this->size;
}

int Network::getFilters()
{
	return this->filters;
}

std::vector<int>& Network::getShapeVec()
{
	return this->shape;
}

int Network::getUnits()
{
	return this->units;
}