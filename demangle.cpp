#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif /* PY_SSIZE_T_CLEAN */

#include <Python.h>
#include <string>
#include <cxxabi.h>

static PyObject *
method_demangle(PyObject *unused, PyObject *const *args, Py_ssize_t size)
{
    (void) unused;

    if (!size) {
        PyErr_BadArgument();
        return NULL;
    }

    PyObject *mangled = args[0];

    if (PyUnicode_Check(mangled)) {
        if (!(mangled = PyUnicode_AsASCIIString(mangled)))
            return NULL;
    } else if (PyBytes_Check(mangled)) {
        Py_INCREF(mangled);
    } else {
        PyErr_BadArgument();
        return NULL;
    }

    int status = -1;
    char *pmangled = PyBytes_AS_STRING(mangled); assert(pmangled);
    char *demangled = abi::__cxa_demangle(pmangled, NULL, NULL, &status);
    PyObject *retval = NULL;

    switch (status) {
    case 0:
        retval = PyUnicode_FromString(demangled);
        break;

    case -1:
        PyErr_NoMemory();
        break;

    case -2:
        retval = args[0];
        Py_INCREF(retval);
        break;

    case -3:
        PyErr_BadArgument();
        break;
    }
    Py_XDECREF(mangled);
    ::free(demangled);
    return retval;
}

static PyMethodDef demangle_methods[] = {
    {
        "demangle", (PyCFunction) method_demangle, METH_FASTCALL,
        "demangle(name: str) -> str\n"
    },
    {NULL, NULL, 0, NULL}, /* end */
};

static PyModuleDef demangle_def = {
    PyModuleDef_HEAD_INIT,
    .m_name = "cxademangle",
    .m_doc = NULL,
    .m_size = -1,
    .m_methods = demangle_methods,
};

extern "C" {

    PyMODINIT_FUNC
    PyInit_cxademangle(void)
    {
        return PyModule_Create(&demangle_def);
    }

} // extern "C"

/*
 * Local Variables:
 * c-file-style: "PEP7"
 * End:
 */
