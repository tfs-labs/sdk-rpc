#include "sig.h"
#include "base58.h"
#include "bip39.h"
#include "debug.h"
#include "openssl/types.h"
#include <cstring>
#include <openssl/bio.h>
#include <openssl/core_names.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <utility>
#include <memory.h>
#include "hexcode.h"
#include "../envelop/bip39.h"








bool sig(const void * pkey, const std::string & message,std::string & value);

bool verf(const  void* pkey,const std::string &message, std::string &signature);

extern "C" {


EVP_PKEY * createEVP_KEY(){
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, NULL);
    if(ctx == nullptr)
    {
        EVP_PKEY_CTX_free(ctx);
    }

    if(EVP_PKEY_keygen_init(ctx) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        std::cout << "keygen init fail" << std::endl;
    }

    if(EVP_PKEY_keygen(ctx, &pkey) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        std::cout << "keygen fail\n" << std::endl;
    }

    EVP_PKEY_CTX_free(ctx);
    return pkey;
}

void *ImportEVP_PKEY(const unsigned char *buf, int buf_size) {
  EVP_PKEY *pkey = nullptr;
  BIO *bio = BIO_new_mem_buf((const void *)buf, buf_size);
  if (bio == nullptr) {
    errorL("BIO_new_mem_buf error!");
    BIO_free(bio);
    return nullptr;
  }

  pkey = PEM_read_bio_PrivateKey(bio, NULL, 0, NULL);
  if (!pkey) {
    errorL("PEM_read_bio_PrivateKey error!");
    return nullptr;
  }
  BIO_free(bio);
  return (void *)pkey;
}
bool ExportEVP_PKEY(unsigned char **buf, int *size){
    EVP_PKEY *pkey = createEVP_KEY();
    
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == nullptr) {
        errorL("BIO_new_mem_buf error!");
        BIO_free(bio);
        return false;
  }
  if(1!= PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)){
     errorL("PEM_write_bio_PrivateKey error!");
     BIO_free(bio);
     return false;
  }

  BUF_MEM *bptr;

 BIO_get_mem_ptr(bio, &bptr);
 BIO_set_close(bio, BIO_NOCLOSE); /* So BIO_free() leaves BUF_MEM alone */
 BIO_free(bio);

 *buf=(unsigned char *)bptr->data;
 *size=(int)bptr->length;
  debugL(bptr->data);
  return true;
}


bool sig_(const void *pkey, const unsigned char *message, int size_message, unsigned char **signature, int *size_signature){
     std::string me((char *)message,size_message);
    std::string val;
    bool ret;
    ret=sig(pkey,me,val);
    unsigned char * rv=(unsigned char *)malloc(val.size());
    if(rv==nullptr){
        free(rv);
        return false;
    }
    
    memcpy(rv, val.c_str(), val.size());
    *size_signature=val.size();
    *signature=rv;
    return true;
}

bool verf_(const void *pkey, const unsigned char *message, int size_message, unsigned char *signature, int size_signature){
    std::string me((char *)message,size_message);
    std::string val((char *)signature,size_signature);
    bool ret;
    ret=verf(pkey,me,val);
    //unsigned char * rv=(unsigned char *)malloc(val.size());
    if(ret==false){
        return false;
    }
    
    return true;
}

}

bool sig(const void *pkey, const std::string &message_, std::string &value) {
  EVP_PKEY *key = (EVP_PKEY *)pkey;

  EVP_MD_CTX *mdctx = NULL;
  const unsigned char *message = (const unsigned char *)message_.c_str();
  int message_size = message_.size();
  if (!(mdctx = EVP_MD_CTX_new())) {
    errorL("EVP_MD_CTX_new error!");
    return false;
  }
  if (pkey == NULL) {
    errorL("pkey is nullptr!");
    return false;
  }

  unsigned char *signuture = nullptr;
  // Initialise the DigestSign operation
  if (1 != EVP_DigestSignInit(mdctx, NULL, NULL, NULL, key)) {
    return false;
  }

  size_t tmpMLen = 0;
  if (1 != EVP_DigestSign(mdctx, NULL, &tmpMLen, (const unsigned char *)message,
                          message_size)) {
    return false;
  }

  signuture = (unsigned char *)OPENSSL_malloc(tmpMLen);

  if (1 != EVP_DigestSign(mdctx, signuture, &tmpMLen,
                          (const unsigned char *)message, message_size)) {
    return false;
  }

  std::string hashString((char *)signuture, tmpMLen);
  value = std::move(hashString);

  OPENSSL_free(signuture);
  EVP_MD_CTX_free(mdctx);
  return true;
}

