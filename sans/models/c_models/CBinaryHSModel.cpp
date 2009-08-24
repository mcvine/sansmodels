/**
	This software was developed by the University of Tennessee as part of the
	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
	project funded by the US National Science Foundation.

	If you use DANSE applications to do scientific research that leads to
	publication, we ask that you acknowledge the use of the software with the
	following sentence:

	"This work benefited from DANSE software developed under NSF award DMR-0520547."

	copyright 2008, University of Tennessee
 */

/** CBinaryHSModel
 *
 * C extension 
 *
 * WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY binaryHs.h
 *          AND RE-RUN THE GENERATOR SCRIPT
 *
 */
#define NO_IMPORT_ARRAY
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API_sans
 
extern "C" {
#include <Python.h>
#include <arrayobject.h>
#include "structmember.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "binaryHs.h"
}

#include "models.hh"
#include "dispersion_visitor.hh"

/// Error object for raised exceptions
static PyObject * CBinaryHSModelError = NULL;


// Class definition
typedef struct {
    PyObject_HEAD
    /// Parameters
    PyObject * params;
    /// Dispersion parameters
    PyObject * dispersion;
    /// Underlying model object
    BinaryHSModel * model;
    /// Log for unit testing
    PyObject * log;
} CBinaryHSModel;


static void
CBinaryHSModel_dealloc(CBinaryHSModel* self)
{
    self->ob_type->tp_free((PyObject*)self);
    

}

static PyObject *
CBinaryHSModel_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CBinaryHSModel *self;
    
    self = (CBinaryHSModel *)type->tp_alloc(type, 0);
   
    return (PyObject *)self;
}

static int
CBinaryHSModel_init(CBinaryHSModel *self, PyObject *args, PyObject *kwds)
{
    if (self != NULL) {
    	
    	// Create parameters
        self->params = PyDict_New();
        self->dispersion = PyDict_New();
        self->model = new BinaryHSModel();
        
        // Initialize parameter dictionary
        PyDict_SetItemString(self->params,"vol_frac_ls",Py_BuildValue("d",0.100000));
        PyDict_SetItemString(self->params,"background",Py_BuildValue("d",0.001000));
        PyDict_SetItemString(self->params,"vol_frac_ss",Py_BuildValue("d",0.200000));
        PyDict_SetItemString(self->params,"solvent_sld",Py_BuildValue("d",0.000006));
        PyDict_SetItemString(self->params,"ls_sld",Py_BuildValue("d",0.000003));
        PyDict_SetItemString(self->params,"ss_sld",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"s_radius",Py_BuildValue("d",25.000000));
        PyDict_SetItemString(self->params,"l_radius",Py_BuildValue("d",100.000000));
        // Initialize dispersion / averaging parameter dict
        DispersionVisitor* visitor = new DispersionVisitor();
        PyObject * disp_dict;
        disp_dict = PyDict_New();
        self->model->l_radius.dispersion->accept_as_source(visitor, self->model->l_radius.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "l_radius", disp_dict);
        disp_dict = PyDict_New();
        self->model->s_radius.dispersion->accept_as_source(visitor, self->model->s_radius.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "s_radius", disp_dict);


         
        // Create empty log
        self->log = PyDict_New();
        
        

    }
    return 0;
}

static PyMemberDef CBinaryHSModel_members[] = {
    {"params", T_OBJECT, offsetof(CBinaryHSModel, params), 0,
     "Parameters"},
	{"dispersion", T_OBJECT, offsetof(CBinaryHSModel, dispersion), 0,
	  "Dispersion parameters"},     
    {"log", T_OBJECT, offsetof(CBinaryHSModel, log), 0,
     "Log"},
    {NULL}  /* Sentinel */
};

