//
// Created by Administrator on 2016/2/22.
//
#include <jni.h>
#include <string.h>
#include <stdio.h>
#include "exercise_hzw_com_ndkdemo_Jni.h"

const char* KEY = "0CC175B9C0F1B6A831C399E269772661";

/**
 * 发布的app 签名,只有和本签名一致的app 才会返回合法的 授权 key
 */
const char* RELEASE_SIGN ="";


static jclass contextClass;
static jclass signatureClass;
static jclass packageNameClass;
static jclass packageInfoClass;
JNIEXPORT jstring JNICALL Java_exercise_hzw_com_ndkdemo_Jni_getKey(
        JNIEnv * env, jobject obj, jobject contextObject) {

    jmethodID getPackageManagerId = (env)->GetMethodID(contextClass, "getPackageManager","()Landroid/content/pm/PackageManager;");
    jmethodID getPackageNameId = (env)->GetMethodID(contextClass, "getPackageName","()Ljava/lang/String;");
    jmethodID signToStringId = (env)->GetMethodID(signatureClass, "toCharsString","()Ljava/lang/String;");
    jmethodID getPackageInfoId = (env)->GetMethodID(packageNameClass, "getPackageInfo","(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageManagerObject =  (env)->CallObjectMethod(contextObject, getPackageManagerId);
    jstring packNameString =  (jstring)(env)->CallObjectMethod(contextObject, getPackageNameId);
    jobject packageInfoObject = (env)->CallObjectMethod(packageManagerObject, getPackageInfoId,packNameString, 64);
    jfieldID signaturefieldID =(env)->GetFieldID(packageInfoClass,"signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signatureArray = (jobjectArray)(env)->GetObjectField(packageInfoObject, signaturefieldID);
    jobject signatureObject =  (env)->GetObjectArrayElement(signatureArray,0);

    const char* signString =  (env)->GetStringUTFChars((jstring)(env)->CallObjectMethod(signatureObject, signToStringId),0);
    if(strcmp(signString,RELEASE_SIGN)==0)//签名一致  返回合法的 api key，否则返回错误
    {
        return (env)->NewStringUTF(KEY);
    }else
    {
//        return (env)->NewStringUTF("error");
        return (env)->NewStringUTF((env)->GetStringUTFChars((jstring)packNameString,0));
    }

}


/**
 * so被加载时会调用
 */
JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM* vm,void* reserved){

    JNIEnv* env = NULL;
    jint result=-1;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        return result;

    contextClass = (jclass)env->NewGlobalRef((env)->FindClass("android/content/Context"));
    signatureClass = (jclass)env->NewGlobalRef((env)->FindClass("android/content/pm/Signature"));
    packageNameClass = (jclass)env->NewGlobalRef((env)->FindClass("android/content/pm/PackageManager"));
    packageInfoClass = (jclass)env->NewGlobalRef((env)->FindClass("android/content/pm/PackageInfo"));

    return JNI_VERSION_1_4;
}



