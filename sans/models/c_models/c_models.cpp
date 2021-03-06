/** c_models
 *
 * Module containing all SANS model extensions
 *
 * @author   M.Doucet / UTK
 */
#include <Python.h>
#include <parameters.hh>
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API_sans
#include "arrayobject.h"


void addCCylinderModel(PyObject *module);
void addCBarBellModel(PyObject *module);
void addCCappedCylinderModel(PyObject *module);
void addCTriaxialEllipsoidModel(PyObject *module);
void addCParallelepipedModel(PyObject *module);
void addCCSParallelepipedModel(PyObject *module);
void addCSphereModel(PyObject *module);
void addCSphereSLDModel(PyObject *module);
void addCOnionModel(PyObject *module);
void addCPearlNecklaceModel(PyObject *module);
void addCReflModel(PyObject *module);
void addCReflAdvModel(PyObject *module);
void addCFuzzySphereModel(PyObject *module);
void addCHardsphereStructure(PyObject *module);
void addCStickyHSStructure(PyObject *module);
void addCSCCrystalModel(PyObject *module);
void addCFCCrystalModel(PyObject *module);
void addCBCCrystalModel(PyObject *module);
void addCSquareWellStructure(PyObject *module);
void addCHayterMSAStructure(PyObject *module);
void addCCoreShellModel(PyObject *module);
void addCCoreFourShellModel(PyObject *module);
void addCCoreShellCylinderModel(PyObject *module);
void addCEllipsoidModel(PyObject *module);
void addCEllipticalCylinderModel(PyObject *module);
void addCTriaxialEllipsoidModel(PyObject *module);
void addCFlexibleCylinderModel(PyObject *module);
void addCFlexCylEllipXModel(PyObject *module);
void addCStackedDisksModel(PyObject *module);
void addCLamellarPSModel(PyObject *module);
void addCLamellarPSHGModel(PyObject *module);
void addCLamellarPCrystalModel(PyObject *module);
void addCCoreShellEllipsoidModel(PyObject *module);
void addCDiamEllipFunc(PyObject *module);
void addCDiamCylFunc(PyObject *module);
void addCSLDCalFunc(PyObject *module);

//void addCOblateModel(PyObject *module);
//void addCProlateModel(PyObject *module);
void addCLamellarModel(PyObject *module);
void addCLamellarFFHGModel(PyObject *module);
void addCHollowCylinderModel(PyObject *module);
void addCMultiShellModel(PyObject *module);
void addCVesicleModel(PyObject *module);
void addCBinaryHSModel(PyObject *module);
void addCRPAModel(PyObject *module);
void addCFractalModel(PyObject *module);
void addCPoly_GaussCoil(PyObject *module);


extern "C" {
	//void addCCoreShellCylinderModel(PyObject *module);
	//void addCCoreShellModel(PyObject *module);
	//void addCEllipsoidModel(PyObject *module);
	//void addCEllipticalCylinderModel(PyObject *module);
	void addDisperser(PyObject *module);
	void addCGaussian(PyObject *module);
	void addCLorentzian(PyObject *module);
	void addCLogNormal(PyObject *module);
	void addCSchulz(PyObject *module);
}

/**
 * Delete a dispersion model object
 */
void del_dispersion_model(void *ptr){
	DispersionModel * disp = static_cast<DispersionModel *>(ptr);
	delete disp;
	return;
}

/**
 * Create a dispersion model as a python object
 */
PyObject * new_dispersion_model(PyObject *, PyObject *args) {
	DispersionModel *disp = new DispersionModel();
	return PyCObject_FromVoidPtr(disp, del_dispersion_model);
}


/**
 * Delete a lognormal dispersion model object
 */
void del_lognormal_dispersion(void *ptr){
	LogNormalDispersion * disp = static_cast<LogNormalDispersion *>(ptr);
	delete disp;
	return;
}

/**
 * Create a lognormal dispersion model as a python object
 */
PyObject * new_lognormal_dispersion(PyObject *, PyObject *args) {
	LogNormalDispersion *disp = new LogNormalDispersion();
	return PyCObject_FromVoidPtr(disp, del_lognormal_dispersion);
}

/**
 * Delete a gaussian dispersion model object
 */
void del_gaussian_dispersion(void *ptr){
	GaussianDispersion * disp = static_cast<GaussianDispersion *>(ptr);
	delete disp;
	return;
}

/**
 * Create a gaussian dispersion model as a python object
 */
PyObject * new_gaussian_dispersion(PyObject *, PyObject *args) {
	GaussianDispersion *disp = new GaussianDispersion();
	return PyCObject_FromVoidPtr(disp, del_gaussian_dispersion);
}


/**
 * Delete a rectangle dispersion model object
 */
void del_rectangle_dispersion(void *ptr){
	RectangleDispersion * disp = static_cast<RectangleDispersion *>(ptr);
	delete disp;
	return;
}

/**
 * Create a rectangle dispersion model as a python object
 */
PyObject * new_rectangle_dispersion(PyObject *, PyObject *args) {
	RectangleDispersion *disp = new RectangleDispersion();
	return PyCObject_FromVoidPtr(disp, del_rectangle_dispersion);
}


/**
 * Delete a schulz dispersion model object
 */
