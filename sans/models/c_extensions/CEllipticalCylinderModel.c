/** [PYTHONCLASS]
 *
 * C extension 
 *
 * WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY elliptical_cylinder.h
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

#include "elliptical_cylinder.h"

/// Error object for raised exceptions
static PyObject * [PYTHONCLASS]Error = NULL;


// Class definition
typedef struct {
    PyObject_HEAD
    /// Parameters
    PyObject * params;
    /// Log for unit testing
    PyObject * log;
    /// Model parameters
	EllipticalCylinderParameters model_pars;
} [PYTHONCLASS];


static void
[PYTHONCLASS]_dealloc([PYTHONCLASS]* self)
{
    self->ob_type->tp_free((PyObject*)self);
    

}

static PyObject *
[PYTHONCLASS]_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    [PYTHONCLASS] *self;
    
    self = ([PYTHONCLASS] *)type->tp_alloc(type, 0);
   
    return (PyObject *)self;
}

static int
[PYTHONCLASS]_init([PYTHONCLASS] *self, PyObject *args, PyObject *kwds)
{
    if (self != NULL) {
    	
    	// Create parameters
        self->params = PyDict_New();
        
        // Initialize parameter dictionary
        PyDict_SetItemString(self->params,"scale",Py_BuildValue("d",1.000000));
        PyDict_SetItemString(self->params,"cyl_psi",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"length",Py_BuildValue("d",400.000000));
        PyDict_SetItemString(self->params,"r_minor",Py_BuildValue("d",20.000000));
        PyDict_SetItemString(self->params,"cyl_theta",Py_BuildValue("d",1.570000));
        PyDict_SetItemString(self->params,"background",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"r_ratio",Py_BuildValue("d",1.500000));
        PyDict_SetItemString(self->params,"contrast",Py_BuildValue("d",0.000003));
        PyDict_SetItemString(self->params,"cyl_phi",Py_BuildValue("d",0.000000));

         
        // Create empty log
        self->log = PyDict_New();
        
        

    }
    return 0;
}

static PyMemberDef [PYTHONCLASS]_members[] = {
    {"params", T_OBJECT, offsetof([PYTHONCLASS], params), 0,
     "Parameters"},
    {"log", T_OBJECT, offsetof([PYTHONCLASS], log), 0,
     "Log"},
    {NULL}  /* Sentinel */
};

