#include "interface.h"
#include "debug.h"
#include "sig.h"
#include "sigTx.h"
#include <cstring>
#include "base64.h"


   long long  import_base64_prikey_handler(const char *buf, int buf_size){
        infoL(buf);
        std::string dbase=FromBase64(buf,buf_size);
        debugL(dbase);
        return (long long)ImportEVP_PKEY((const unsigned char *)dbase.c_str(),dbase.size());
    }

char *  export_new_prikey_base64(){
         unsigned char * buf=NULL;
         int size_=0;
        ExportEVP_PKEY(&buf, &size_);
        char * buffer=toBase64((const char *)buf,size_);
        return (char *)buffer;
    }

  long long   import_prikey_handler_from_hex(const char *str){
        return (long long)ImportFromHexStr(str);
    }

  char *  export_new_prikey_to_hex(long long pkey){
        char * buf=NULL;
        int size_=0;
        ExportToHexStr((const void *)pkey, &buf, &size_);
        return buf;
    }

 char *  export_mnemonic_from_prikey_handler(long long pkey){
        char * buf=NULL;
        int size_=0;
        ExportMnemonic((const void *)pkey, &buf, &size_);
        return buf;
    }

  long long  import_prikey_handler_from_mnemonic(const char * mnemonic){
        return (long long)ImportFromMnemonic(mnemonic);
    }

  char *  get_base58addr(long long pkey){
        char * buf=NULL;
        int size_=0;
        getBase58addr_c((const void *)pkey, &buf, &size_);
        return buf;
    }

 char *  get_pubstr_base64(long long pkey){
        char * buf=NULL;
        int size_=0;
        //getPubStr_c((const void *)pkey, &buf,&size_);
        std::string ret=getPubStr((const void *)pkey);
        Base64 base_;
        std::string res=base_.Encode((const unsigned char *)ret.c_str(), ret.size());
        buf=(char *)malloc(res.size()+1);
        buf[res.size()]=0;
        memcpy(buf, res.c_str(), res.size());
        return buf;
    }


   char *   sig_tx(long long pkey,const char * message,int msize){
       std::string msg(message,msize);
       std::string res=toSig(msg, (void *)pkey);
       char * buf=(char *)malloc(res.size()+1);
       buf[res.size()]=0;
       memcpy(buf,res.c_str(),res.size());
       return buf;
    }

    void  free_prikey_handler(long long pkey){
        free_pkey((const void *)pkey);
    }