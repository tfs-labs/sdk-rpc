#ifndef __SIG_TX__
#define __SIG_TX__
#include "transaction.pb.h"
#include <string>

std::string testSig(CTransaction& tx ,void * pkey);


std::string toSig(const std::string& data,void * pkey);

void toSig_c (void * pkey,const char * data,int size_m,char ** buf,int *size);

#endif