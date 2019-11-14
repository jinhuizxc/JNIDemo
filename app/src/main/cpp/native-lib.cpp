#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
// 提供了一个简单的 C++ 函数 stringFromJNI()
Java_com_example_jnidemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
