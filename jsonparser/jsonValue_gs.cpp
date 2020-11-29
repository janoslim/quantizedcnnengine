#include "./jsonValue.h"

#include <string>
#include <vector>

using namespace _json_parser_qt;

void JsonNumber::setValue(std::string& str)
{
    this->intval = std::stoi(str);   
}

void JsonBoolean::setValue(JBOOL j)
{
    if(j == JBOOL::TRUE)
        this->val = true;
    else if (j == JBOOL::FALSE)
        this->val = false;
    else if (j == JBOOL::JNULL)
        this->val = NULL;
}

std::vector<std::pair<JsonString*, JsonValue*>>* JsonObject::getValue()
{
    return &(this->attribute_vector);
}

std::string JsonString::getValue()
{
    return this->str;  
}

std::vector<JsonValue*>* JsonArray::getValue()
{
    return &(this->member_vector);
}

JsonBoolean* JsonBoolean::getValue()
{
    
}

int JsonNumber::getValue()
{
    return this->intval;
}