bool verf(const void *pkey, const std::string &message,
          std::string &signature) {

  EVP_PKEY *key = (EVP_PKEY *)pkey;
  if (key == nullptr) {
    errorL("key is nullptr!");
    return false;
  }
  EVP_MD_CTX *mdctx = NULL;
  const char *msg = message.c_str();
  unsigned char *sig = (unsigned char *)signature.data();
  size_t slen = signature.size();
  size_t msg_len = strlen(msg);

  if (!(mdctx = EVP_MD_CTX_new())) {
    errorL("EVP_MD_CTX_new error");
    return false;
  }

  /* Initialize `key` with a public key */
  if (1 != EVP_DigestVerifyInit(mdctx, NULL, NULL, NULL, key)) {
    EVP_MD_CTX_free(mdctx);
    errorL("EVP_DigestVerifyInit error");
    return false;
  }

  if (1 !=
      EVP_DigestVerify(mdctx, sig, slen, (const unsigned char *)msg, msg_len)) {
      EVP_MD_CTX_free(mdctx);
    errorL("EVP_DigestVerify error");
    return false;
  }

  EVP_MD_CTX_free(mdctx);
  return true;
}


std::string getBase58(const void * pkey){
  EVP_PKEY * pkey_t=(EVP_PKEY *)pkey;
   unsigned char *pkey_der = NULL;
    int publen = i2d_PUBKEY(pkey_t ,&pkey_der);
   std::string pubStr;
    for(int i = 0; i < publen; ++i)
    {
        pubStr += pkey_der[i];
    }
   return GetBase58Addr(pubStr);
}

std::string getPriStr(const void *pkey)
{
  EVP_PKEY *pkey_t=(EVP_PKEY *)pkey;

    size_t len = 80;
    char pkey_data[80] = {0};
    if(EVP_PKEY_get_raw_private_key(pkey_t, (unsigned char *)pkey_data, &len) == 0)
    {
        return "error";
    }

    std::string data(pkey_data,len);
    return data;

}

 std::string getPubStr(const void * pkey){
    EVP_PKEY * pkey_t=(EVP_PKEY *)pkey;
    unsigned char *pkey_der = NULL;
    int publen = i2d_PUBKEY(pkey_t ,&pkey_der);
   std::string pubStr;
    for(int i = 0; i < publen; ++i)
    {
        pubStr += pkey_der[i];
    }
    return pubStr;
 }


 void *ImportFromHexStr(const char *str){
    std::string privateKeyHex(str);
    std::string priStr_ = Hex2Str(privateKeyHex);
    std::string pubStr_;
    unsigned char* buf_ptr = (unsigned char *)priStr_.data();
    const unsigned char *pk_str = buf_ptr;

    EVP_PKEY * pkey_ = EVP_PKEY_new_raw_private_key(EVP_PKEY_ED25519, NULL, pk_str, priStr_.size());
    if(pkey_ == nullptr)
    {
        return nullptr;
    }

    return pkey_;
 }

bool ExportToHexStr(const void *pkey, char **buf, int *size){
  std::string pri= getPriStr(pkey);
  if(pri=="error"){
     return false;
  }
  std::string strPriHex = Str2Hex(pri);
  char * buffer=(char *)malloc(strPriHex.size());
  memcpy(buffer, strPriHex.c_str(), strPriHex.size());
  *buf=buffer;
  *size=strPriHex.size();
  return true;
}

bool ExportMnemonic(const void *pkey,char ** buf,int *size){
  std::string priStr=getPriStr(pkey);
  char * buffer=(char *)malloc(1024);
  mnemonic_from_data((const uint8_t*)priStr.data(), priStr.size(), buffer, 1024);
  *buf=buffer;
  *size=1024;
  return true;
}

void *ImportFromMnemonic(const char * mnemonic){
  char out[33]={0};
  int outLen=0;
  if(mnemonic_check((char *)mnemonic, out, &outLen)==0){
     return nullptr;
  }
  char mnemonic_hex[65]={0};
  encode_hex(mnemonic_hex, out, outLen);

  std::string mnemonic_key;
  mnemonic_key.append(mnemonic_hex,outLen*2);

  return ImportFromHexStr(mnemonic_key.c_str());
}


void getBase58addr_c(const void * pkey,char **buf,int *size){
   std::string base58_addr=getBase58(pkey);
   char * buffer=(char *)malloc(base58_addr.size());
   memcpy(buffer, base58_addr.c_str(), base58_addr.size());
   *buf=buffer;
   *size=base58_addr.size();
}

void getPriStr_c(const void * pkey,char **buf,int *size){
  std::string pristr=getPriStr(pkey);
   char * buffer=(char *)malloc(pristr.size());
    memcpy(buffer, pristr.c_str(), pristr.size());
   *buf=buffer;
   *size=pristr.size();
}

void getPubStr_c(const void *pkey,char ** buf,int *size){
  std::string pubstr=getPubStr(pkey);
   char * buffer=(char *)malloc(pubstr.size());
   memcpy(buffer, pubstr.c_str(), pubstr.size());
   *buf=buffer;
   *size=pubstr.size();
}

 
 
 