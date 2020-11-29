#include "./jsonValue.h"

#include <string>
#include <vector>
#include <iostream>

using namespace _json_parser_qt;

void JsonObject::printValue()
{
    for(std::pair<JsonString*, JsonValue*> p : this->attribute_vector)
    {
        p.first->printValue();
        std::cout << ':';
        p.second->printValue();
        std::cout << std::endl;
    }
}

void JsonString::printValue()
{
    std::cout << this->str;
}

void JsonArray::printValue()
{
    std::cout << "[ ";
    for(JsonValue* val : this->member_vector)
    {
        val->printValue();
        std::cout << ", ";
    }
    std::cout << "]";
}

void JsonBoolean::printValue()
{
    if(this->val)
        std::cout << "True";
}

void JsonNumber::printValue()
{
    std::cout << this->intval;
}

