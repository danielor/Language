#include <jni.h>
#include "stringUtils.h"
#include "JNISequenceUtils.h"

/*
 * Check if a character is a hex number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isHexNumber
(JNIEnv *env , jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isHex, env, thisObj, str, encoding);
}

/**
 * Check if a character is a natural number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isNaturalNumber
(JNIEnv *env , jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isNumber, env, thisObj, str, encoding);
}

/*
 * Check if a character is in the romance alphabet
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInRomanceAlphabet
(JNIEnv *env , jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isInRomanceAlphabet, env, thisObj, str, encoding);
}

/*
 * Check if a character is valid in a certain encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isValid
(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isValidCharacter, env, thisObj, str, encoding);
}

/**
 * Check if character is part of a language set of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isInAlphabet, env, thisObj, str, encoding, language);
}

/**
 * Check if character is lower case in a language set
 * of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isLowerCaseInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isLowerCaseInAlphabet, env, thisObj, str, encoding, language);
}

/**
 * Check if character is  upper case in a language set
 * of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isUpperCaseInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isUpperCaseInAlphabet, env, thisObj, str, encoding, language);
}

/**
 * Check if character is  upper case in a language set
 * of characters in an encoding
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageCharUtils_isPunctuationMarkInAlphabet
(JNIEnv * env, jobject thisObj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isPunctuationMarkInAlphabet, env, thisObj, str, encoding, language);
}
