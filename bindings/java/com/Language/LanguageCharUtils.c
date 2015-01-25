#include <jni.h>
#include "stringUtils.h"

/*
 * Check if a character is a hex number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isHexNumberChar
(JNIEnv *env , jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isHex(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/**
 * Check if a character is a natural number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isNaturalNumberChar
(JNIEnv *env , jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isNumber(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/*
 * Check if a character is in the romance alphabet
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInRomanceAlphabetChar
(JNIEnv *env , jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isInRomanceAlphabet(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/*
 * Check if a character is valid in a certain encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isValidChar
(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isValidCharacter(buffer, encoding);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}

/**
 * Check if character is part of a language set of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInAlphabetChar
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language){
	const char * buffer = (*env)->GetStringUTFChars(env, str, NULL);
	if(buffer == NULL){
		return JNI_FALSE;
	}
	int result = isInAlphabet(buffer, encoding, language);
	if(result == 0){
		return JNI_FALSE;
	}else{
		return JNI_TRUE;
	}
}
