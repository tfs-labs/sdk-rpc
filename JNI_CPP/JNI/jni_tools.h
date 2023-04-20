#ifndef __JNI_TOOLS_
#define __JNI_TOOLS_
#include "jni.h"
#include <string>
std::string jstring2string(JNIEnv *env, jstring jStr);
#endif