#include <jni.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Get the length of a string in C
 * @param str The java string
 * @param encoding The encodiing of the string
 */
JNIEXPORT jsint JNICALL Java_Language__LanguageStringUtils_length(JNIEnv *, jobject, jstring, jint);

#ifdef __cplusplus
}
#endif
