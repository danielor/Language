#include <jni.h>
#include "stringUtils.h"
#include "JNISequenceUtils.h"

/*
 * Check if a character is a hex number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isHexNumber
(JNIEnv *env , jobject thisObj, jstring str, jint encoding, jint index){
	return sequenceCheckAtIndex(isHex, env, thisObj, str, encoding, index);
}

/**
 * Check if a character is a natural number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isNaturalNumber
(JNIEnv *env , jobject thisObj, jstring str, jint encoding, jint index){
	return sequenceCheckAtIndex(isNumber, env, thisObj, str, encoding, index);
}

/*
 * Check if a character is in the romance alphabet
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInRomanceAlphabet
(JNIEnv *env , jobject thisObj, jstring str, jint encoding, jint index){
	return sequenceCheckAtIndex(isInRomanceAlphabet, env, thisObj, str, encoding, index);
}

/*
 * Check if a character is valid in a certain encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isValid
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint index){
	return sequenceCheckAtIndex(isValidCharacter, env, thisObj, str, encoding, index);
}

/**
 * Check if character is part of a language set of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language, jint index){
	return alphabetLanguageSequenceCheckAtIndex(isInAlphabet, env, thisObj, str, encoding, language, index);
}

/**
 * Check if character is lower case in a language set
 * of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isLowerCaseInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language, jint index){
	return alphabetLanguageSequenceCheckAtIndex(isLowerCaseInAlphabet, env, thisObj, str, encoding, language, index);
}

/**
 * Check if character is  upper case in a language set
 * of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isUpperCaseInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language, jint index){
	return alphabetLanguageSequenceCheckAtIndex(isUpperCaseInAlphabet, env, thisObj, str, encoding, language, index);
}

/**
 * Check if character is  upper case in a language set
 * of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isPunctuationMarkInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language, jint index){
	return alphabetLanguageSequenceCheckAtIndex(isPunctuationMarkInAlphabet, env, thisObj, str, encoding, language, index);
}
