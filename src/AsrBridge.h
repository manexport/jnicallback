/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_lenovo_cui_AsrBridge */

#ifndef _Included_com_lenovo_cui_AsrBridge
#define _Included_com_lenovo_cui_AsrBridge
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_lenovo_cui_AsrBridge
 * Method:    PreLoad
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_PreLoad
  (JNIEnv * env, jobject thiz, jstring logPath);

/*
 * Class:     com_lenovo_cui_AsrBridge
 * Method:    Init
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_lenovo_cui_AsrBridge_Init
  (JNIEnv * env, jobject thiz, jstring enginetype);

/*
 * Class:     com_lenovo_cui_AsrBridge
 * Method:    UnInit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_UnInit
  (JNIEnv * env, jobject thiz, jlong lhandle);

/*
 * Class:     com_lenovo_cui_AsrBridge
 * Method:    Post
 * Signature: (JLcom/lenovo/cui/BaseMessage;I)I
 */
JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_Post
  (JNIEnv * env, jobject thiz, jlong lhandle, jobject message, jint msgtype);

/*
 * Class:     com_lenovo_cui_AsrBridge
 * Method:    UnLoad
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_lenovo_cui_AsrBridge_UnLoad
  (JNIEnv * env, jobject thiz, jlong lhandle);

/*
 * Class:     com_lenovo_cui_AsrBridge
 * Method:    SetListener
 * Signature: (JLcom/lenovo/cui/Listener;)I
 */
JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_SetListener
  (JNIEnv * env, jobject thiz, jlong lhandle, jobject listener);

#ifdef __cplusplus
}
#endif
#endif
