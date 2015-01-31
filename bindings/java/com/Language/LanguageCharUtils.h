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
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isHexNumber
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isHexNumberChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isNaturalNumber
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isInRomanceAlphabetChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInRomanceAlphabet
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isValidChar
 * Signature: (Ljava/lang/String;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isValid
(JNIEnv *, jobject, jstring, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isInAlphabetChar
 * Signature: (Ljava/lang/String;I;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInAlphabet
(JNIEnv *, jobject, jstring, jint, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isLowerCaseInAlphabet
 * Signature: (Ljava/lang/String;I;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isLowerCaseInAlphabet
(JNIEnv *, jobject, jstring, jint, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isInUpperCaseInAlphabet
 * Signature: (Ljava/lang/String;I;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isUpperCaseInAlphabet
(JNIEnv *, jobject, jstring, jint, jint);

/*
 * Class:     LanguageCharUtils
 * Method:    isPunctucationMarkInAlphabet
 * Signature: (Ljava/lang/String;I;I)B
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isPunctuationMarkInAlphabet
(JNIEnv *, jobject, jstring, jint, jint);


#ifdef __cplusplus
}
#endif
#endif
