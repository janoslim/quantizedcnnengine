#include "./jsonValue.h"

#include <string>
#include <vector>

using namespace _json_parser_qt;

//

void JsonObject::pushPair(JsonString* jsonStringPtr, JsonValue* jsonValuePtr)
{
    this->attribute_vector.push_back(std::pair<JsonString*, JsonValue*>(jsonStringPtr, jsonValuePtr));
}

void JsonArray::pushMember(JsonValue* jsonValuePtr)
{
    this->member_vector.push_back(jsonValuePtr);
}

void JsonString::pushChar(char c)
{
    this->str.push_back(c);
}