#ifndef ARGS_CONVERTORS_H
#define ARGS_CONVERTORS_H
#include <boost/algorithm/string/trim.hpp>
#include "Exceptions.h"
#include <boost/format.hpp>
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
            boost::format f = boost::format("无效的整型参数值:%s")%intString;
            throw InvalidValueException(f.str());
        }
    }
    static bool convertTobool(const std::string &boolString) {
        if (boolString != "true" && boolString != "false") {
            boost::format f = boost::format("无效的布尔参数值:%s")%boolString;
            throw InvalidValueException(f.str());
        }
        return boolString=="true" ? true : false;
    }
};
#endif //ARGS_CONVERTORS_H
