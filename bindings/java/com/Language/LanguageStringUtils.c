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

/**
 * Check if a sequence is a natural number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isNaturalNumber(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isNumberSequence(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}

}

/**
 * Check if a sequence is a hex number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isHexNumber(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isHexSequence(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/**
 * Check if a sequence is a valid character
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isValid(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isValidCharacterSequence(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/**
 * Check if a sequence is in the romance alphabet
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isInRomanceAlphabet(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isInRomanceAlphabetSequence(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/**
 * Check if a sequence is in an alphabet of an arbitrary language
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isInAlphabet
(JNIEnv * env, jobject obj, jstring str, jint encoding, jint language){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isInAlphabetSequence(buffer, encoding, language);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}


