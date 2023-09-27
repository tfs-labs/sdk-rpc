#include "Envelop.h"
#include <openssl/rsa.h>
#include "util2.h"
#include "base58.h"
#include <vector>
#include <openssl/types.h>
#include <openssl/crypto.h>
#include <openssl/pem.h>
#include "hexcode.h"
#include "debug.h"
#include <openssl/rand.h>



bool SignMessage(const std::string& message, EVP_PKEY* pkey, std::string& signature)
{
    EVP_MD_CTX* mdctx = NULL;
    const char* sig_name = message.c_str();

    unsigned char* sig_value = NULL;
    size_t sig_len = strlen(sig_name);

    // Create the Message Digest Context 
    if (!(mdctx = EVP_MD_CTX_new()))
    {
        return false;
    }

    if (pkey == NULL)
    {
        return false;
    }

    // Initialise the DigestSign operation
    if (1 != EVP_DigestSignInit(mdctx, NULL, NULL, NULL, pkey))
    {
        return false;
    }

    size_t tmpMLen = 0;
    if (1 != EVP_DigestSign(mdctx, NULL, &tmpMLen, (const unsigned char*)sig_name, sig_len))
    {
        return false;
    }

    sig_value = (unsigned char*)OPENSSL_malloc(tmpMLen);

    if (1 != EVP_DigestSign(mdctx, sig_value, &tmpMLen, (const unsigned char*)sig_name, sig_len))
    {
        return false;
    }

    signature.append(reinterpret_cast<const char*>(sig_value), tmpMLen);
    OPENSSL_free(sig_value);
    EVP_MD_CTX_free(mdctx);
    return true;

}

bool VerifyMessage(const std::string& message, EVP_PKEY* pkey, const std::string& signature)
{
    EVP_MD_CTX* mdctx = NULL;
    const char* msg = message.c_str();
    unsigned char* sig = (unsigned char*)signature.data();
    size_t slen = signature.size();
    size_t msg_len = strlen(msg);

    if (!(mdctx = EVP_MD_CTX_new()))
    {
        return false;
    }

    /* Initialize `key` with a public key */
    if (1 != EVP_DigestVerifyInit(mdctx, NULL, NULL, NULL, pkey))
    {
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    if (1 != EVP_DigestVerify(mdctx, sig, slen, (const unsigned char*)msg, msg_len))
    {
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    EVP_MD_CTX_free(mdctx);
    return true;

}




envelop::envelop(/* args */)
{
    const int kBits = 2048; // 
    rsaPkey = EVP_PKEY_new();
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if(EVP_PKEY_keygen_init(ctx) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return;
    }

    if(EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, kBits) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return;
    }

    if(EVP_PKEY_keygen(ctx, &rsaPkey) <= 0)
    {
        EVP_PKEY_CTX_free(ctx);
        return;
    }
    EVP_PKEY_CTX_free(ctx);
}

envelop::~envelop()
{
    EVP_PKEY_free(rsaPkey);
}

bool envelop::GetEDPubKeyByBytes(const std::string& pubStr, EVP_PKEY*& pKey)
{
    //Generate public key from binary string of public key  
    unsigned char* buf_ptr = (unsigned char*)pubStr.data();
    const unsigned char* pk_str = buf_ptr;
    int len_ptr = pubStr.size();

    if (len_ptr == 0)
    {
       // ERRORLOG("public key Binary is empty");
        return false;
    }

    EVP_PKEY* peer_pub_key = d2i_PUBKEY(NULL, &pk_str, len_ptr);

    if (peer_pub_key == nullptr)
    {
        return false;
    }
    pKey = peer_pub_key;
    return true;
}

std::string envelop::getPubstr()
{
    std::string pubstr;
 
    unsigned char* pkey_der = NULL;
    int publen = i2d_PUBKEY(rsaPkey, &pkey_der);
    pubstr.append(reinterpret_cast<const char*>(pkey_der), publen);
    return pubstr;
}




bool envelop::Encrypt(const std::string &in, std::string &out, std::string &key)
{       
    EVP_CIPHER_CTX *ctx;
    
    ctx = EVP_CIPHER_CTX_new();

    unsigned char aes_key[EVP_MAX_KEY_LENGTH];
    unsigned char aes_iv[EVP_MAX_IV_LENGTH];
    RAND_bytes(aes_key, EVP_MAX_KEY_LENGTH);
    RAND_bytes(aes_iv, EVP_MAX_IV_LENGTH);



    int ret = EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, aes_key, aes_iv);
    if(ret != 1)
    {
        return false;
    }


    int mlen = 0;
    out.resize(in.size() + EVP_MAX_BLOCK_LENGTH);
    ret = EVP_EncryptUpdate(ctx, (unsigned char*)out.data(), &mlen, (const unsigned char*)in.data(), in.size());
    if(ret != 1)
    {
        return false;
    }


    int flen = 0;
    ret = EVP_EncryptFinal_ex(ctx, (unsigned char *)out.data() + mlen, &flen);
    if(ret != 1)
    {
        return false;
    }
    out.resize(mlen + flen);
    
    key.append(reinterpret_cast<const char*>(aes_key), sizeof(aes_key));
    std::string keyHex =  Str2Hex(key); 
    std::string ivec(reinterpret_cast<const char*>(aes_iv), sizeof(aes_iv));
    std::string ivecHex =  Str2Hex(ivec);

    key =   keyHex + "_" + ivecHex;

    EVP_CIPHER_CTX_free(ctx);


    return true;
}

