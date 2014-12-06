#include <jni.h>
#include "stringUtils.h"

/*
 * Get the length of the string
 */
JNIEXPORT jint JNICALL Java_com_Language_LanguageStringUtils_length(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return -1;
	}

	return len(buffer, encoding);
}

/**
 * Get the length of an escape string
 */
JNIEXPORT jint JNICALL Java_com_Language_LanguageStringUtils_lengthEscaped(JNIEnv * env, jobject thisObj, jstring str,
		jint encoding, jstring estr, jint escapedEncoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	const char * escapedStr = (*env)->GetStringUTFChars(env, estr, NULL);
	return lenEscaped(buffer, encoding, escapedStr, escapedEncoding, NULL);
}

/**
 * Get the length of an escaped string
 */
JNIEXPORT jint JNICALL Java_com_Language_LanguageStringUtils_lengthEscapedWithEnd(JNIEnv * env, jobject thisObj, jstring str,
			jint encoding, jstring estr, jint escapedEncoding, jstring nstr){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	const char * escapedStr = (*env)->GetStringUTFChars(env, estr, NULL);
	const char * endString = (*env)->GetStringUTFChars(env, nstr, NULL);
	return lenEscaped(buffer, encoding, escapedStr,escapedEncoding, endString);
}
