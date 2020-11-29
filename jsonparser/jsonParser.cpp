#include "./jsonParser.h"
#include "./jsonValue.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace _json_parser_qt;

void JsonParser::parse(std::ifstream& fileObj)
{
    char character;
    while(fileObj.get(character))
    {
        switch(character)
        {
            case ' ': case '\n': case '\t':
                break;
            case '{': // start of json object
                this->mainObject = this->stateObject(fileObj);
                break;
            default:
            {
                try 
                {
                    this->parseError(ERRORTYPE::NOTSPECIFIED);
                }
                catch(int exception)
                {
                    std::cout << "Line:31 char: " << character << std::endl; 
                }
            }
        }
    }
    
}

void JsonParser::readJsonFile(char* filePath)
{
    std::ifstream netFile;
    netFile.open(filePath);
    

    if(netFile.is_open())
    {
        this->parse(netFile);
    }
    else
    {
        std::cout << "Cannot open Network File" << std::endl;
        exit(0);

    }
}

void JsonParser::parseError(ERRORTYPE errotype)
{
    switch(errotype)
    {
        case ERRORTYPE::VALUEONKEY:
            std::cout << "ERROR:: VALUEONKEY error." << std::endl;
            break;
        case ERRORTYPE::VALUEONVALUE:
            std::cout << "ERROR::  VALUEONVALUE error." << std::endl;
            break;
        case ERRORTYPE::NOTSPECIFIED:
            std::cout << "ERROR::NOTSPECIFIED error." << std::endl;
            break;
        case ERRORTYPE::WRONGCHAR:
            std::cout << "ERROR::WRONGCHAR error." << std::endl;
            break;
    }
    throw 0;
}

JsonObject* JsonParser::stateObject(std::ifstream& fileObj)
{
    char character;
    int keyFlag = 0; // zero for key 1 for value
    JsonObject* jsonObject = new JsonObject();
    JsonString* keyStringPtr;
    JsonValue* jsonValuePtr;
    while(fileObj.get(character))
    {
        switch(character)
        {
            case ' ': case '\n': case '\t':
                break;
            case '"': // start of json object
                if(!keyFlag)
                    keyStringPtr = this->stateString(fileObj);
                else
                    jsonValuePtr = this->stateString(fileObj);
                break;
            case ':':
                if(keyFlag != 0)
                {
                    try { this->parseError(ERRORTYPE::VALUEONVALUE); }
                    catch(int exception) { std::cout << "Line:100 char: " << character << std::endl;  }   
                }
                keyFlag = 1;
                break;
            case 'n': case 't': case 'f':
                if(keyFlag != 1)
                {
                    try { this->parseError(ERRORTYPE::VALUEONKEY); }
                    catch(int exception) { std::cout << "Line:108 char: " << character << std::endl;  } 
                }
                jsonValuePtr = this->stateBoolean(fileObj);
                break;
            case '0': case '1': case '2': case '3': case '4': case '-':
            case '5': case '6': case '7': case '8': case '9':
                if(keyFlag != 1)
                {
                    try { this->parseError(ERRORTYPE::VALUEONKEY); }
                    catch(int exception) { std::cout << "Line:117 char: " << character << std::endl;  } 
                }
                jsonValuePtr = this->stateNumber(fileObj, character);
                break;
            case '[':
                if(keyFlag != 1)
                {
                    try { this->parseError(ERRORTYPE::VALUEONKEY); }
                    catch(int exception) { std::cout << "Line:125 char: " << character << std::endl;  } 
                }
                jsonValuePtr = this->stateArray(fileObj);
                break;
            case '{':
                if(keyFlag != 1)
                {
                    try { this->parseError(ERRORTYPE::VALUEONKEY); }
                    catch(int exception) { std::cout << "Line:133 char: " << character << std::endl;  } 
                }
                jsonValuePtr = this->stateObject(fileObj);
                break;
            case '}': // end of object
                if(keyFlag != 1)
                {
                    try { this->parseError(ERRORTYPE::VALUEONKEY); }
                    catch(int exception) { std::cout << "Line:141 char: " << character << std::endl;  } 
                }
                jsonObject->pushPair(keyStringPtr, jsonValuePtr);
                return jsonObject;
            case ',':
                if(keyFlag != 1)
                {
                    try { this->parseError(ERRORTYPE::VALUEONKEY); }
                    catch(int exception) { std::cout << "Line:149 char: " << character << std::endl;  }
                }
                jsonObject->pushPair(keyStringPtr, jsonValuePtr);
                keyFlag = 0;
                break;
            default:
            {
                this->parseError(ERRORTYPE::NOTSPECIFIED);
            }
        }
    }
    return NULL;
}

