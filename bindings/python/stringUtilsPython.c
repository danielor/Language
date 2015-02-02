#include <Python.h>
#include "bytesobject.h"
#include "stringUtils.h"


/**
 * A wrapper of the underlying stringUtils:length function that handles different
 * type of python strings
 */
static PyObject * py_stringutils_length(PyObject * self, PyObject *args){
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, "stringutils_length", 1, 2, &stringArg, &encodingArg)){
		return PyInt_FromLong(-1);
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "Py_stringutils_length expects a string");
	}

	// Check for different types of encoding parameters to assert what state the length
	// parameter should be analyzed with different constraints
	if(encodingArg != NULL){
		if(PyObject_TypeCheck(encodingArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(encodingArg);
			if(potentialEncoding >= UTF8_BINARY && potentialEncoding <= ISO_8859_1){
				encoding = potentialEncoding;
			}
		}
	}
	size_t ldist = len(buffer, encoding);
	return PyInt_FromLong((long)ldist);
}

/**
 * A wrapper of the underlying stringUtils:lengthEscaped function that handles
 * different types of python strings
 */
static PyObject * py_stringutils_lengthescaped(PyObject * self, PyObject * args){
	// The arguments for the length escaped functionality
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;
	PyObject * escapedArg = NULL;
	PyObject * escapedEncodingArg = NULL;
	PyObject * endString = NULL;

	// The C arguments associated with the function lengthEscaped
	const char * buffer = NULL;
	int encoding = ASCII;
	const char * escapedChars = NULL;
	int escapedEncoding = ASCII_HEX_UTF_ESCAPE;
	const char * endChar = NULL;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, "stringutils_lengthEscaped", 2, 5, &stringArg, &encodingArg,
			&escapedArg, &escapedEncodingArg, &endString)){
		return PyInt_FromLong(-1);
	}

	// Check that a string is being passed
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "Py_stringutils_lengthEscaped expects an ASCII string");
	}

	// Ignore the different variables
	if(PyObject_TypeCheck(encodingArg, &PyInt_Type)){
		encoding =  PyInt_AsLong(encodingArg);
	}
	if(escapedArg != NULL){
		if(PyObject_TypeCheck(escapedArg, &PyString_Type)){
			escapedChars = PyString_AS_STRING(escapedArg);
		}
	}
	if(escapedEncodingArg != NULL){
		if(PyObject_TypeCheck(escapedEncodingArg, &PyInt_Type)){
			escapedEncoding = PyInt_AsLong(escapedEncodingArg);
		}
	}
	if(endString != NULL){
		if(PyObject_TypeCheck(endString, &PyString_Type)){
			endChar = PyString_AS_STRING(endString);
		}
	}

	size_t ldist = lenEscaped(buffer, encoding, escapedChars, escapedEncoding, endChar);
	return PyInt_FromLong((long)ldist);
}


/**
 * A python function that checks if a character is of a certain type
 */
static PyObject * checkStringContent(PyObject * self, PyObject * args, int (*func)(const char *, int),
		const char * unPackString, const char * errorString){
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, unPackString, 2, 2, &stringArg, &encodingArg)){
		Py_RETURN_FALSE;
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "%s",errorString);
		Py_RETURN_FALSE;
	}
	// Check for different types of encoding parameters to assert what state the length
	// parameter should be analyzed with different constraints
	if(encodingArg != NULL){
		if(PyObject_TypeCheck(encodingArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(encodingArg);
			if(potentialEncoding >= UTF8_BINARY && potentialEncoding <= ISO_8859_1){
				encoding = potentialEncoding;
			}
		}
	}
	size_t ldist = func(buffer, encoding);
	if(ldist == 0){
		Py_RETURN_FALSE;
	}else{
		Py_RETURN_TRUE;
	}
}

/**
 * A python function that checks if the string content is of a certain type
 * at an index
 */
