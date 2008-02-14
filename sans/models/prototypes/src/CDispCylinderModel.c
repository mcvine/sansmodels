/** CDispCylinderModel
 *
 * C extension 
 *
 * WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY disperse_cylinder.h
 *          AND RE-RUN THE GENERATOR SCRIPT
 *
 * @author   M.Doucet / UTK
 */
 
#include <Python.h>
#include "structmember.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "disperse_cylinder.h"

static double UNDEFINED = 1000010010.1234567;

/// Error object for raised exceptions
static PyObject * CDispCylinderModelError = NULL;


// Class definition
typedef struct {
    PyObject_HEAD
    /// Parameters
    PyObject * params;
    /// Log for unit testing
    PyObject * log;
    /// Model parameters
	DispCylinderParameters model_pars;
} CDispCylinderModel;


static void
CDispCylinderModel_dealloc(CDispCylinderModel* self)
{
    self->ob_type->tp_free((PyObject*)self);
    

}

static PyObject *
CDispCylinderModel_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CDispCylinderModel *self;
    
    self = (CDispCylinderModel *)type->tp_alloc(type, 0);
   
    return (PyObject *)self;
}

static int
CDispCylinderModel_init(CDispCylinderModel *self, PyObject *args, PyObject *kwds)
{
    if (self != NULL) {
    	
    	// Create parameters
        self->params = PyDict_New();
        
        // Initialize parameter dictionary
        PyDict_SetItemString(self->params,"scale",Py_BuildValue("d",1.000000));
        PyDict_SetItemString(self->params,"sigma_phi",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"sigma_radius",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"sigma_theta",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"length",Py_BuildValue("d",400.000000));
        PyDict_SetItemString(self->params,"cyl_theta",Py_BuildValue("d",1.570000));
        PyDict_SetItemString(self->params,"background",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"radius",Py_BuildValue("d",20.000000));
        PyDict_SetItemString(self->params,"n_pts",Py_BuildValue("d",25.000000));
        PyDict_SetItemString(self->params,"contrast",Py_BuildValue("d",0.000003));
        PyDict_SetItemString(self->params,"cyl_phi",Py_BuildValue("d",0.000000));

         
        // Create empty log
        self->log = PyDict_New();
        
        

    }
    return 0;
}

static PyMemberDef CDispCylinderModel_members[] = {
    {"params", T_OBJECT, offsetof(CDispCylinderModel, params), 0,
     "Parameters"},
    {"log", T_OBJECT, offsetof(CDispCylinderModel, log), 0,
     "Log"},
    {NULL}  /* Sentinel */
};

/** Read double from PyObject
    @param p PyObject
    @return double
*/
double CDispCylinderModel_readDouble(PyObject *p) {
    if (PyFloat_Check(p)==1) {
        return (double)(((PyFloatObject *)(p))->ob_fval);
    } else if (PyInt_Check(p)==1) {
        return (double)(((PyIntObject *)(p))->ob_ival);
    } else if (PyLong_Check(p)==1) {
        return (double)PyLong_AsLong(p);
    } else {
        return 0.0;
    }
}


/**
 * Function to call to evaluate model
 * @param args: input q or [q,phi]
 * @return: function value
 */
static PyObject * run(CDispCylinderModel *self, PyObject *args) {
	double q_value, phi_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	// Reader parameter dictionary
    self->model_pars.scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model_pars.sigma_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_phi") );
    self->model_pars.sigma_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_radius") );
    self->model_pars.sigma_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_theta") );
    self->model_pars.length = PyFloat_AsDouble( PyDict_GetItemString(self->params, "length") );
    self->model_pars.cyl_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_theta") );
    self->model_pars.background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model_pars.radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model_pars.n_pts = PyFloat_AsDouble( PyDict_GetItemString(self->params, "n_pts") );
    self->model_pars.contrast = PyFloat_AsDouble( PyDict_GetItemString(self->params, "contrast") );
    self->model_pars.cyl_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_phi") );

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CDispCylinderModelError, 
	    	"CDispCylinderModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(q,phi)
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CDispCylinderModelError, 
	    		"CDispCylinderModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the q and phi values at which
	    // to evaluate I(q,phi)
	    q_value = CDispCylinderModel_readDouble(PyList_GET_ITEM(pars,0));
	    phi_value = CDispCylinderModel_readDouble(PyList_GET_ITEM(pars,1));
	    // Skip zero
	    if (q_value==0) {
	    	return Py_BuildValue("d",0.0);
	    }
		return Py_BuildValue("d",disperse_cylinder_analytical_2D(&(self->model_pars),q_value,phi_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		q_value = CDispCylinderModel_readDouble(pars);		
		
		return Py_BuildValue("d",disperse_cylinder_analytical_1D(&(self->model_pars),q_value));
	}	
}

static PyObject * reset(CDispCylinderModel *self, PyObject *args) {
    

    return Py_BuildValue("d",0.0);
}


static PyMethodDef CDispCylinderModel_methods[] = {
    {"run",      (PyCFunction)run     , METH_VARARGS,
      "Evaluate the model at a given Q"},
    {"reset",    (PyCFunction)reset   , METH_VARARGS,
      "Reset pair correlation"},
    //{"numerical_1D",      (PyCFunction)numerical_1D     , METH_VARARGS,
    //  "Evaluate the 1D model at a given Q"},
   {NULL}
};

static PyTypeObject CDispCylinderModelType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "CDispCylinderModel",             /*tp_name*/
    sizeof(CDispCylinderModel),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CDispCylinderModel_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "CDispCylinderModel objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    CDispCylinderModel_methods,             /* tp_methods */
    CDispCylinderModel_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)CDispCylinderModel_init,      /* tp_init */
    0,                         /* tp_alloc */
    CDispCylinderModel_new,                 /* tp_new */
};


static PyMethodDef module_methods[] = {
    {NULL} 
};

/**
 * Function used to add the model class to a module
 * @param module: module to add the class to
 */ 
void addCDispCylinderModel(PyObject *module) {
	PyObject *d;
	
    if (PyType_Ready(&CDispCylinderModelType) < 0)
        return;

    Py_INCREF(&CDispCylinderModelType);
    PyModule_AddObject(module, "CDispCylinderModel", (PyObject *)&CDispCylinderModelType);
    
    d = PyModule_GetDict(module);
    CDispCylinderModelError = PyErr_NewException("CDispCylinderModel.error", NULL, NULL);
    PyDict_SetItemString(d, "CDispCylinderModelError", CDispCylinderModelError);
}

