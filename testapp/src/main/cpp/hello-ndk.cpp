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