void SplitString(const std::string& s, const std::string& c, std::vector<std::string>& v)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        std::string str = s.substr(pos1, pos2 - pos1);

        if (!str.empty())
        {
            v.push_back(str);
        }

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }

    if (pos1 != s.length())
    {
        std::string str = s.substr(pos1);
        if (!str.empty())
        {
            v.push_back(str);
        }
    }
}


bool envelop::Decrypt(const std::string &in, std::string &out, const std::string &key)
{
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    std::vector<std::string> key_iv;

	SplitString(key, "_", key_iv);
    if(key_iv.size() != 2)
    {
        return false;
    }

    std::string iv = Hex2Str(key_iv[1]);
    std::string aes_key = Hex2Str(key_iv[0]);

   
    int ret = EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (const unsigned char*)aes_key.data(), (const unsigned char*)iv.data());
    if(ret != 1)
    {
        return false;
    }

  
    int mlen = 0;
    out.resize(in.size());
    ret = EVP_DecryptUpdate(ctx, (unsigned char*)out.data(), &mlen, (const unsigned char*)in.data(), in.size());
    if(ret != 1)
    {
        return false;
    }

 
    int flen = 0;
    ret = EVP_DecryptFinal_ex(ctx, (unsigned char *)out.data() + mlen, &flen);
    if(ret != 1)
    {
        return false;
    }
    out.resize(mlen + flen);

    EVP_CIPHER_CTX_free(ctx);

    return true;
}


bool GetPubKeyByBytes(const std::string& pubStr, EVP_PKEY*& pKey)
{
    //Generate public key from binary string of public key  
    unsigned char* buf_ptr = (unsigned char*)pubStr.data();
    const unsigned char* pk_str = buf_ptr;
    int len_ptr = pubStr.size();

    if (len_ptr == 0)
    {
       // ERRORLOG("public key Binary is empty");
        return false;
    }

    EVP_PKEY* peer_pub_key = d2i_PUBKEY(NULL, &pk_str, len_ptr);

    if (peer_pub_key == nullptr)
    {
        return false;
    }
    pKey = peer_pub_key;
    return true;
}

