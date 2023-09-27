#pragma once
#include "base64.h"
#include <string>
class Base64
{
    std::string _base64_table;
    static const char base64_pad = '='; public:
    Base64()
    {
        _base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
    }
   
public:
    std::string Encode(const unsigned char* str, int bytes);
    std::string Decode(const char* str, int bytes);

};


char * toBase64(const char * src,int size);

char * toBase64(const std::string & str);

std::string FromBase64(const char * str,int size);

std::string FromBase64(const std::string & str);
