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
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;
	PyObject * languageArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;
	int language = ENGLISH;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, "stringutils_isInAlphabet", 3, 3, &stringArg, &encodingArg, &languageArg)){
		Py_RETURN_FALSE;
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "py_stringutils_isInAlphabet expects a string");
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

	size_t ldist = isInAlphabet(buffer, encoding, language);
	if(ldist == 0){
		Py_RETURN_FALSE;
	}else{
		Py_RETURN_TRUE;
	}
}

/**
 * A python function to check if a character is a hex number
 */
static PyObject * py_charutils_isHexNumber(PyObject * self, PyObject * args){
	return checkStringContent(self, args, isHex,"charutils_isHexNumber",
			"Py_charutils_isHexNumber expects a string");
}

/**
 * A python function to check if a character is a natural number
 */
static PyObject * py_charutils_isNaturalNumber(PyObject * self, PyObject * args){
	return checkStringContent(self, args, isNumber, "charutils_isNaturalNumber",
			"Py_charutils_isNaturalNumber expects a string");
}

/**
 * A python function to check if a character is in the romance alphabet
 */
static PyObject * py_charutils_isInRomanceAlphabet(PyObject * self, PyObject * args){
	return checkStringContent(self, args, isInRomanceAlphabet, "charutils_isInRomanceAlphabet",
			"Py_charutils_isInRomanceAlphabet");
}

/**
 * A python function to check if a character is valid in a certain encoding
 */
static PyObject * py_charutils_isValidCharacter(PyObject * self, PyObject * args){
	return checkStringContent(self, args, isValidCharacter, "charutils_isValidCharacter",
			"Py_charutils_isValidCharacter");
}

/**
 * A python function that checks if a character is part of a language alphabet
 */
static PyObject * py_charutils_isInAlphabet(PyObject * self, PyObject * args){
	// The string argument for the string utils
	PyObject * stringArg = NULL;
	PyObject * encodingArg = NULL;
	PyObject * languageArg = NULL;

	// The main buffere of the py utils
	const char * buffer = NULL;
	int encoding = UTF8_BINARY;
	int language = ENGLISH;

	// Check if the pyarg unpack tuple
	if(!PyArg_UnpackTuple(args, "charutils_isInAlphabet", 2, 3, &stringArg, &encodingArg, &languageArg)){
		Py_RETURN_FALSE;
	}

	// Check if the argument is a unicode string or an ascii string. For the ascii
	// utf-8 can be encoded into the string.
	if(PyObject_TypeCheck(stringArg, &PyString_Type)){
		buffer = PyString_AS_STRING(stringArg);
	}else if(PyObject_TypeCheck(stringArg, &PyUnicode_Type)){
		buffer = PyUnicode_AS_DATA(stringArg);
	}else{
		PyErr_Format(PyExc_TypeError, "Py_charutils_isInAlphabet expects a string");
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

	if(languageArg != NULL){
		if(PyObject_TypeCheck(languageArg, &PyInt_Type)){
			int potentialLanguage = PyInt_AsLong(languageArg);
			if(potentialLanguage >= UTF8_BINARY && potentialLanguage <= ISO_8859_1){
				language = potentialLanguage;
			}
		}
	}

	size_t ldist = isInAlphabet(buffer, encoding, language);
	if(ldist == 0){
		Py_RETURN_FALSE;
	}else{
		Py_RETURN_TRUE;
	}
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
		{NULL, NULL}
};

/**
 * A list of all of the methods defined in the char utils module.
 */
static PyMethodDef charutils_methods[] = {
		{"isHexChar",py_charutils_isHexNumber, METH_VARARGS, "Is the character of text a hex number?"},
		{"isNaturalChar",py_charutils_isNaturalNumber, METH_VARARGS, "Is the character of text a natural number?"},
		{"isRomanceChar",py_charutils_isInRomanceAlphabet, METH_VARARGS, "Is the character part of the base romance alphabet?"},
		{"isValidChar",py_charutils_isValidCharacter, METH_VARARGS, "Is the character a valid character in the encoding?"},
		{"isInAlphabetChar",py_charutils_isInAlphabet, METH_VARARGS, "Is the character part of an alphabet?"},
		{NULL, NULL}
};

/**
 * Initialize the string utilties module using the Python/C API
 */
PyMODINIT_FUNC initLanguage(void){
	Py_InitModule3("Language.stringUtils", stringutils_methods, "A package of string utility function for Language");
	Py_InitModule3("Language.charUtils", charutils_methods, "A package of character utility function for Language");
}
