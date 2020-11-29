#ifndef NETWORK_H
#define NETWORK_H

#include "../io/io.h"
#include "../io/iopool.h"
#include <vector>
#include <thread>

enum class NETWORKTYPE
{
	NETWORK,
	RESHAPE,
	CONV2D,
	MAXPOOL2D,
	FLATTEN,
	DENSE
};

enum class ACTTYPE
{
	LINEAR,
	RELU
};

enum class PADDINGTYPE
{
	VALID
};

class Network
{
private:
// attributes
	IOPool* iopool;
	int id;
	int output_id;
	int filters;
	std::vector<int> input_id;
	std::vector<int> pool_size;
	std::vector<int> stride;
	std::vector<int> size;
	std::thread* my_thread;
	std::vector<Network*> child_networks;
	NETWORKTYPE network_type;
	ACTTYPE act_type;
	PADDINGTYPE padding;
	std::vector<int> shape;
	int units;

	void check_input();
public:
	Network(IOPool* iopool);
	~Network();
	void forward();
	void wait_thread();
	void setId(int id);
	void setInputId(std::vector<int>& id_vec);
	void setOutputId(int id);
	void add_network(Network* network);
	void setNetworkType(NETWORKTYPE);
	void setActType(ACTTYPE);
	void setShape(std::vector<int>&);
	void setUnits(int);
	void setPoolSize(std::vector<int>&);
	void setStride(std::vector<int>&);
	void setSize(std::vector<int>&);
	void setFilter(int);
	void setPadding(PADDINGTYPE);
	int getID();
	IOPool* getIOPool();
};
#endif
