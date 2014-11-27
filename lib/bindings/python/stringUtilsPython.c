#include <Python.h>
#include "bytesobject.h"
#include "stringUtils.h"
/**
 *
 */

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
 * A list of all of the methods defined in this module. The
 * length module is defined as a python function that
 */
static PyMethodDef stringutils_methods[] = {
		{"length", py_stringutils_length, METH_VARARGS, "Calculate the length of a string with different encodings"},
		{NULL, NULL}
};

/**
 * Initialize the string utilties module using the Python/C API
 */
PyMODINIT_FUNC initLanguage(void){
	Py_InitModule3("Language.stringUtils", stringutils_methods, "A package of string utility function for Language");
}