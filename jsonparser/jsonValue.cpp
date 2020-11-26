#include "./jsonValue.h"

#include <string>
#include <vector>

using namespace _json_parser_qt;

//
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

void JsonObject::pushPair(JsonString* str, JsonValue* jv)
{
    
}
//
JsonArray::JsonArray()
{
}

JsonArray::~JsonArray()
{
}

void JsonArray::pushMember(JsonValue* v)
{

}
//
JsonNumber::JsonNumber()
{
}

JsonNumber::~JsonNumber()
{
}


void JsonNumber::setValue(std::string& str)
{
}
//
JsonString::JsonString()
{
    this->str = "";
}

JsonString::~JsonString()
{
}

void JsonString::pushChar(char c)
{
    this->str.push_back(c);
}
//
JsonBoolean::JsonBoolean()
{
}

JsonBoolean::~JsonBoolean()
{
}

void JsonBoolean::setValue(JBOOL j)
{
}

void JsonObject::printValue()
{

}

void JsonString::printValue()
{
    
}

void JsonArray::printValue()
{
    
}

void JsonBoolean::printValue()
{
    
}

void JsonNumber::printValue()
{
    
}

JsonObject* JsonObject::getValue()
{

}

JsonString* JsonString::getValue()
{
    
}

JsonArray* JsonArray::getValue()
{
    
}

JsonBoolean* JsonBoolean::getValue()
{
    
}

JsonNumber* JsonNumber::getValue()
{
    
}




