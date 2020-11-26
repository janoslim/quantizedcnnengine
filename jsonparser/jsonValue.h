#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <string>
#include <vector>

namespace _json_parser_qt
{
    enum class JsonType
    {
        OBJECT,
        ARRAY,
        NUMBER,
        STRING,
        BOOLEAN,
        JNULL
    };

    enum class JBOOL
    {
        TRUE,
        FALSE,
        JNULL
    };

    class JsonValue
    {
    private:
        
    public:
        JsonValue();
        ~JsonValue();
        virtual JsonValue* getValue() = 0;
        virtual void printValue() = 0;
    };

    class JsonArray : public JsonValue
    {
    private:
        std::vector<JsonValue> member_vector;
    public:
        JsonArray();
        ~JsonArray();
        void pushMember(JsonValue*);
        JsonArray* getValue();
        void printValue();
    };

    class JsonNumber : public JsonValue
    {
    private:
        
    public:
        JsonNumber();
        ~JsonNumber();
        JsonNumber* getValue();
        void setValue(std::string&);
        void printValue();
    };

    class JsonString : public JsonValue
    {
    private:
        std::string str;
    public:
        JsonString();
        ~JsonString();
        void pushChar(char c);
        JsonString* getValue();
        void printValue();
    };

    class JsonBoolean : public JsonValue
    {
    private:
        bool val;
    public:
        JsonBoolean();
        ~JsonBoolean();
        JsonBoolean* getValue();
        void setValue(JBOOL);
        void printValue();
    };

    class JsonObject : public JsonValue
    {
    private:
        std::vector<std::pair<JsonString*, JsonValue*>> attribute_vector;
    public:
        JsonObject();
        ~JsonObject();
        void pushPair(JsonString*, JsonValue*);
        JsonObject* getValue();
        void printValue();
    };
}

#endif