/** Read double from PyObject
    @param p PyObject
    @return double
*/
double CBinaryHSModel_readDouble(PyObject *p) {
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
 * @param args: input numpy array q[] 
 * @return: numpy array object 
 */
 
static PyObject *evaluateOneDim(BinaryHSModel* model, PyArrayObject *q){
    PyArrayObject *result;
   
    // Check validity of array q , q must be of dimension 1, an array of double
    if (q->nd != 1 || q->descr->type_num != PyArray_DOUBLE)
    {
        //const char * message= "Invalid array: q->nd=%d,type_num=%d\n",q->nd,q->descr->type_num;
        //PyErr_SetString(PyExc_ValueError , message);
        return NULL;
    }
    result = (PyArrayObject *)PyArray_FromDims(q->nd, (int *)(q->dimensions), 
										  PyArray_DOUBLE);
	if (result == NULL) {
        const char * message= "Could not create result ";
        PyErr_SetString(PyExc_RuntimeError , message);
		return NULL;
	}
	 for (int i = 0; i < q->dimensions[0]; i++){
      double q_value  = *(double *)(q->data + i*q->strides[0]);
      double *result_value = (double *)(result->data + i*result->strides[0]);
      *result_value =(*model)(q_value);
	}
    return PyArray_Return(result); 
 }

 /**
 * Function to call to evaluate model
 * @param args: input numpy array  [x[],y[]]
 * @return: numpy array object 
 */
 static PyObject * evaluateTwoDimXY( BinaryHSModel* model, 
                              PyArrayObject *x, PyArrayObject *y)
 {
    PyArrayObject *result;
    int i,j, x_len, y_len, dims[2];
    //check validity of input vectors
    if (x->nd != 2 || x->descr->type_num != PyArray_DOUBLE
        || y->nd != 2 || y->descr->type_num != PyArray_DOUBLE
        || y->dimensions[1] != x->dimensions[0]){
        const char * message= "evaluateTwoDimXY  expect 2 numpy arrays";
        PyErr_SetString(PyExc_ValueError , message); 
        return NULL;
    }
   
	if (PyArray_Check(x) && PyArray_Check(y)) {
		
	    x_len = dims[1]= x->dimensions[0];
        y_len = dims[0]= y->dimensions[1];
	    
	    // Make a new double matrix of same dims
        result=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
        if (result == NULL){
	    const char * message= "Could not create result ";
        PyErr_SetString(PyExc_RuntimeError , message);
	    return NULL;
	    }
       
        /* Do the calculation. */
        for ( j=0; j< y_len; j++) {
            for ( i=0; i< x_len; i++) {
                double x_value = *(double *)(x->data + i*x->strides[0]);
      		    double y_value = *(double *)(y->data + j*y->strides[1]);
      			double *result_value = (double *)(result->data +
      			      j*result->strides[0] + i*result->strides[1]);
      			*result_value = (*model)(x_value, y_value);
            }           
        }
        return PyArray_Return(result); 
        
        }else{
		    PyErr_SetString(CBinaryHSModelError, 
                   "CBinaryHSModel.evaluateTwoDimXY couldn't run.");
	        return NULL;
		}      	
}
/**
 *  evalDistribution function evaluate a model function with input vector
 *  @param args: input q as vector or [qx, qy] where qx, qy are vectors
 *
 */ 
static PyObject * evalDistribution(CBinaryHSModel *self, PyObject *args){
	PyObject *qx, *qy;
	PyArrayObject * pars;
	int npars ,mpars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->vol_frac_ls = PyFloat_AsDouble( PyDict_GetItemString(self->params, "vol_frac_ls") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->vol_frac_ss = PyFloat_AsDouble( PyDict_GetItemString(self->params, "vol_frac_ss") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->ls_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "ls_sld") );
    self->model->ss_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "ss_sld") );
    self->model->s_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "s_radius") );
    self->model->l_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "l_radius") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "l_radius");
    self->model->l_radius.dispersion->accept_as_destination(visitor, self->model->l_radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "s_radius");
    self->model->s_radius.dispersion->accept_as_destination(visitor, self->model->s_radius.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CBinaryHSModelError, 
	    	"CBinaryHSModel.evalDistribution expects a q value.");
		return NULL;
	}
    // Check params
	
    if(PyArray_Check(pars)==1) {
		
	    // Length of list should 1 or 2
	    npars = pars->nd; 
	    if(npars==1) {
	        // input is a numpy array
	        if (PyArray_Check(pars)) {
		        return evaluateOneDim(self->model, (PyArrayObject*)pars); 
		    }
		}else{
		    PyErr_SetString(CBinaryHSModelError, 
                   "CBinaryHSModel.evalDistribution expect numpy array of one dimension.");
	        return NULL;
		}
    }else if( PyList_Check(pars)==1) {
    	// Length of list should be 2 for I(qx,qy)
	    mpars = PyList_GET_SIZE(pars); 
	    if(mpars!=2) {
	    	PyErr_SetString(CBinaryHSModelError, 
	    		"CBinaryHSModel.evalDistribution expects a list of dimension 2.");
	    	return NULL;
	    }
	     qx = PyList_GET_ITEM(pars,0);
	     qy = PyList_GET_ITEM(pars,1);
	     if (PyArray_Check(qx) && PyArray_Check(qy)) {
	         return evaluateTwoDimXY(self->model, (PyArrayObject*)qx,
		           (PyArrayObject*)qy);
		 }else{
		    PyErr_SetString(CBinaryHSModelError, 
                   "CBinaryHSModel.evalDistribution expect 2 numpy arrays in list.");
	        return NULL;
	     }
	}
	PyErr_SetString(CBinaryHSModelError, 
                   "CBinaryHSModel.evalDistribution couln't be run.");
	return NULL;
	
}

