
#include "src_envelop_Envelop.h"
#include "Envelop.h"
#include "RSA_TEXT.h"
#include "base64.h"
#include "debug.h"
#include "jni_tools.h"


/*
 * Class:     src_envelop_Envelop
 * Method:    GetEnvelopPoint
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_src_envelop_Envelop_GetEnvelopPoint
  (JNIEnv *, jobject){
        void * p=new envelop;
        long long pt=(long long)p;
        infoL("pt:" << std::hex << pt << std::dec);
        return pt;
  }

/*
 * Class:     src_envelop_Envelop
 * Method:    GetPublicString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_src_envelop_Envelop_GetPublicString
  (JNIEnv *env, jobject, jlong env_pointer){
        long long evn_p=(long long)env_pointer;
        infoL("evn_p:" << std::hex << evn_p << std::dec);
        Base64 base_;
        envelop * pter=(envelop *) evn_p;
        std::string pub=pter->getPubstr();
        std::string ret=base_.Encode((const unsigned char*)pub.c_str(), pub.size());
        return env->NewStringUTF(ret.c_str());

  }

/*
 * Class:     src_envelop_Envelop
 * Method:    Encode
 * Signature: (JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_src_envelop_Envelop_Encode
  (JNIEnv *env, jobject, jlong env_pointer, jstring pubstr, jstring messagestr){
         long long evn_p=(long long)env_pointer;
          envelop * pter=(envelop *) evn_p;
          Base64 base_;
          std::string temp=jstring2string(env, pubstr);
          std::string pubstr_base=base_.Decode(temp.c_str(), temp.size());

          std::string message_=jstring2string(env, messagestr);


          std::string ret;
         bool ret_= RSAEnCode(message_, pter, pubstr_base, ret);
         if(ret_==false){
            errorL("RSAEncode fail");
            return env->NewStringUTF("");
         }
         std::string ret_base=base_.Encode((const unsigned char *)ret.c_str(), ret.size());
         return env->NewStringUTF(ret_base.c_str());
  }

/*
 * Class:     src_envelop_Envelop
 * Method:    Decode
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_src_envelop_Envelop_Decode
  (JNIEnv *env , jobject, jlong env_pointer, jstring messagestr){
        Base64 base_;
        long long evn_p=(long long)env_pointer;
        envelop * pter=(envelop *) evn_p;
        std::string temp=jstring2string(env,messagestr);
        std::string message_=base_.Decode((const char *)temp.c_str(), temp.size());
        std::string ret;
        bool ret_=RSADeCode(message_, pter, temp, ret);
        if(ret_==false){
            errorL("RSADeCode fail");
            return env->NewStringUTF("");
        }
        //std::string ret_base=base_.Encode((const unsigned char *)ret.c_str(), ret.size());
        return env->NewStringUTF(ret.c_str());
  }


 JNIEXPORT void JNICALL Java_src_envelop_Envelop_FreeEnvelopPoint(JNIEnv *, jobject, jlong env_pointer){
        long long evn_p=(long long)env_pointer;
        envelop * pter=(envelop *) evn_p;
        delete pter;
  }