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

