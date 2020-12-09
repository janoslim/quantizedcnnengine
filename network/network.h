#ifndef NETWORK_H
#define NETWORK_H

#include "../type/io.h"
#include "../type/iopool.h"
#include <vector>
#include <thread>

enum class Ninfo
{
	NETWORK,
	RESHAPE,
	CONV2D,
	MAXPOOL2D,
	FLATTEN,
	DENSE
};

enum Ainfo {
    LINEAR,
    LOGISTIC,
    LOGGY,
    RELU,
    RELU6,
    ELU,
    SELU,
    GELU,
    RELIE,
    RAMP,
    LEAKY,
    TANH,
    PLSE,
    STAIR,
    HARDTAN,
    LHTAN,
};

class Network
{
protected:
// attributes
	IOPool* iopool;

	int net_id;
	std::vector<int> input_id;
	int output_id;
	std::vector<int> shape;
	Tinfo Dtype;

	int filters;
	int units;
	std::vector<int> size;
	std::vector<int> pool_size;
	std::vector<int> stride;
	std::vector<int> padding;

	std::thread* my_thread;
	std::vector<Network*> child_networks;

	Ninfo network_type;
	Ainfo act_type;
	
	void check_input();

public:
	Network(IOPool* iopool);
	virtual ~Network();

	void setIOPool(IOPool*);
	void setId(int id);
	void setDType(Tinfo);
	void setInputId(std::vector<int>& id_vec);
	void setOutputId(int id);
	void setShape(std::vector<int>&);

	void setNetworkType(Ninfo);
	void setActType(Ainfo);

	void add_network(Network* network);

	void setUnits(int);
	void setFilter(int);
	void setSize(std::vector<int>&);
	void setPoolSize(std::vector<int>&);
	void setStride(std::vector<int>&);
	void setPadding(std::vector<int>&);

	void setMyThead(std::thread*);
	void wait_thread();


	int getID();
	Ninfo getNetworkType();
	IOPool* getIOPool();
	int getUnits();
	int getFilters();
	std::vector<int>& getShapeVec();
	std::vector<int>& getSizeVec();
	std::vector<int>& getPoolSizeVec();
	std::vector<int>& getStrideVec();


	void preset_forward();
	virtual void forward();
	// This function setup after makeObject()
	virtual void setupLayer();
};
#endif
