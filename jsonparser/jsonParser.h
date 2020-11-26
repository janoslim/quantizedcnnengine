#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include "./jsonValue.h"

namespace _json_parser_qt 
{
    enum class ERRORTYPE
    {
        VALUEONKEY,
        VALUEONVALUE,
        NOTSPECIFIED,
        WRONGCHAR
    };

    class JsonParser
    {
    private:
        void parse(std::ifstream& fileObj);
        void parseError(enum ERRORTYPE);
        JsonObject* stateObject(std::ifstream& fileObj);
        JsonNumber* stateNumber(std::ifstream& fileObj, char c);
        JsonBoolean* stateBoolean(std::ifstream& fileObj);
        JsonArray* stateArray(std::ifstream& fileObj);
        JsonString* stateString(std::ifstream& fileObj);
    public:
        JsonParser();
        void readJsonFile(char* filePath);
    };

}


#endif