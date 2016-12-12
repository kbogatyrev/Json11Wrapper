#include "Logging.h"
#include "Wrapper.h"

int main()
{
    const CEString sTest(LR"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})");
    CJson11Wrapper JsonParser(sTest);

    vector<CJson11Value> vecParsedJson;
    bool bRet = JsonParser.bGetValues(JsonParser.GetTopJsonObject(), L"k1", vecParsedJson);

    /*
    // Json parsing
    CEString sTestSource = LR"({"key1":"string_value", "key2":1234567.1234567, "key3":true})";
    b_ = sTestSource.bParseJsonString();
    if (b_)
    {
    CEString sValue;
    if (sTestSource.bGetJsonStringValue(CEString(L"key1"), sValue))
    {
    if (sValue != L"string_value")
    {
    ERROR_LOG(L"Error accessing Json string value");
    }
    }

    double dValue = 0.0;
    if (sTestSource.bGetJsonNumericValue(CEString(L"key2"), dValue))
    {
    if (dValue != 1234567.1234567)
    {
    ERROR_LOG(L"Error accessing Json numeric value");
    }
    }

    bool bValue = false;
    if (sTestSource.bGetJsonBooleanValue(CEString(L"key3"), bValue))
    {
    if (bValue != true)
    {
    ERROR_LOG(L"Error accessing Json Boolean value");
    }
    }
    }
    else
    {
    ERROR_LOG(L"Json parse failed.");
    }

    */

    return 0;
}