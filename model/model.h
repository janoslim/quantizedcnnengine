#ifndef MODEL_H
#define MODEL_H

#include "../network/network.h"
#include "../io/iopool.h"
#include "../jsonparser/jsonParser.h"
#include "../jsonparser/jsonValue.h"

using namespace _json_parser_qt;
class Model
{
private:
    Network* rootNetwork;
    Network* makeNetwork(JsonObject*, IOPool&);
public:
    Model();
    ~Model();
    Network* makeObject(JsonParser&, IOPool&);
    Network* geRootNetwork();
};

#endif