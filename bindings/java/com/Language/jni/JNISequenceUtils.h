#ifndef __JNI_SEQUENCE_UTILS__
#define __JNI_SEQUENCE_UTILS__

#include <jni.h>

/**
 * A function that generically performs a sequence check for a string
 * in a specific encoding.
 */
static jboolean sequenceCheck(int (*func)(const char *, int), JNIEnv * env, jobject obj,
		jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = func(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/**
 * A function that computes a languae specific string check. This
 * generic function provides the interface for all other language
 * specific function
 */
static jboolean alphabetLanguageSequenceCheck(int (*func)(const char *, int, int), JNIEnv * env, jobject obj,
		jstring str, jint encoding, jint language){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = func(buffer, encoding, language);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

#endif