static PyObject * checkStringContentAtIndex(PyObject * self, PyObject * args, int (*func)(const char *, int),
		const char * unPackString, const char * errorString){
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;
	PyObject * indexArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;
	int index = 0;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, unPackString, 2, 3, &stringArg, &encodingArg, &indexArg)){
		Py_RETURN_FALSE;
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "%s",errorString);
		Py_RETURN_FALSE;
	}
	// Check for different types of encoding parameters to assert what state the length
	// parameter should be analyzed with different constraints
	if(encodingArg != NULL){
		if(PyObject_TypeCheck(encodingArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(encodingArg);
			if(potentialEncoding >= UTF8_BINARY && potentialEncoding <= ISO_8859_1){
				encoding = potentialEncoding;
			}
		}
	}
	if(indexArg != NULL){
		if(PyObject_TypeCheck(indexArg, &PyInt_Type)){
			int potentialIndex = PyInt_AsLong(indexArg);
			if(potentialIndex >= 0){
				index = potentialIndex;
			}
		}
	}

	size_t ldist = isSequenceAtIndex(func, buffer, encoding, index);
	if(ldist == 0){
		Py_RETURN_FALSE;
	}else{
		Py_RETURN_TRUE;
	}
}

/**
 * A python function that checks if a character is of a certain type in a language
 */
static PyObject * checkLanguageStringContent(PyObject * self, PyObject * args, int (*func)(const char *, int, int),
		const char * unPackString, const char * errorString){
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;
	PyObject * languageArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;
	int language = ENGLISH;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, unPackString, 3, 3, &stringArg, &encodingArg, &languageArg)){
		Py_RETURN_FALSE;
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "%s",errorString);
		Py_RETURN_FALSE;
	}
	// Check for different types of encoding parameters to assert what state the length
	// parameter should be analyzed with different constraints
	if(encodingArg != NULL){
		if(PyObject_TypeCheck(encodingArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(encodingArg);
			if(potentialEncoding >= UTF8_BINARY && potentialEncoding <= ISO_8859_1){
				encoding = potentialEncoding;
			}
		}
	}

	// Check for differen type of encoding parameters
	if(languageArg == NULL){
		if(PyObject_TypeCheck(languageArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(languageArg);
			if(potentialEncoding >= ENGLISH && potentialEncoding <= FRENCH){
				language = potentialEncoding;
			}
		}
	}

	size_t ldist = func(buffer, encoding, language);
	if(ldist == 0){
		Py_RETURN_FALSE;
	}else{
		Py_RETURN_TRUE;
	}
}

/**
 * A python function that checks if a sequence of character is of certain type in
 * different languages after a particular index
 */
static PyObject * checkLanguageStringContentAtIndex(PyObject * self, PyObject * args, int (*func)(const char *, int, int),
		const char * unPackString, const char * errorString){
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;
	PyObject * languageArg = NULL;
	PyObject * indexArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;
	int language = ENGLISH;
	int index = 0;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, unPackString, 4, 4, &stringArg, &encodingArg, &languageArg, &indexArg)){
		Py_RETURN_FALSE;
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "%s",errorString);
		Py_RETURN_FALSE;
	}
	// Check for different types of encoding parameters to assert what state the length
	// parameter should be analyzed with different constraints
	if(encodingArg != NULL){
		if(PyObject_TypeCheck(encodingArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(encodingArg);
			if(potentialEncoding >= UTF8_BINARY && potentialEncoding <= ISO_8859_1){
				encoding = potentialEncoding;
			}
		}
	}

	// Check for differen type of encoding parameters
	if(languageArg == NULL){
		if(PyObject_TypeCheck(languageArg, &PyInt_Type)){
			int potentialEncoding = PyInt_AsLong(languageArg);
			if(potentialEncoding >= ENGLISH && potentialEncoding <= FRENCH){
				language = potentialEncoding;
			}
		}
	}

	// Check for differen type of encoding parameters
	if(indexArg == NULL){
		if(PyObject_TypeCheck(indexArg, &PyInt_Type)){
			int potentialIndex = PyInt_AsLong(indexArg);
			if(potentialIndex >= 0){
				index = potentialIndex;
			}
		}
	}
	size_t ldist = isLanguageSequenceAtIndex(func, buffer, encoding, language, index);
	if(ldist == 0){
		Py_RETURN_FALSE;
	}else{
		Py_RETURN_TRUE;
	}
}

/**
 * A python function that checks if a sequence of characters is a natural number
 * in different encodings
 */
static PyObject * py_stringutils_isNaturalNumber(PyObject * self, PyObject *args){
	return  checkStringContent(self, args, isNumberSequence,"stringutils_isNaturalNumber",
				"py_stringutils_isNaturalNumber expects a string");

}

