#include "dispersion_visitor.hh"
#include "parameters.hh"

#ifndef __MODELS_STANDALONE__
extern "C" {
	#include <Python.h>
}
#endif

void DispersionVisitor:: dispersion_to_dict(void* dispersion, void* dictionary) {
#ifndef __MODELS_STANDALONE__
	DispersionModel * disp = (DispersionModel*)dispersion;
	PyObject * dict = (PyObject*)dictionary;

	PyDict_SetItemString(dict, "type",  Py_BuildValue("s", "flat"));
    PyDict_SetItemString(dict, "npts",  Py_BuildValue("i", disp->npts));
    PyDict_SetItemString(dict, "width", Py_BuildValue("d", disp->width));
#endif
}

void DispersionVisitor:: gaussian_to_dict(void* dispersion, void* dictionary) {
#ifndef __MODELS_STANDALONE__
	GaussianDispersion * disp = (GaussianDispersion*)dispersion;
	PyObject * dict = (PyObject*)dictionary;

	PyDict_SetItemString(dict, "type",  Py_BuildValue("s", "gaussian"));
    PyDict_SetItemString(dict, "npts",  Py_BuildValue("i", disp->npts));
    PyDict_SetItemString(dict, "width", Py_BuildValue("d", disp->width));
    PyDict_SetItemString(dict, "nsigmas", Py_BuildValue("i", disp->nsigmas));
#endif
}

void DispersionVisitor:: array_to_dict(void* dispersion, void* dictionary) {
#ifndef __MODELS_STANDALONE__
	ArrayDispersion * disp = (ArrayDispersion*)dispersion;
	PyObject * dict = (PyObject*)dictionary;

    PyDict_SetItemString(dict, "type",  Py_BuildValue("s", "array"));
#endif
}

void DispersionVisitor:: dispersion_from_dict(void* dispersion, void* dictionary) {
#ifndef __MODELS_STANDALONE__
	DispersionModel * disp = (DispersionModel*)dispersion;
	PyObject * dict = (PyObject*)dictionary;

	disp->npts  = PyInt_AsLong( PyDict_GetItemString(dict, "npts") );
	disp->width = PyFloat_AsDouble( PyDict_GetItemString(dict, "width") );
#endif
}

void DispersionVisitor:: gaussian_from_dict(void* dispersion, void* dictionary) {
#ifndef __MODELS_STANDALONE__
	GaussianDispersion * disp = (GaussianDispersion*)dispersion;
	PyObject * dict = (PyObject*)dictionary;

	disp->npts    = PyInt_AsLong( PyDict_GetItemString(dict, "npts") );
	disp->width   = PyFloat_AsDouble( PyDict_GetItemString(dict, "width") );
	disp->nsigmas = PyFloat_AsDouble( PyDict_GetItemString(dict, "nsigmas") );
#endif
}

void DispersionVisitor:: array_from_dict(void* dispersion, void* dictionary) {}