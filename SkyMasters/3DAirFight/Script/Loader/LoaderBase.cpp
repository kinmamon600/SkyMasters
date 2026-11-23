#include"LoaderBase.h"
#include"DxLib.h"
#include <sstream>
#include <stdexcept> 

int LoaderBase::StringToInt(const std::string& value)
{
    try {
        int numi = std::stoi(value);
        return numi;
    }
    catch (const std::invalid_argument& e) {
        // 数値として解釈できない場合
        printfDx("エラー: 数値ではない文字列です。\n");
    }
    catch (const std::out_of_range& e) {
        // intの範囲を超えている場合
        printfDx("エラー: 数値が範囲外です。\n");
    }
}

float LoaderBase::StringToFloat(const std::string& value)
{
    try {
        float numf = std::stof(value);
        return numf;
    }
    catch (const std::invalid_argument& e) {
        // 数値として解釈できない場合
        printfDx("エラー: 数値ではない文字列です。\n");
    }
    catch (const std::out_of_range& e) {
        // intの範囲を超えている場合
        printfDx("エラー: 数値が範囲外です。\n");
    }
}