/**
 * Function to call to evaluate model
 * @param args: input q or [q,phi]
 * @return: function value
 */
static PyObject * run(CBinaryHSModel *self, PyObject *args) {
	double q_value, phi_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->vol_frac_ls = PyFloat_AsDouble( PyDict_GetItemString(self->params, "vol_frac_ls") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->vol_frac_ss = PyFloat_AsDouble( PyDict_GetItemString(self->params, "vol_frac_ss") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->ls_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "ls_sld") );
    self->model->ss_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "ss_sld") );
    self->model->s_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "s_radius") );
    self->model->l_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "l_radius") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "l_radius");
    self->model->l_radius.dispersion->accept_as_destination(visitor, self->model->l_radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "s_radius");
    self->model->s_radius.dispersion->accept_as_destination(visitor, self->model->s_radius.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CBinaryHSModelError, 
	    	"CBinaryHSModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(q,phi)
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CBinaryHSModelError, 
	    		"CBinaryHSModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the q and phi values at which
	    // to evaluate I(q,phi)
	    q_value = CBinaryHSModel_readDouble(PyList_GET_ITEM(pars,0));
	    phi_value = CBinaryHSModel_readDouble(PyList_GET_ITEM(pars,1));
	    // Skip zero
	    if (q_value==0) {
	    	return Py_BuildValue("d",0.0);
	    }
		return Py_BuildValue("d",(*(self->model)).evaluate_rphi(q_value,phi_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		q_value = CBinaryHSModel_readDouble(pars);		
		
		return Py_BuildValue("d",(*(self->model))(q_value));
	}	
}

/**
 * Function to call to evaluate model in cartesian coordinates
 * @param args: input q or [qx, qy]]
 * @return: function value
 */
static PyObject * runXY(CBinaryHSModel *self, PyObject *args) {
	double qx_value, qy_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->vol_frac_ls = PyFloat_AsDouble( PyDict_GetItemString(self->params, "vol_frac_ls") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->vol_frac_ss = PyFloat_AsDouble( PyDict_GetItemString(self->params, "vol_frac_ss") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->ls_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "ls_sld") );
    self->model->ss_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "ss_sld") );
    self->model->s_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "s_radius") );
    self->model->l_radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "l_radius") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "l_radius");
    self->model->l_radius.dispersion->accept_as_destination(visitor, self->model->l_radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "s_radius");
    self->model->s_radius.dispersion->accept_as_destination(visitor, self->model->s_radius.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CBinaryHSModelError, 
	    	"CBinaryHSModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(qx, qy))
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CBinaryHSModelError, 
	    		"CBinaryHSModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the qx and qy values at which
	    // to evaluate I(qx,qy)
	    qx_value = CBinaryHSModel_readDouble(PyList_GET_ITEM(pars,0));
	    qy_value = CBinaryHSModel_readDouble(PyList_GET_ITEM(pars,1));
	    return Py_BuildValue("d",(*(self->model))(qx_value,qy_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		qx_value = CBinaryHSModel_readDouble(pars);		
		
		return Py_BuildValue("d",(*(self->model))(qx_value));
	}	
}

static PyObject * reset(CBinaryHSModel *self, PyObject *args) {
    

    return Py_BuildValue("d",0.0);
}

static PyObject * set_dispersion(CBinaryHSModel *self, PyObject *args) {
	PyObject * disp;
	const char * par_name;

	if ( !PyArg_ParseTuple(args,"sO", &par_name, &disp) ) {
	    PyErr_SetString(CBinaryHSModelError,
	    	"CBinaryHSModel.set_dispersion expects a DispersionModel object.");
		return NULL;
	}
	void *temp = PyCObject_AsVoidPtr(disp);
	DispersionModel * dispersion = static_cast<DispersionModel *>(temp);


	// Ugliness necessary to go from python to C
	    // TODO: refactor this
    if (!strcmp(par_name, "l_radius")) {
        self->model->l_radius.dispersion = dispersion;
    } else    if (!strcmp(par_name, "s_radius")) {
        self->model->s_radius.dispersion = dispersion;
    } else {
	    PyErr_SetString(CBinaryHSModelError,
	    	"CBinaryHSModel.set_dispersion expects a valid parameter name.");
		return NULL;
	}

	DispersionVisitor* visitor = new DispersionVisitor();
	PyObject * disp_dict = PyDict_New();
	dispersion->accept_as_source(visitor, dispersion, disp_dict);
	PyDict_SetItemString(self->dispersion, par_name, disp_dict);
    return Py_BuildValue("i",1);
}


static PyMethodDef CBinaryHSModel_methods[] = {
    {"run",      (PyCFunction)run     , METH_VARARGS,
      "Evaluate the model at a given Q or Q, phi"},
    {"runXY",      (PyCFunction)runXY     , METH_VARARGS,
      "Evaluate the model at a given Q or Qx, Qy"},
      
    {"evalDistribution",  (PyCFunction)evalDistribution , METH_VARARGS,
      "Evaluate the model at a given Q or Qx, Qy vector "},
    {"reset",    (PyCFunction)reset   , METH_VARARGS,
      "Reset pair correlation"},
    {"set_dispersion",      (PyCFunction)set_dispersion     , METH_VARARGS,
      "Set the dispersion model for a given parameter"},
   {NULL}
};

static PyTypeObject CBinaryHSModelType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "CBinaryHSModel",             /*tp_name*/
    sizeof(CBinaryHSModel),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CBinaryHSModel_dealloc, /*tp_dealloc*/
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
    "CBinaryHSModel objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    CBinaryHSModel_methods,             /* tp_methods */
    CBinaryHSModel_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)CBinaryHSModel_init,      /* tp_init */
    0,                         /* tp_alloc */
    CBinaryHSModel_new,                 /* tp_new */
};


//static PyMethodDef module_methods[] = {
//    {NULL} 
//};

/**
 * Function used to add the model class to a module
 * @param module: module to add the class to
 */ 
void addCBinaryHSModel(PyObject *module) {
	PyObject *d;
	
    if (PyType_Ready(&CBinaryHSModelType) < 0)
        return;

    Py_INCREF(&CBinaryHSModelType);
    PyModule_AddObject(module, "CBinaryHSModel", (PyObject *)&CBinaryHSModelType);
    
    d = PyModule_GetDict(module);
    CBinaryHSModelError = PyErr_NewException("CBinaryHSModel.error", NULL, NULL);
    PyDict_SetItemString(d, "CBinaryHSModelError", CBinaryHSModelError);
}