int envelop::EncryptByRSA(const std::string &data, EVP_PKEY * &pkey, std::string & ciphertext)
{
    unsigned char* buf_ptr = (unsigned char *)data.data();
    const unsigned char *data_str = buf_ptr;
    size_t data_len = data.size();
    size_t out_len;
    unsigned char* out = nullptr;
    char szErr[1024];

    size_t len = EVP_PKEY_get_size(pkey);
    out = (unsigned char *)OPENSSL_malloc(len);
  
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);

    if(!ctx)
    {
        return -4;
    }

    int ret = EVP_PKEY_encrypt_init(ctx);
    if(ret <= 0)
    {
        return -2;
    }

    int rv = EVP_PKEY_encrypt(ctx ,out, &out_len, data_str, data_len);
    if (rv <= 0) {
        return -1;
    }

    if(out == nullptr)
    {
        return -3;
    }
    ciphertext.append(reinterpret_cast<const char *>(out), out_len);

    OPENSSL_free(out);
    EVP_PKEY_CTX_free(ctx);
    return 0;
}

int envelop::DecryptByRSA(const std::string &enc, EVP_PKEY *pkey, std::string & ciphertext)
{

    unsigned char * buf_ptr =(unsigned char *)enc.data();
    const unsigned char *data_str = buf_ptr;
    size_t in_len = enc.size();
    size_t out_len;
    unsigned char* out = nullptr;

    size_t len = EVP_PKEY_get_size(pkey);
    out = (unsigned char *)OPENSSL_malloc(len);
  
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    EVP_PKEY_decrypt_init(ctx);

    if(EVP_PKEY_decrypt(ctx, out, &out_len, data_str, in_len) <= 0)
    {
        return -1;
    }
    ciphertext.append(reinterpret_cast<const char *>(out), out_len);
    OPENSSL_free(out);
    return 0;
}


int envelop::EncapsulatEnvelope(const std::string &data, const std::string& pubstr, std::string& strEncTxt, std::string& cipher_text, std::string& out)
{
  
   EVP_PKEY*pkey_der = NULL;
   GetEDPubKeyByBytes(pubstr, pkey_der);


 
    std::string data256 = getsha256hash(data);
    if(SignMessage(data256, rsaPkey, out) == false)
    {
        return -1;
    }


    std::string aes_key;
    if(Encrypt(data,strEncTxt,aes_key) == false)
    {
        return -2;
    }
    

    if(EncryptByRSA(aes_key, pkey_der, cipher_text) != 0)
    {
        return -3;
    }

    return 0;
}


int envelop::OpenEnvelope(const std::string& cipher_text, const std::string& out, const std::string& strEncTxt, const std::string& pub_str, std::string& message)
{
   
    
    std::string key;
    if(DecryptByRSA(cipher_text, rsaPkey, key) != 0)
    {
        return -1;
    }
    
   
    if(Decrypt(strEncTxt,message,key) == false)
    {
        return -2;
    }
    
  
    EVP_PKEY* rsa_key = nullptr;
    if(GetPubKeyByBytes(pub_str, rsa_key) == false)
    {
        return -3; 
    }
    
    std::string message256 = getsha256hash(message);
    if(VerifyMessage(message256, rsa_key, out) == false)
    {
        return -4;
    }
    
    EVP_PKEY_free(rsa_key);

    return 0;
}



void TestFunction2()
{
    std::string data = R"()";

    envelop enve;

    std::string message;
    for(int i = 0; i < 1; ++i)
    {
        std::string data_1 = data + std::to_string(i);

        std::string pubstr,strEncTxt,cipher_text,sign_message;

        if(enve.EncapsulatEnvelope(data_1,pubstr,strEncTxt,cipher_text,sign_message) != 0)
        {
            errorL("EncapsulatEnvelope fail !");
            return;
        }

       
        if(enve.OpenEnvelope(cipher_text, sign_message, strEncTxt, pubstr, message) != 0)
        {
            errorL("OpenEnvelope fail !");
            return;
        }
    }
   // infoL("message:" << message);
 

    return;
}