/**
 * A python function that checks if a sequence of a characters is a hex number
 * in different encodings
 */
static PyObject * py_stringutils_isHexNumber(PyObject * self, PyObject * args){
	return  checkStringContent(self, args, isHexSequence,"stringutils_isHexNumber",
			"py_stringutils_isHexNumber expects a string");
}

/**
 * A python object that checks if a sequence of character is valid in different
 * encodings
 */
static PyObject * py_stringutils_isValid(PyObject * self, PyObject * args){
	return  checkStringContent(self, args, isValidCharacterSequence,"stringutils_isHexNumber",
			"Py_stringutils_length expects a string");
}

/**
 * A python function that checks if a sequence of characters is part of the
 * romance alphabet
 */
static PyObject * py_stringutils_isInRomanceAlphabet(PyObject * self, PyObject * args){
	return  checkStringContent(self, args, isInRomanceAlphabetSequence,"stringutils_isInRomanceAlphabet",
				"Py_stringutils_length expects a string");
}

/**
 * A python function that checks if a sequence of characeters is part of an alphabet
 * for a specific language and encoding
 */
static PyObject * py_stringutils_isInAlphabet(PyObject * self, PyObject * args){
	return checkLanguageStringContent(self, args, isInAlphabetSequence, "stringutils_isInAlphabet",
			"Py_stringutils_length expects a string");
}

/**
 * A python function to check if a character is upper case in a certain  encoding
 * and language
 */
static PyObject * py_stringutils_isUpperCaseInAlphabetSequence(PyObject * self, PyObject * args){
	return checkLanguageStringContent(self, args, isUpperCaseInAlphabetSequence, "charutils_isUpperCaseInAlphabetSequence",
			"py_stringutils_isUpperCaseInAlphabetSequence");
}

/**
 * A python function to check if a character is upper case in a certain  encoding
 * and language
 */
static PyObject * py_stringutils_isLowerCaseInAlphabetSequence(PyObject * self, PyObject * args){
	return checkLanguageStringContent(self, args, isLowerCaseInAlphabetSequence, "charutils_isLowerCaseInAlphabetSequence",
			"py_stringutils_isLowerCaseInAlphabetSequence");
}

/**
 * A python function to check if a character is a punctuation mark in a certain  encoding
 * and language
 */
static PyObject * py_stringutils_isPunctuationMarkInAlphabetSequence(PyObject * self, PyObject * args){
	return checkLanguageStringContent(self, args, isPunctuationMarkInAlphabetSequence, "stringutils_isPunctuationMarkInAlphabet",
			"py_stringutils_isPunctuationMarkInAlphabetSequence");
}

/**
 * A python function to check if a character is a hex number
 */
static PyObject * py_charutils_isHexNumber(PyObject * self, PyObject * args){
	return checkStringContentAtIndex(self, args, isHex,"charutils_isHexNumber",
			"Py_charutils_isHexNumber expects a string");
}

/**
 * A python function to check if a character is a natural number
 */
static PyObject * py_charutils_isNaturalNumber(PyObject * self, PyObject * args){
	return checkStringContentAtIndex(self, args, isNumber, "charutils_isNaturalNumber",
			"Py_charutils_isNaturalNumber expects a string");
}

/**
 * A python function to check if a character is in the romance alphabet
 */
static PyObject * py_charutils_isInRomanceAlphabet(PyObject * self, PyObject * args){
	return checkStringContentAtIndex(self, args, isInRomanceAlphabet, "charutils_isInRomanceAlphabet",
			"Py_charutils_isInRomanceAlphabet");
}

/**
 * A python function to check if a character is valid in a certain encoding
 */
static PyObject * py_charutils_isValidCharacter(PyObject * self, PyObject * args){
	return checkStringContentAtIndex(self, args, isValidCharacter, "charutils_isValidCharacter",
			"Py_charutils_isValidCharacter");
}

/**
 * A python function to check if a character is upper case in a certain  encoding
 * and language
 */
static PyObject * py_charutils_isUpperCaseInAlphabet(PyObject * self, PyObject * args){
	return checkLanguageStringContentAtIndex(self, args, isUpperCaseInAlphabet, "charutils_isUpperCaseInAlphabet",
			"py_charutils_isUpperCaseInAlphabet");
}

/**
 * A python function to check if a character is upper case in a certain  encoding
 * and language
 */
