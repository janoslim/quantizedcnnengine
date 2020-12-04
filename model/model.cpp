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
    IO* io_start = new IO(-1);
    IO* io_end = new IO(this->rootNetwork->getID());
    this->rootNetwork->getIOPool()->add_IO(io_start);
    this->rootNetwork->getIOPool()->add_IO(io_end);
    this->distributeWBParameters();
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

            JsonString* jsonStr = dynamic_cast<JsonString*>(jsonValue);
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
                CONVOLUTIONAL_LAYER* conv2dObj = new CONVOLUTIONAL_LAYER(&iopool);
                networkObj = dynamic_cast<Network*>(conv2dObj);
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
            std::vector<JsonValue*>* member_vec = dynamic_cast<JsonArray*>(jsonValue)->getValue();
            for(JsonValue* netObject : *member_vec) // netObject은 { network: {} }
            {  
                std::vector<std::pair<JsonString*, JsonValue*>>* netValueVector = dynamic_cast<JsonObject*>(netObject)->getValue();
                Network* subnet = this->makeNetwork(dynamic_cast<JsonObject*>(netValueVector->front().second), iopool);
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
            JsonNumber* jsonId = dynamic_cast<JsonNumber*>(jsonValue);
            networkObj->setId(jsonId->getValue());
            networkObj->setOutputId(jsonId->getValue());
        }
        else if(key.compare("units") == 0)
        {
            JsonNumber* jsonId = dynamic_cast<JsonNumber*>(jsonValue);
            networkObj->setUnits(jsonId->getValue());
        }
        else if(key.compare("shape") == 0)
        {
            std::vector<JsonValue*>* mem_vec = dynamic_cast<JsonArray*>(jsonValue)->getValue();
            std::vector<int> shapeVec;
            for(JsonValue* shapeNum : *mem_vec)
            {
                shapeVec.push_back((dynamic_cast<JsonNumber*>(shapeNum))->getValue());
            }
            networkObj->setShape(shapeVec);
        }
        else if(key.compare("act_type") == 0)
        {
            JsonString* jsonStr = dynamic_cast<JsonString*>(jsonValue);
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
            JsonNumber* jsonFilter = dynamic_cast<JsonNumber*>(jsonValue);
            networkObj->setFilter(jsonFilter->getValue());
        }
        else if(key.compare("size") == 0)
        {
            std::vector<JsonValue*>* mem_vec = dynamic_cast<JsonArray*>(jsonValue)->getValue();
            std::vector<int> sizeVec;
            for(JsonValue* sizeNum : *mem_vec)
            {
                sizeVec.push_back(((JsonNumber*)sizeNum)->getValue());
            }
            networkObj->setSize(sizeVec);
        }
        else if(key.compare("input") == 0)
        {
            std::vector<JsonValue*>* mem_vec = dynamic_cast<JsonArray*>(jsonValue)->getValue();
            std::vector<int> inputVec;
            for(JsonValue* inputNum : *mem_vec)
            {
                inputVec.push_back(((JsonNumber*)inputNum)->getValue());
            }
            networkObj->setInputId(inputVec);
        }
        else if(key.compare("stride") == 0)
        {
            std::vector<JsonValue*>* mem_vec = dynamic_cast<JsonArray*>(jsonValue)->getValue();
            std::vector<int> strideVec;
            for(JsonValue* strideNum : *mem_vec)
            {
                strideVec.push_back(((JsonNumber*)strideNum)->getValue());
            }
            networkObj->setStride(strideVec);
        }
        else if(key.compare("pool_size") == 0)
        {
            std::vector<JsonValue*>* mem_vec = dynamic_cast<JsonArray*>(jsonValue)->getValue();
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
        else if(key.compare("type") == 0)
        {}
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

    // make layer
    this->enqueueWNNQ(networkObj);

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


void Model::enqueueWNNQ(Network* network)
{
    this->weightNeededNetworksQueue.push(network);
}

void Model::distributeWBParameters()
{
    // read file
    std::ifstream wbParamFile;
    wbParamFile.open(this->weightPath, std::ios::binary);

    int max = this->weightNeededNetworksQueue.size();
    for(int i = 0; i < max; i++)
    {
        Network* networkObj = this->weightNeededNetworksQueue.top();
        
        switch (networkObj->getNetworkType())
        {
        case NETWORKTYPE::CONV2D:
            {
                CONVOLUTIONAL_LAYER* convObj = dynamic_cast<CONVOLUTIONAL_LAYER*>(networkObj);
                std::vector<int>& size = convObj->getSizeVec();
                int filter = convObj->getFilters();
                int weightC = size[0]*size[1]*filter;
	            int biasC = filter;
                convObj->weightFptr = new float[weightC];
                convObj->biasFptr = new float[biasC];
                wbParamFile.read(reinterpret_cast<char*>(convObj->weightFptr), weightC*sizeof(float));
                wbParamFile.read(reinterpret_cast<char*>(convObj->biasFptr), biasC*sizeof(float));
                convObj->make();
            }
            break;
        case NETWORKTYPE::DENSE:
            {
                DENSE_LAYER* denseObj = dynamic_cast<DENSE_LAYER*>(networkObj);
                int weightShape = denseObj->getShapeVec()[0] * denseObj->getUnits();
                int biasShape = denseObj->getUnits();
                denseObj->weightFptr = new float[weightShape];
                denseObj->biasFptr = new float[biasShape];
                wbParamFile.read(reinterpret_cast<char*>(denseObj->weightFptr), weightShape*sizeof(float));
                wbParamFile.read(reinterpret_cast<char*>(denseObj->biasFptr), biasShape*sizeof(float));
                denseObj->make();
            }
            break;
        case NETWORKTYPE::MAXPOOL2D:
            {
                MAXPOOL_LAYER* maxpoolObj = dynamic_cast<MAXPOOL_LAYER*>(networkObj);
                maxpoolObj->make();
            }
            break;
        default:
            break;
        }

        this->weightNeededNetworksQueue.pop();
    }
}

void Model::setWeightPath(std::string& str)
{
    this->weightPath = str;
}
