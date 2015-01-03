#include <jni.h>

#ifndef _Included_LanguageCharUtils
#define _Included_LanguageCharUtils
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     LanguageCharUtils
 * Method:    isHexNumberChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isHexNumberChar
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isHexNumberChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isNaturalNumberChar
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isInRomanceAlphabetChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInRomanceAlphabetChar
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isValidChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isValidChar
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isInAlphabetChar
 * Signature: (Ljava/lang/String;I;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInAlphabetChar
(JNIEnv *, jobject, jstring, jint, jint);


#ifdef __cplusplus
}
#endif
#endif
