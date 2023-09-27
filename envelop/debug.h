#ifndef __DEBUG__L
#define __DEBUG__L

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define RED_t "\033[31m"
#define YELLOW_t "\033[33m"
#define GREEN_t "\033[32m"
#define WRITE "\033[0m"

    
#define STDIO_INIT std::ios_base::sync_with_stdio(false)

#define _S(n) std::to_string(n)

#include <sstream>
static std::string ArgToString(const char* value) {
    return  std::string(value);
}

static std::string ArgToString(char* value) {
    return  std::string(value);
}
template<int N>
std::string ArgToString(char(&s)[N]) {
    return  std::string(s);
}
template<int N>
std::string ArgToString(const char(&s)[N]) {
    return  std::string(s);
}

static std::string ArgToString(const std::string & str){
    return str;
}


template <typename T>
std::string ArgToString(T value) {
    return  std::to_string(value);
}

template <typename T>
void make_args_vect(std::vector<std::string>& vec, T t) {
    vec.push_back(ArgToString(t));
}
template<typename T, typename ...Ts>
void make_args_vect(std::vector<std::string>& vec, T t, Ts...  ts) {
    vec.push_back(ArgToString(t));
    make_args_vect(vec, ts...);
}

static void make_args_vect(std::vector<std::string>& vec){

}

class Sutil {
public:
    template<typename T, typename... Ts>
    static std::string Format(const T& str, const Ts &... args) {
        std::vector<std::string> allArgs;
        make_args_vect(allArgs, args...);
        return BuildFormatTarget(ArgToString(str), allArgs);
    }


private:
    static std::string  BuildFormatTarget(const std::string& str, const std::vector<std::string>& allarg) {
        int arg_s = 0;
        int index = 0;
        std::stringstream svl;
        for (; index < str.size(); index++) {
            if (str[index] == '%' &&
                index != str.size() - 1 &&
                str[index + 1] == 's' &&
                arg_s < allarg.size()) {
                svl << allarg[arg_s];
                index += 1;
                arg_s++;
                continue;
            }
            svl << str[index];
        }
        return svl.str();
    }


};
#define BASECOLOER "\033[0m"
#define errorL(msg,...) \
	std::cout << RED_t <<"Error:["<< __FILE__  << ":"<< __LINE__ << "]:"<< Sutil::Format(msg, ##__VA_ARGS__) <<BASECOLOER<< std::endl;
#define debugL(msg,...) \
	std::cout << YELLOW_t <<"debug:["<< __FILE__ << ":"<< __LINE__ << "]:"<< Sutil::Format(msg, ##__VA_ARGS__) <<BASECOLOER<< std::endl;
#define infoL(msg,...) \
    std::cout << GREEN_t <<"debug:["<< __FILE__ << ":" << __LINE__ << "]:"<<  Sutil::Format(msg, ##__VA_ARGS__)<< BASECOLOER <<std::endl;


#endif // !__DEBUG__L


