#include <jni.h>

/*
 * Get the length of the string
 */
JNIEXPORT jsint JNICALL Java_Language__LanguageStringUtils_length(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, inJNIStr, NULL);
	if(buffer == NULL){
		return -1;
	}

	return len(buffer, encoding);
}

