#include "./jsonValue.h"

#include <string>
#include <vector>

using namespace _json_parser_qt;

JsonValue::JsonValue() 
{
}

JsonValue::~JsonValue()
{
}
//

JsonObject::JsonObject()
{
}

JsonObject::~JsonObject()
{
}

JsonArray::JsonArray()
{
}

JsonArray::~JsonArray()
{
}

JsonNumber::JsonNumber()
{
}

JsonNumber::~JsonNumber()
{
}

JsonString::JsonString()
{
    this->str = "";
}

JsonString::~JsonString()
{
}

JsonBoolean::JsonBoolean()
{
}

JsonBoolean::~JsonBoolean()
{
}