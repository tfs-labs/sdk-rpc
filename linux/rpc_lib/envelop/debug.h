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

#define errorL(msg) \
	std::cout << RED_t <<"Error:["<< __FILE__  << ":"<< __LINE__ << "]:"<< msg << WRITE <<std::endl;
#define debugL(msg) \
	std::cout << YELLOW_t <<"debug:["<< __FILE__ << ":"<< __LINE__ << "]:"<< msg << WRITE << std::endl;
#define infoL(msg) \
	std::cout << GREEN_t <<"infor:["<< __FILE__ << ":" << __LINE__ << "]:"<< msg << WRITE << std::endl;

#define _S(n) std::to_string(n)



#endif // !__DEBUG__L


