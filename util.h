#ifndef __UTIL
#define __UTIL

#include <string>
#include <iostream>

class Util{

public:
       
    static std::string trim(std::string& str)
    {
        size_t first = str.find_first_not_of(" \t\r\n;");
        size_t last = str.find_last_not_of(" \t\r\n;");
        return str.substr(first, (last-first+1));
    }

    static std::string intToStr(int i){
        std::ostringstream ss;
  		ss << i;
  		return ss.str();
    }
    
    static int strToInt(std::string s){
        int i = 0;
        std::istringstream ss(s);
  		ss >> i;
  		return i;
    }
};

#endif