/** Read double from PyObject
    @param p PyObject
    @return double
*/
double [PYTHONCLASS]_readDouble(PyObject *p) {
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
static PyObject * run([PYTHONCLASS] *self, PyObject *args) {
	double q_value, phi_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	// Reader parameter dictionary
    self->model_pars.scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model_pars.cyl_psi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_psi") );
    self->model_pars.length = PyFloat_AsDouble( PyDict_GetItemString(self->params, "length") );
    self->model_pars.r_minor = PyFloat_AsDouble( PyDict_GetItemString(self->params, "r_minor") );
    self->model_pars.cyl_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_theta") );
    self->model_pars.background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model_pars.r_ratio = PyFloat_AsDouble( PyDict_GetItemString(self->params, "r_ratio") );
    self->model_pars.contrast = PyFloat_AsDouble( PyDict_GetItemString(self->params, "contrast") );
    self->model_pars.cyl_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_phi") );

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString([PYTHONCLASS]Error, 
	    	"[PYTHONCLASS].run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(q,phi)
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString([PYTHONCLASS]Error, 
	    		"[PYTHONCLASS].run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the q and phi values at which
	    // to evaluate I(q,phi)
	    q_value = [PYTHONCLASS]_readDouble(PyList_GET_ITEM(pars,0));
	    phi_value = [PYTHONCLASS]_readDouble(PyList_GET_ITEM(pars,1));
	    // Skip zero
	    if (q_value==0) {
	    	return Py_BuildValue("d",0.0);
	    }
		return Py_BuildValue("d",elliptical_cylinder_analytical_2D(&(self->model_pars),q_value,phi_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		q_value = [PYTHONCLASS]_readDouble(pars);		
		
		return Py_BuildValue("d",elliptical_cylinder_analytical_1D(&(self->model_pars),q_value));
	}	
}

/**
 * Function to call to evaluate model in cartesian coordinates
 * @param args: input q or [qx, qy]]
 * @return: function value
 */
static PyObject * runXY([PYTHONCLASS] *self, PyObject *args) {
	double qx_value, qy_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	// Reader parameter dictionary
    self->model_pars.scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model_pars.cyl_psi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_psi") );
    self->model_pars.length = PyFloat_AsDouble( PyDict_GetItemString(self->params, "length") );
    self->model_pars.r_minor = PyFloat_AsDouble( PyDict_GetItemString(self->params, "r_minor") );
    self->model_pars.cyl_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_theta") );
    self->model_pars.background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model_pars.r_ratio = PyFloat_AsDouble( PyDict_GetItemString(self->params, "r_ratio") );
    self->model_pars.contrast = PyFloat_AsDouble( PyDict_GetItemString(self->params, "contrast") );
    self->model_pars.cyl_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "cyl_phi") );

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString([PYTHONCLASS]Error, 
	    	"[PYTHONCLASS].run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(qx, qy))
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString([PYTHONCLASS]Error, 
	    		"[PYTHONCLASS].run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the qx and qy values at which
	    // to evaluate I(qx,qy)
	    qx_value = [PYTHONCLASS]_readDouble(PyList_GET_ITEM(pars,0));
	    qy_value = [PYTHONCLASS]_readDouble(PyList_GET_ITEM(pars,1));
		return Py_BuildValue("d",elliptical_cylinder_analytical_2DXY(&(self->model_pars),qx_value,qy_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		qx_value = [PYTHONCLASS]_readDouble(pars);		
		
		return Py_BuildValue("d",elliptical_cylinder_analytical_1D(&(self->model_pars),qx_value));
	}	
}

static PyObject * reset([PYTHONCLASS] *self, PyObject *args) {
    

    return Py_BuildValue("d",0.0);
}


static PyMethodDef [PYTHONCLASS]_methods[] = {
    {"run",      (PyCFunction)run     , METH_VARARGS,
      "Evaluate the model at a given Q or Q, phi"},
    {"runXY",      (PyCFunction)runXY     , METH_VARARGS,
      "Evaluate the model at a given Q or Qx, Qy"},
    {"reset",    (PyCFunction)reset   , METH_VARARGS,
      "Reset pair correlation"},
    //{"numerical_1D",      (PyCFunction)numerical_1D     , METH_VARARGS,
    //  "Evaluate the 1D model at a given Q"},
   {NULL}
};

static PyTypeObject [PYTHONCLASS]Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "[PYTHONCLASS]",             /*tp_name*/
    sizeof([PYTHONCLASS]),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)[PYTHONCLASS]_dealloc, /*tp_dealloc*/
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
    "[PYTHONCLASS] objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    [PYTHONCLASS]_methods,             /* tp_methods */
    [PYTHONCLASS]_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)[PYTHONCLASS]_init,      /* tp_init */
    0,                         /* tp_alloc */
    [PYTHONCLASS]_new,                 /* tp_new */
};


static PyMethodDef module_methods[] = {
    {NULL} 
};

/**
 * Function used to add the model class to a module
 * @param module: module to add the class to
 */ 
void add[PYTHONCLASS](PyObject *module) {
	PyObject *d;
	
    if (PyType_Ready(&[PYTHONCLASS]Type) < 0)
        return;

    Py_INCREF(&[PYTHONCLASS]Type);
    PyModule_AddObject(module, "[PYTHONCLASS]", (PyObject *)&[PYTHONCLASS]Type);
    
    d = PyModule_GetDict(module);
    [PYTHONCLASS]Error = PyErr_NewException("[PYTHONCLASS].error", NULL, NULL);
    PyDict_SetItemString(d, "[PYTHONCLASS]Error", [PYTHONCLASS]Error);
}

