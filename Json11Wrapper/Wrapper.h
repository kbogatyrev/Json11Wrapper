#ifndef C_WRAPPER_H_INCLUDED
#define C_WRAPPER_H_INCLUDED

#include <string>
#include "json11.hpp"
#include "EString.h"

using namespace Hlib;

enum ET_Json11_Value_Type
{
    JSON11_VALUE_UNDEFINED,
    JSON11_VALUE_NULL,
    JSON11_VALUE_DOUBLE,
    JSON11_VALUE_INT,
    JSON11_VALUE_BOOL,
    JSON11_VALUE_STRING,
    JSON11_VALUE_ARRAY,
    JSON11_VALUE_OBJECT,
    JSON11_VALUE_COUNT
};

struct CJson11Value
{
    ET_Json11_Value_Type m_eType;
    double m_dValue;
    int m_iValue;
    bool m_bValue;
    CEString m_sValue;
    json11::Json m_json11Value;
};

class CJson11Wrapper
{
public:
    CJson11Wrapper();
    CJson11Wrapper(const CEString& sSource);
    ~CJson11Wrapper();

    json11::Json GetTopJsonObject();

    bool bParse(const CEString& sSource);
    bool bGetValues(json11::Json JsonObject, const CEString& sKey, vector<CJson11Value>& vecValues);

protected:
    json11::Json m_JsonParser;
    bool bGetScalarValue(json11::Json JsonObject, const CEString& sKey, CJson11Value& Value);
};

#endif
