#include <jni.h>
#include "stringUtils.h"
#include "JNISequenceUtils.h"

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
	return sequenceCheck(isNumberSequence, env, thisObj, str, encoding);
}

/**
 * Check if a sequence is a hex number
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isHexNumber(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isHexSequence, env, thisObj, str, encoding);
}

/**
 * Check if a sequence is a valid character
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isValid(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isValidCharacterSequence,env, thisObj, str, encoding);
}

/**
 * Check if a sequence is in the romance alphabet
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isInRomanceAlphabet(JNIEnv * env, jobject thisObj, jstring str, jint encoding){
	return sequenceCheck(isInRomanceAlphabetSequence, env, thisObj, str, encoding);
}


/**
 * Check if a sequence is in an alphabet of an arbitrary language
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isInAlphabet
(JNIEnv * env, jobject obj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isInAlphabetSequence, env, obj, str, encoding, language);
}

/**
 * Check if a sequence is in the upper case portion of alphabet in
 * an arbitrary language and encoding.
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isUpperCaseInAlphabet
(JNIEnv * env, jobject obj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isUpperCaseInAlphabetSequence, env, obj, str, encoding, language);
}

/**
 * Check if a sequence is in the lower case portion of alphabet in
 * an arbitrary language and encoding.
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isLowerCaseInAlphabet
(JNIEnv * env, jobject obj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isLowerCaseInAlphabetSequence, env, obj, str, encoding, language);
}

/**
 * Check if a sequence is a punctuation mark of an alphabet in
 * an arbitrary language and encoding.
 */
JNIEXPORT jboolean JNICALL Java_com_Language_LanguageStringUtils_isPunctuationMarkInAlphabet
(JNIEnv * env, jobject obj, jstring str, jint encoding, jint language){
	return alphabetLanguageSequenceCheck(isPunctuationMarkInAlphabetSequence, env, obj, str, encoding, language);
}



