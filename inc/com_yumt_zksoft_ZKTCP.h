/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_yumt_zksoft_ZKTCP */

#ifndef _Included_com_yumt_zksoft_ZKTCP
#define _Included_com_yumt_zksoft_ZKTCP
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    connect
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_connect
  (JNIEnv *, jclass, jstring, jstring, jint);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    disConnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_yumt_zksoft_ZKTCP_disConnect
  (JNIEnv *, jclass);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    ReadAllGLogData
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_yumt_zksoft_ZKTCP_ReadAllGLogData
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetGeneralLogDataStr
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetGeneralLogDataStr
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    ClearGLog
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_ClearGLog
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    ReadAllUserID
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_ReadAllUserID
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetAllUserInfo
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetAllUserInfo
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    SetUserInfo
 * Signature: (JJLjava/lang/String;Ljava/lang/String;JZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_SetUserInfo
  (JNIEnv *, jclass, jlong, jlong, jstring, jstring, jlong, jboolean);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetUserInfo
 * Signature: (JJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetUserInfo
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    SetUserTmpStr
 * Signature: (JJJLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_SetUserTmpStr
  (JNIEnv *, jclass, jlong, jlong, jlong, jstring);

/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetUserTmpStr
 * Signature: (JJJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetUserTmpStr
  (JNIEnv *, jclass, jlong, jlong, jlong);
  
  
JNIEXPORT void JNICALL Java_com_yumt_zksoft_ZKTCP_Release
  (JNIEnv *, jclass);


#ifdef __cplusplus
}
#endif
#endif
