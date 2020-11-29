#include <iostream>
#include "../network/network.h"
#include "../io/io.h"
#include "../io/iopool.h"
#include "../jsonparser/jsonValue.h"
#include "../jsonparser/jsonParser.h"
#include "../model/model.h"

using namespace _json_parser_qt;

int main()
{
	JsonParser* jsonParser = new JsonParser();
	jsonParser->readJsonFile("./networkModel.json");
	//jsonParser->printResult();
	
	IOPool* iopool = new IOPool();
	Model mainModel;
	
	mainModel.makeObject(*jsonParser, *iopool);
	iopool->finish_input(-1);
	mainModel.geRootNetwork()->forward();
	
}