JsonNumber* JsonParser::stateNumber(std::ifstream& fileObj, char c)
{
    std::string str = "";
    str.push_back(c);
    
    char character;
    JsonNumber* jsonNumber = new JsonNumber();
    while(fileObj.get(character))
    {
        switch(character)
        {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                str.push_back(character);
                break; 
            default:
                fileObj.seekg(-1, std::ios::cur); 
                jsonNumber->setValue(str);
                return jsonNumber;
        }
    }
    return NULL;
}

JsonBoolean* JsonParser::stateBoolean(std::ifstream& fileObj)
{
    char character;
    JsonBoolean* jsonBoolean = new JsonBoolean();
    while(fileObj.get(character))
    {
        switch(character)
        {
            case 'r':
                fileObj.get(character);
                if(character != 'u') 
                {
                    try { this->parseError(ERRORTYPE::WRONGCHAR); }
                    catch(int exception) { std::cout << "Line:200 char: " << character << std::endl;  }
                }
                fileObj.get(character);
                if(character != 'e') this->parseError(ERRORTYPE::WRONGCHAR);
                jsonBoolean->setValue(JBOOL::TRUE);
                return jsonBoolean;
            case 'a':
                fileObj.get(character);
                if(character != 'l') 
                {
                    try { this->parseError(ERRORTYPE::WRONGCHAR); }
                    catch(int exception) { std::cout << "Line:211 char: " << character << std::endl;  }
                }
                fileObj.get(character);
                if(character != 's')
                {
                    try { this->parseError(ERRORTYPE::WRONGCHAR); }
                    catch(int exception) { std::cout << "Line:217 char: " << character << std::endl;  }
                }
                fileObj.get(character);
                if(character != 'e')
                {
                    try { this->parseError(ERRORTYPE::WRONGCHAR); }
                    catch(int exception) { std::cout << "Line:223 char: " << character << std::endl;  }
                }
                jsonBoolean->setValue(JBOOL::FALSE);
                return jsonBoolean;
            case 'u':
                fileObj.get(character);
                if(character != 'l')
                {
                    try { this->parseError(ERRORTYPE::WRONGCHAR); }
                    catch(int exception) { std::cout << "Line:232 char: " << character << std::endl;  }
                }
                fileObj.get(character);
                if(character != 'l')
                {
                    try { this->parseError(ERRORTYPE::WRONGCHAR); }
                    catch(int exception) { std::cout << "Line:238 char: " << character << std::endl;  }
                }
                jsonBoolean->setValue(JBOOL::JNULL);
                return jsonBoolean;
            default:
                this->parseError(ERRORTYPE::NOTSPECIFIED);
        }
    }
    return NULL;
}

JsonArray* JsonParser::stateArray(std::ifstream& fileObj)
{
    char character;
    int valueFlag = 0;
    JsonValue* jsonValuePtr;
    JsonArray* jsonArrayPtr = new JsonArray();
    while(fileObj.get(character))
    {
        switch(character)
        {
            case ' ': case '\n': case '\t':
                break;
            case ']': // end of jsonString
                if(valueFlag == 1)
                    jsonArrayPtr->pushMember(jsonValuePtr);
                return jsonArrayPtr;
            case ',':
                jsonArrayPtr->pushMember(jsonValuePtr);
                valueFlag = 0;
                break;
            case '"':
                jsonValuePtr = this->stateString(fileObj);
                valueFlag = 1;
                break;
                case 'n': case 't': case 'f':
                jsonValuePtr = this->stateBoolean(fileObj);
                valueFlag = 1;
                break;
            case '0': case '1': case '2': case '3': case '4': case '-':
            case '5': case '6': case '7': case '8': case '9':
                jsonValuePtr = this->stateNumber(fileObj, character);
                valueFlag = 1;
                break;
            case '[':
                jsonValuePtr = this->stateArray(fileObj);
                valueFlag = 1;
                break;
            case '{':
                jsonValuePtr = this->stateObject(fileObj);
                valueFlag = 1;
                break;
            default:
                {
                    try { this->parseError(ERRORTYPE::NOTSPECIFIED); }
                    catch(int exception) { std::cout << "Line:289 char: " << character << std::endl;  }
                }
        }
    }
    return NULL;
}

JsonString* JsonParser::stateString(std::ifstream& fileObj)
{
    char character;
    JsonString* jsonStringPtr = new JsonString();

    while(fileObj.get(character))
    {
        switch(character)
        {
            case '"': // end of jsonString
                return jsonStringPtr;
            default:
                jsonStringPtr->pushChar(character);
        }
    }
    return NULL;
}

void JsonParser::printResult()
{
    std::cout << "PRINT RESULT" << std::endl;
    this->mainObject->printValue();
}

JsonParser::JsonParser()
{
    this->mainObject = new JsonObject();
}

JsonParser::~JsonParser()
{
    delete this->mainObject;
}

JsonObject* JsonParser::getMainObject()
{
    return this->mainObject;
}