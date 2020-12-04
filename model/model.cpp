#include "../network/network.h"
#include "../type/iopool.h"
#include "../jsonparser/jsonParser.h"
#include "./model.h"
#include "../layer/activation_layer.h"
#include "../layer/convolutional_layer.h"
#include "../layer/dense_layer.h"
#include "../layer/maxpool_layer.h"
#include "../layer/softmax_layer.h"
#include <stdlib.h>

using namespace _json_parser_qt;

Network* Model::makeObject(JsonParser& jsonParser, IOPool& iopool)
{
    JsonObject* mainObject = jsonParser.getMainObject();
    std::vector<std::pair<JsonString*, JsonValue*>>* modelVector = mainObject->getValue();
    this->rootNetwork = this->makeNetwork((JsonObject*)modelVector->front().second, iopool);
    IO* io = new IO(-1);
    this->rootNetwork->getIOPool()->add_IO(io);
}

Network* Model::makeNetwork(JsonObject* networkObject, IOPool& iopool)
{   
    // DTYPE
    Tinfo Dtype = FLOAT;

    std::vector<std::pair<JsonString*, JsonValue*>>& networkAttr = *(networkObject->getValue());
    if(networkAttr.size() == 0)
        return NULL;
 
    JsonString* jsonKey;
    JsonValue* jsonValue;
    Network* networkObj;

    // network의 type을 먼저 확인하고 layer 객체를 만들어야함.
    for(std::pair<JsonString*, JsonValue*> kvPair : networkAttr)
    {
        jsonKey = kvPair.first;
        jsonValue = kvPair.second;
        std::string key = jsonKey->getValue();
        if(key.compare("type") == 0)
        {
            JsonString* jsonStr = (JsonString*)jsonValue;
            std::string typeStr = jsonStr->getValue();
            
            if(typeStr.compare("network") == 0) 
            {
                networkObj = new Network(&iopool);
                networkObj->setNetworkType(NETWORKTYPE::NETWORK);
            }
            /* else if(typeStr.compare("reshape") == 0) 
            {
                networkObj = new Network(&iopool);
                networkObj->setNetworkType(NETWORKTYPE::RESHAPE);
            } */
            else if(typeStr.compare("conv2d") == 0) 
            {
                networkObj = new CONVOLUTIONAL_LAYER(&iopool);
                networkObj->setNetworkType(NETWORKTYPE::CONV2D);
            }
            else if(typeStr.compare("max_pooling2d") == 0) 
            {
                networkObj = new MAXPOOL_LAYER(&iopool);
                networkObj->setNetworkType(NETWORKTYPE::MAXPOOL2D);
            }
            /* else if(typeStr.compare("flatten") == 0) 
            {
                networkObj = new Network(&iopool);
                networkObj->setNetworkType(NETWORKTYPE::FLATTEN);
            } */
            else if(typeStr.compare("dense") == 0) 
            {
                networkObj = new DENSE_LAYER(&iopool);
                networkObj->setNetworkType(NETWORKTYPE::DENSE);
            }
            else
            {
                std::cout << "ERROR: Line 60 model.cpp" << std::endl;
                exit(0);
            }
        }
    }
    
    // 나머지 Network안 object의 Attribute을 검사한다
    for(std::pair<JsonString*, JsonValue*> kvPair : networkAttr)
    {
        jsonKey = kvPair.first;
        jsonValue = kvPair.second;
        std::string key = jsonKey->getValue();

        if(key.compare("subnet") == 0)
        {
            std::vector<JsonValue*>* member_vec = ((JsonArray*)jsonValue)->getValue();
            for(JsonValue* netObject : *member_vec) // netObject은 { network: {} }
            {  
                std::vector<std::pair<JsonString*, JsonValue*>>* netValueVector = ((JsonObject*)netObject)->getValue();
                Network* subnet = this->makeNetwork((JsonObject*)netValueVector->front().second, iopool);
                if (subnet != NULL)
                {
                    networkObj->add_network(subnet);
                    IO* io = new IO(subnet->getID());
                    iopool.add_IO(io);
                }
                else
                {
                    std::cout << "SUBNET NULL!";
                }
            }
        }
        else if(key.compare("id") == 0)
        {
            JsonNumber* jsonId = (JsonNumber*)jsonValue;
            networkObj->setId(jsonId->getValue());
            networkObj->setOutputId(jsonId->getValue());
        }
        else if(key.compare("units") == 0)
        {
            JsonNumber* jsonId = (JsonNumber*)jsonValue;
            networkObj->setUnits(jsonId->getValue());
        }
        else if(key.compare("shape") == 0)
        {
            std::vector<JsonValue*>* mem_vec = ((JsonArray*)jsonValue)->getValue();
            std::vector<int> shapeVec;
            for(JsonValue* shapeNum : *mem_vec)
            {
                shapeVec.push_back(((JsonNumber*)shapeNum)->getValue());
            }
            networkObj->setShape(shapeVec);
        }
        else if(key.compare("act_type") == 0)
        {
            JsonString* jsonStr = (JsonString*)jsonValue;
            std::string acttypeStr = jsonStr->getValue();

            if(acttypeStr.compare("relu") == 0) {
                networkObj->setActType(ACTTYPE::RELU);
            }else if(acttypeStr.compare("linear") == 0) {
                networkObj->setActType(ACTTYPE::LINEAR);
            }else
            {
                std::cout << "ERROR: Line 91 model.cpp" << std::endl;
                exit(0);
            }
        }
        else if(key.compare("filters") == 0)
        {
            JsonNumber* jsonFilter = (JsonNumber*)jsonValue;
            networkObj->setFilter(jsonFilter->getValue());
        }
        else if(key.compare("size") == 0)
        {
            std::vector<JsonValue*>* mem_vec = ((JsonArray*)jsonValue)->getValue();
            std::vector<int> sizeVec;
            for(JsonValue* sizeNum : *mem_vec)
            {
                sizeVec.push_back(((JsonNumber*)sizeNum)->getValue());
            }
            networkObj->setSize(sizeVec);
        }
        else if(key.compare("input") == 0)
        {
            std::vector<JsonValue*>* mem_vec = ((JsonArray*)jsonValue)->getValue();
            std::vector<int> inputVec;
            for(JsonValue* inputNum : *mem_vec)
            {
                inputVec.push_back(((JsonNumber*)inputNum)->getValue());
            }
            networkObj->setInputId(inputVec);
        }
        else if(key.compare("stride") == 0)
        {
            std::vector<JsonValue*>* mem_vec = ((JsonArray*)jsonValue)->getValue();
            std::vector<int> strideVec;
            for(JsonValue* strideNum : *mem_vec)
            {
                strideVec.push_back(((JsonNumber*)strideNum)->getValue());
            }
            networkObj->setStride(strideVec);
        }
        else if(key.compare("pool_size") == 0)
        {
            std::vector<JsonValue*>* mem_vec = ((JsonArray*)jsonValue)->getValue();
            std::vector<int> poolVec;
            for(JsonValue* poolNum : *mem_vec)
            {
                poolVec.push_back(((JsonNumber*)poolNum)->getValue());
            }
            networkObj->setPoolSize(poolVec);
        }
        else if(key.compare("padding") == 0)
        {
            JsonString* jsonStr = (JsonString*)jsonValue;
            std::string paddingStr = jsonStr->getValue();

            if(paddingStr.compare("valid") == 0) {
                networkObj->setPadding(PADDINGTYPE::VALID);
            }else
            {
                std::cout << "ERROR: Line 139 model.cpp" << std::endl;
                exit(0);
            }
        }
        else
        {
            std::cout << key << std::endl;
            std::cout << "NOT SPECIFIED !" << std::endl;   
            exit(0);
        }
    }

    // set layer info
    networkObj->setDType(Dtype);
    networkObj->setupLayer();

    return networkObj;
}
Model::Model()
{
}

Model::~Model()
{
    delete this->rootNetwork;
}

Network* Model::geRootNetwork()
{
    return this->rootNetwork;
}