static PyObject * py_charutils_isLowerCaseInAlphabet(PyObject * self, PyObject * args){
	return checkLanguageStringContentAtIndex(self, args, isLowerCaseInAlphabet, "charutils_isLowerCaseInAlphabet",
			"py_charutils_isLowerCaseInAlphabet");
}

/**
 * A python function to check if a character is a punctuation mark in a certain  encoding
 * and language
 */
static PyObject * py_charutils_isPunctuationMarkInAlphabet(PyObject * self, PyObject * args){
	return checkLanguageStringContentAtIndex(self, args, isPunctuationMarkInAlphabet, "charutils_isPunctuationMarkInAlphabet",
			"py_charutils_isPunctuationMarknAlphabet");
}

/**
 * A python function that checks if a character is part of a language alphabet
 */
static PyObject * py_charutils_isInAlphabet(PyObject * self, PyObject * args){
	return checkLanguageStringContentAtIndex(self, args, isInAlphabet, "charutils_isInAlphabet",
				"Py_charutils_isInAlphabet expects a string");
}


/**
 * A list of all of the methods defined in this module. The
 * length module is defined as a python function that
 */
static PyMethodDef stringutils_methods[] = {
		{"length", py_stringutils_length, METH_VARARGS, "Calculate the length of a string with different encodings"},
		{"lengthEscaped", py_stringutils_lengthescaped, METH_VARARGS, "Calculate the length of an escaped string with different encodings"},
		{"isNaturalNumber", py_stringutils_isNaturalNumber, METH_VARARGS, "Is the sequence of text a natural number?"},
		{"isHexNumber",py_stringutils_isHexNumber, METH_VARARGS,"Is the sequence of text a hex number?"},
		{"isValid",py_stringutils_isValid, METH_VARARGS, "Is the sequence of text all valid characters?"},
		{"isInRomanceAlphabet", py_stringutils_isInRomanceAlphabet, METH_VARARGS, "Is the sequence text part of the romance alphabet? "},
		{"isInAlphabet", py_stringutils_isInAlphabet, METH_VARARGS, "Is the sequence of text part of an alphabet?"},
		{"isUpperCaseInAlphabet", py_stringutils_isUpperCaseInAlphabetSequence, METH_VARARGS, "Is the sequence of text part of the upper case of an alphabet?"},
		{"isLowerCaseInAlphabet", py_stringutils_isLowerCaseInAlphabetSequence, METH_VARARGS, "Is the sequence of text part of the lower case of an alphabet?"},
		{"isPunctuationMarkInAlphabet",py_stringutils_isPunctuationMarkInAlphabetSequence, METH_VARARGS, "Is the sequence of text a punctuation makr in an alphabet?"},
		{NULL, NULL}
};

/**
 * A list of all of the methods defined in the char utils module.
 */
static PyMethodDef charutils_methods[] = {
		{"isHexNumber",py_charutils_isHexNumber, METH_VARARGS, "Is the character of text a hex number?"},
		{"isNaturalNumber",py_charutils_isNaturalNumber, METH_VARARGS, "Is the character of text a natural number?"},
		{"isInRomanceAlphabet",py_charutils_isInRomanceAlphabet, METH_VARARGS, "Is the character part of the base romance alphabet?"},
		{"isValid",py_charutils_isValidCharacter, METH_VARARGS, "Is the character a valid character in the encoding?"},
		{"isInAlphabet",py_charutils_isInAlphabet, METH_VARARGS, "Is the character part of an alphabet?"},
		{"isUpperCaseInAlphabet", py_charutils_isUpperCaseInAlphabet, METH_VARARGS, "Is the character part of the upper case of an alphabet?"},
		{"isLowerCaseInAlphabet", py_charutils_isLowerCaseInAlphabet, METH_VARARGS, "Is the character part of the lower case of an alphabet?"},
		{"isPunctuationMarkInAlphabet",py_charutils_isPunctuationMarkInAlphabet, METH_VARARGS, "Is the character a punctuation makr in an alphabet?"},
		{NULL, NULL}
};

/**
 * Initialize the string utilties module using the Python/C API
 */
PyMODINIT_FUNC initLanguage(void){
	Py_InitModule3("Language.stringUtils", stringutils_methods, "A package of string utility function for Language");
	Py_InitModule3("Language.charUtils", charutils_methods, "A package of character utility function for Language");
}
