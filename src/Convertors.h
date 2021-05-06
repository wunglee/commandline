#ifndef ARGS_CONVERTORS_H
#define ARGS_CONVERTORS_H
#include <boost/algorithm/string/trim.hpp>
#include "Exceptions.h"
class Convertors{
public:
    static std::string converToString(std::string valueString) {
        boost::trim(valueString);
        return valueString;
    }
    static int convertToInt(const std::string &intString) {
        try{
            return stoi(intString);
        }catch(...){
            throw InvalidValueException("无效的整型参数值");
        }
    }
    static bool convertTobool(const std::string &boolString) {
        if (boolString != "true" && boolString != "false") {
            throw InvalidValueException("无效的布尔参数值");
        }
        return boolString=="true" ? true : false;
    }
};
#endif //ARGS_CONVERTORS_H