void del_schulz_dispersion(void *ptr){
	SchulzDispersion * disp = static_cast<SchulzDispersion *>(ptr);
	delete disp;
	return;
}
/**
 * Create a schulz dispersion model as a python object
 */
PyObject * new_schulz_dispersion(PyObject *, PyObject *args) {
	SchulzDispersion *disp = new SchulzDispersion();
	return PyCObject_FromVoidPtr(disp, del_schulz_dispersion);
}


/**
 * Delete an array dispersion model object
 */
void del_array_dispersion(void *ptr){
	ArrayDispersion * disp = static_cast<ArrayDispersion *>(ptr);
	delete disp;
	return;
}

/**
 * Create an array dispersion model as a python object
 */
PyObject * new_array_dispersion(PyObject *, PyObject *args) {
	ArrayDispersion *disp = new ArrayDispersion();
	return PyCObject_FromVoidPtr(disp, del_array_dispersion);
}

#define INVECTOR(obj,buf,len)										\
    do { \
        int err = PyObject_AsReadBuffer(obj, (const void **)(&buf), &len); \
        if (err < 0) return NULL; \
        len /= sizeof(*buf); \
    } while (0)

/**
 * Sets weights from a numpy array
 */
PyObject * set_weights(PyObject *, PyObject *args) {
	PyObject *val_obj;
	PyObject *wei_obj;
	PyObject *disp;
	Py_ssize_t nval;
	Py_ssize_t nwei;
	double *values;
	double *weights;
    //int i;

	if (!PyArg_ParseTuple(args, "OOO", &disp, &val_obj, &wei_obj)) return NULL;
	INVECTOR(val_obj, values, nval);
	INVECTOR(wei_obj, weights, nwei);

	// Sanity check
	if(nval!=nwei) return NULL;

	// Set the array pointers
	void *temp = PyCObject_AsVoidPtr(disp);
	DispersionModel * dispersion = static_cast<DispersionModel *>(temp);
	dispersion->set_weights(nval, values, weights);

	return Py_BuildValue("i",1);
}



/**
 * Define empty module
 */
static PyMethodDef module_methods[] = {
	{"new_dispersion_model", (PyCFunction)new_dispersion_model     , METH_VARARGS,
		  "Create a new DispersionModel object"},
	{"new_gaussian_model",   (PyCFunction)new_gaussian_dispersion, METH_VARARGS,
		  "Create a new GaussianDispersion object"},
	{"new_rectangle_model",   (PyCFunction)new_rectangle_dispersion, METH_VARARGS,
		  "Create a new RectangleDispersion object"},
    {"new_lognormal_model",   (PyCFunction)new_lognormal_dispersion, METH_VARARGS,
		  "Create a new LogNormalDispersion object"},
    {"new_schulz_model",   (PyCFunction)new_schulz_dispersion, METH_VARARGS,
		  "Create a new SchulzDispersion object"},
	{"new_array_model",      (PyCFunction)new_array_dispersion  , METH_VARARGS,
		  "Create a new ArrayDispersion object"},
	{"set_dispersion_weights",(PyCFunction)set_weights  , METH_VARARGS,
			"Create the dispersion weight arrays for an Array Dispersion object"},
    {NULL}
};


#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initc_models(void)
{
    PyObject* m;

    m = Py_InitModule3("c_models", module_methods,
                       "C extension module for SANS scattering models.");
	import_array();

	addCCylinderModel(m);
	addCBarBellModel(m);
	addCCappedCylinderModel(m);
	addCParallelepipedModel(m);
	addCCSParallelepipedModel(m);
	addCCoreShellCylinderModel(m);
	addCCoreShellModel(m);
	addCCoreFourShellModel(m);
	addCEllipsoidModel(m);
	addCSphereModel(m);
	addCSphereSLDModel(m);
	addCOnionModel(m);
	addCReflModel(m);
	addCReflAdvModel(m);
	addCFuzzySphereModel(m);
	addCHardsphereStructure(m);
	addCStickyHSStructure(m);
	addCSCCrystalModel(m);
	addCFCCrystalModel(m);
	addCBCCrystalModel(m);
	addCSquareWellStructure(m);
	addCHayterMSAStructure(m);
	addCEllipticalCylinderModel(m);
	addCTriaxialEllipsoidModel(m);
	addCFlexibleCylinderModel(m);
	addCFlexCylEllipXModel(m);
	addCStackedDisksModel(m);
	addCLamellarPSModel(m);
	addCLamellarPSHGModel(m);
	addCLamellarPCrystalModel(m);
	addCCoreShellEllipsoidModel(m);
	addCDiamEllipFunc(m);
	addCDiamCylFunc(m);
	addCSLDCalFunc(m);
	addCPearlNecklaceModel(m);
	addCLamellarModel(m);
	addCLamellarFFHGModel(m);
	addCHollowCylinderModel(m);
	addCMultiShellModel(m);
	addCBinaryHSModel(m);
	addDisperser(m);
	addCGaussian(m);
	addCSchulz(m);
	addCLogNormal(m);
	addCLorentzian(m);
	addCVesicleModel(m);
	addCPoly_GaussCoil(m);
	addCRPAModel(m);
	addCFractalModel(m);
}
