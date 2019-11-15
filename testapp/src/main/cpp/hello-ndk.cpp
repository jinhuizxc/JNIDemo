//
// Created by Administrator on 2019/11/14.
//
#include <jni.h>
//确认此处名字是否可你生成的头文件的名字一样
#include "com_example_testapp_MainActivity.h"

#include <random>
//数组元素最大值
const jint max = 100;

//函数名要和头文件中的名字一致
JNIEXPORT jstring JNICALL Java_com_example_testapp_MainActivity_helloNDK
        (JNIEnv *env, jobject) {
    return env->NewStringUTF("Hello NDK");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testapp_MainActivity_accessField(JNIEnv *env, jobject instance) {
    //获取类
    jclass jcla = env->GetObjectClass(instance);
    //获取类的成员变量showText的id
    jfieldID jfId = env->GetFieldID(jcla, "showText", "Ljava/lang/String;");

    jstring after = env->NewStringUTF("Hello NDK");
    //修改属性id对应的值
    env->SetObjectField(instance, jfId, after);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testapp_MainActivity_accessStaticField(JNIEnv *env, jobject instance) {
    //获取类
    jclass oClass = env->GetObjectClass(instance);
    //获取静态变量id
    jfieldID staticFid = env->GetStaticFieldID(oClass, "staticString", "Ljava/lang/String;");

    //设置静态变量
    jstring after = env->NewStringUTF("static field update in jni");
    env->SetStaticObjectField(oClass, staticFid, after);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_testapp_MainActivity_accessMethod(JNIEnv *env, jobject instance) {
    //获取类
    jclass jCla = env->GetObjectClass(instance);
    //获取方法id  第二个参数：方法名  第三个参数：(参数)返回值 的类型描述
    jmethodID methodID = env->GetMethodID(jCla, "getAuthName",
                                          "(Ljava/lang/String;)Ljava/lang/String;");
    jstring res = env->NewStringUTF("103style");
    jobject objRes = env->CallObjectMethod(instance, methodID, res);
    return static_cast<jstring>(objRes);
}extern "C"
JNIEXPORT jint JNICALL
Java_com_example_testapp_MainActivity_accessStaticMethod(JNIEnv *env, jobject instance, jint max) {
    //获取类
    jclass jCla = env->GetObjectClass(instance);
    //获取静态方法的id
    jmethodID methodID = env->GetStaticMethodID(jCla, "getRandomValue", "(I)I");
    //调用静态方法
    jint res = env->CallStaticIntMethod(jCla, methodID, max);
    //返回结果
    return res;
}extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_testapp_MainActivity_accessConstructor(JNIEnv *env, jobject thiz) {
    //得到TestClass对应的jclass
//    jclass jCla = env->FindClass("com/example/myapplication/TestClass");
    jclass jCla = env->FindClass("java/util/Date");
    //获取构造函数的methodId  构造函数为 void函数 对应的方法名为<init>
    jmethodID methodID = env->GetMethodID(jCla, "<init>", "()V");
    jobject jTestClass = env->NewObject(jCla, methodID);
    return jTestClass;
}

int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_testapp_JniArrayOperation_getIntArray(JNIEnv *env, jobject thiz, jint length) {
    //创建一个指定大小的数组
    jintArray array = env->NewIntArray(length);

    jint *elementsP = env->GetIntArrayElements(array, nullptr);

    //设置 0-100的随机元素
    jint *startP = elementsP;
    for (; startP < elementsP + length; startP++) {
        *startP = static_cast<jint>(random() % max);
    }
    env->ReleaseIntArrayElements(array, elementsP, 0);
    return array;
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testapp_JniArrayOperation_sortIntArray(JNIEnv *env, jobject thiz, jintArray arr_) {
    //获取数组起始元素的指针
    jint *arr = env->GetIntArrayElements(arr_, nullptr);
    //获取数组长度
    jint len = env->GetArrayLength(arr_);
    //排序
    qsort(arr, len, sizeof(jint), compare);

    //第三个参数 同步
    //0：Java数组进行更新，并且释放C/C++数组
    //JNI_ABORT：Java数组不进行更新，但是释放C/C++数组
    //JNI_COMMIT：Java数组进行更新，不释放C/C++数组(函数执行完后，数组还是会释放的)
    env->ReleaseIntArrayElements(arr_, arr, 0);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_testapp_Encryptor_createFile(JNIEnv *env, jobject thiz, jstring normalPath_) {
    //获取字符串保存在JVM中内存中
    const char *normalPath = env->GetStringUTFChars(normalPath_, nullptr);
    //打开 normalPath  wb:只写打开或新建一个二进制文件；只允许写数据
    FILE *fp = fopen(normalPath, "wb");

    //把字符串写入到指定的流 stream 中，但不包括空字符。
    fputs("Hi, this file is created by JNI, and my name is 103style.", fp);

    //关闭流 fp。刷新所有的缓冲区
    fclose(fp);
    //释放JVM保存的字符串的内存
    env->ReleaseStringUTFChars(normalPath_, normalPath);
}

#include <android/log.h>
#include <cstdio>
#include <cstring>

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"Encryptor",FORMAT,##__VA_ARGS__);

char password[] = "103style";

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testapp_Encryptor_encryption(JNIEnv *env, jclass clazz, jstring normalPath_,
                                              jstring encryptPath_) {
    //获取字符串保存在JVM中内存中
    const char *normalPath = env->GetStringUTFChars(normalPath_, nullptr);
    const char *encryptPath = env->GetStringUTFChars(encryptPath_, nullptr);

    LOGE("normalPath = %s, encryptPath = %s", normalPath, encryptPath);

    //rb:只读打开一个二进制文件，允许读数据。
    //wb:只写打开或新建一个二进制文件；只允许写数据
    FILE *normal_fp = fopen(normalPath, "rb");
    FILE *encrypt_fp = fopen(encryptPath, "wb");

    if (normal_fp == nullptr) {
        LOGE("%s", "文件打开失败");
        return;
    }

    //一次读取一个字符
    int ch = 0;
    int i = 0;
    size_t pwd_length = strlen(password);
    while ((ch = fgetc(normal_fp)) != EOF) { //End of File
        //写入(异或运算)
        fputc(ch ^ password[i % pwd_length], encrypt_fp);
        i++;
    }

    //关闭流 normal_fp和encrypt_fp。刷新所有的缓冲区
    fclose(normal_fp);
    fclose(encrypt_fp);

    //释放JVM保存的字符串的内存
    env->ReleaseStringUTFChars(normalPath_, normalPath);
    env->ReleaseStringUTFChars(encryptPath_, encryptPath);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testapp_Encryptor_decryption(JNIEnv *env, jclass clazz, jstring encryptPath_,
                                              jstring decryptPath_) {
    ////获取字符串保存在JVM中内存中
    const char *encryptPath = env->GetStringUTFChars(encryptPath_, nullptr);
    const char *decryptPath = env->GetStringUTFChars(decryptPath_, nullptr);

    LOGE("encryptPath = %s, decryptPath = %s", encryptPath, decryptPath);

    //rb:只读打开一个二进制文件，允许读数据。
    //wb:只写打开或新建一个二进制文件；只允许写数据
    FILE *encrypt_fp = fopen(encryptPath, "rb");
    FILE *decrypt_fp = fopen(decryptPath, "wb");

    if (encrypt_fp == nullptr) {
        LOGE("%s", "加密文件打开失败");
        return;
    }

    int ch;
    int i = 0;
    size_t pwd_length = strlen(password);
    while ((ch = fgetc(encrypt_fp)) != EOF) {
        fputc(ch ^ password[i % pwd_length], decrypt_fp);
        i++;
    }

    //关闭流 encrypt_fp 和 decrypt_fp。刷新所有的缓冲区
    fclose(encrypt_fp);
    fclose(decrypt_fp);

    //释放JVM保存的字符串的内存
    env->ReleaseStringUTFChars(encryptPath_, encryptPath);
    env->ReleaseStringUTFChars(decryptPath_, decryptPath);
}