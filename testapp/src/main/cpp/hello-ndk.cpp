//
// Created by Administrator on 2019/11/14.
//
#include <jni.h>
//确认此处名字是否可你生成的头文件的名字一样
#include "com_example_testapp_MainActivity.h"

//函数名要和头文件中的名字一致
JNIEXPORT jstring JNICALL Java_com_example_testapp_MainActivity_helloNDK
        (JNIEnv * env, jobject){
    return env ->NewStringUTF("Hello NDK");
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