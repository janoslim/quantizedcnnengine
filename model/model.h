#ifndef MODEL_H
#define MODEL_H

#include "../network/network.h"
#include "../type/iopool.h"
#include "../jsonparser/jsonParser.h"
#include "../jsonparser/jsonValue.h"
#include <queue>

using namespace _json_parser_qt;

struct comparePr
{
    bool operator()(Network* n1, Network* n2)
    {
        int id1 = n1->getID();
        int id2 = n2->getID();
        if(id1 == id2)
        {
            std::cout << "Compare priority error!\n" << std::endl;
            exit(-1);
        }
        else if(id1 > id2)
        {
            return true;
        }
        else
            return false;
    }
};
class Model
{
private:
    Network* rootNetwork;
    Network* makeNetwork(JsonObject*, IOPool&);
    std::string weightPath;
    std::priority_queue<Network*, std::vector<Network*>, comparePr> weightNeededNetworksQueue;  
public:
    Model();
    ~Model();
    Network* makeObject(JsonParser&, IOPool&);
    Network* getRootNetwork();
    void setWeightPath(std::string&);
    void enqueueWNNQ(Network*);
    void distributeWBParameters();
};



#endif