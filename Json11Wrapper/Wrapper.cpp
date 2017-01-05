#include <cmath>
#include <string>
#include "Logging.h"
#include "Json11Wrapper.h"

CJson11Wrapper::CJson11Wrapper()
{}

CJson11Wrapper::CJson11Wrapper(const CEString& sSource)
{
    CEString sSourceCopy(sSource);
    bParse(sSourceCopy);
}

CJson11Wrapper::~CJson11Wrapper()
{}

json11::Json CJson11Wrapper::GetTopJsonObject()
{
    return m_JsonParser;
}

bool CJson11Wrapper::bParse(const CEString& sSource)
{
    std::string stl_sError;
    m_JsonParser = json11::Json::parse(const_cast<CEString&>(sSource).stl_sToUtf8(), stl_sError);
    if (stl_sError.length() > 0)
    {
        wstring wsMsg(L"Json parsing error: ");
        wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        wsMsg += converter.from_bytes(stl_sError).c_str();
        ERROR_LOG(wsMsg.c_str());
        return false;
    }

    return true;
}

bool CJson11Wrapper::bGetValues(json11::Json JsonObject, const CEString& sKey, vector<CJson11Value>& vecValues)
{
    if (m_JsonParser.is_null())
    {
        const wchar_t * szMsg = L"Error: Json object is null.";
        ERROR_LOG(szMsg);
        return false;
    }


    vecValues.clear();
    string stl_sKey = const_cast<CEString&>(sKey).stl_sToUtf8();
    if (JsonObject[stl_sKey].is_array())
    {
        for (auto& TheirValue : JsonObject[stl_sKey].array_items())
        {
            CJson11Value MyValue;
            if (TheirValue.is_number())
            {
                double dIntPart = 0.0;
                double dValue = TheirValue.number_value();
                double dFractPart = modf(dValue, &dIntPart);
                if (0 == dFractPart)
                {
                    MyValue.m_eType = JSON11_VALUE_INT;
                    MyValue.m_iValue = static_cast<int>(dIntPart);
                }
                else
                {
                    MyValue.m_eType = JSON11_VALUE_DOUBLE;
                    MyValue.m_dValue = dValue;
                }
            }
            else if (TheirValue.is_bool())
            {
                MyValue.m_eType = JSON11_VALUE_BOOL;
                MyValue.m_bValue = TheirValue.bool_value();
            }
            else if (TheirValue.is_string())
            {
                MyValue.m_eType = JSON11_VALUE_STRING;
                string stl_sKey = const_cast<CEString&>(sKey).stl_sToUtf8();
                string stl_sValue = JsonObject[stl_sKey].string_value();
                MyValue.m_sValue = CEString::sFromUtf8(stl_sValue);
            }
            else if (TheirValue.is_object())
            {
                MyValue.m_eType = JSON11_VALUE_OBJECT;
                MyValue.m_json11Value = TheirValue;
            }
            else
            {
                const wchar_t * szMsg = L"Error: Illegal Json value type.";
                ERROR_LOG(szMsg);
                return false;
            }

            vecValues.push_back(MyValue);
        }       //  for ...
    }       //  if (JsonObject[stl_sKey].is_array())
    else
    {
        CJson11Value Value;
        bool bRet = bGetScalarValue(JsonObject, sKey, Value);
        if (bRet)
        {
            vecValues.push_back(Value);
        }
    }

    return true;

}   //  bGetValues()

bool CJson11Wrapper::bGetScalarValue(json11::Json JsonObject, const CEString& sKey, CJson11Value& Value)
{
    if (m_JsonParser.is_null())
    {
        const wchar_t * szMsg = L"Error: Json object is null.";
        ERROR_LOG(szMsg);
        return false;
    }

    string stl_sKey = const_cast<CEString&>(sKey).stl_sToUtf8();

    CJson11Value Val;
    if (JsonObject[stl_sKey].is_number())
    {
        double dIntPart = 0.0;
        double dValue = m_JsonParser[stl_sKey].number_value();
        double dFractPart = modf(dValue, &dIntPart);
        if (0 == dFractPart)
        {
            Val.m_eType = JSON11_VALUE_INT;
            Val.m_iValue = static_cast<int>(dIntPart);
        }
        else
        {
            Val.m_eType = JSON11_VALUE_DOUBLE;
            Val.m_dValue = dValue;
        }
    }
    else if (JsonObject[stl_sKey].is_bool())
    {
        Val.m_eType = JSON11_VALUE_BOOL;
        Val.m_bValue = JsonObject[stl_sKey].bool_value();
    }
    else if (JsonObject[stl_sKey].is_string())
    {
        Val.m_eType = JSON11_VALUE_STRING;
        string stl_sKey = const_cast<CEString&>(sKey).stl_sToUtf8();
        string stl_sValue = JsonObject[stl_sKey].string_value();
        Val.m_sValue = CEString::sFromUtf8(stl_sValue);
    }
    else if (JsonObject[stl_sKey].is_object())
    {
        Val.m_eType = JSON11_VALUE_OBJECT;
        Val.m_json11Value = JsonObject[stl_sKey];
    }
    else if (JsonObject[stl_sKey].is_array())
    {
        const wchar_t * szMsg = L"Error: Unexpected Json value type.";
        ERROR_LOG(szMsg);
        return false;
    }
    else
    {
        const wchar_t * szMsg = L"Error: Illegal Json value type.";
        ERROR_LOG(szMsg);
        return false;
    }

    return true;
}
