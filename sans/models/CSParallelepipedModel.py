#!/usr/bin/env python

##############################################################################
#	This software was developed by the University of Tennessee as part of the
#	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
#	project funded by the US National Science Foundation.
#
#	If you use DANSE applications to do scientific research that leads to
#	publication, we ask that you acknowledge the use of the software with the
#	following sentence:
#
#	"This work benefited from DANSE software developed under NSF award DMR-0520547."
#
#	copyright 2008, University of Tennessee
##############################################################################


""" 
Provide functionality for a C extension model

:WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\csparallelepiped.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans.models.sans_extension.c_models import CCSParallelepipedModel
import copy    

def create_CSParallelepipedModel():
    obj = CSParallelepipedModel()
    #CCSParallelepipedModel.__init__(obj) is called by CSParallelepipedModel constructor
    return obj

class CSParallelepipedModel(CCSParallelepipedModel, BaseComponent):
    """ 
    Class that evaluates a CSParallelepipedModel model. 
    This file was auto-generated from ..\c_extensions\csparallelepiped.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         scale           = 1.0 
         shortA          = 35.0 [A]
         midB            = 75.0 [A]
         longC           = 400.0 [A]
         rimA            = 10.0 [A]
         rimB            = 10.0 [A]
         rimC            = 10.0 [A]
         sld_rimA        = 2e-06 [1/A^(2)]
         sld_rimB        = 4e-06 [1/A^(2)]
         sld_rimC        = 2e-06 [1/A^(2)]
         sld_pcore       = 1e-06 [1/A^(2)]
         sld_solv        = 6e-06 [1/A^(2)]
         background      = 0.06 [1/cm]
         parallel_theta  = 0.0 [deg]
         parallel_phi    = 0.0 [deg]
         parallel_psi    = 0.0 [deg]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        #apply(CCSParallelepipedModel.__init__, (self,)) 
        CCSParallelepipedModel.__init__(self)
        
        ## Name of the model
        self.name = "CSParallelepipedModel"
        ## Model description
        self.description =""" Form factor for a rectangular Shell. Below are the Parameters.
		scale: scale factor
		shortA: length of short edge  [A]
		midB: length of another short edge [A]
		longC: length of long edge  of the parallelepiped [A]
		rimA: length of short edge  [A]
		rimB: length of another short edge [A]
		rimC: length of long edge  of the parallelepiped [A]
		sld_rimA: sld of rimA [1/A^(2)]
		sld_rimB: sld of rimB [1/A^(2)]
		sld_rimC: sld of rimC [1/A^(2)]
		sld_core: Pipe_sld [1/A^(2)]
		sld_solv: solvent_sld [1/A^(2)]
		background: incoherent Background [1/cm]"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['shortA'] = ['[A]', None, None]
        self.details['midB'] = ['[A]', None, None]
        self.details['longC'] = ['[A]', None, None]
        self.details['rimA'] = ['[A]', None, None]
        self.details['rimB'] = ['[A]', None, None]
        self.details['rimC'] = ['[A]', None, None]
        self.details['sld_rimA'] = ['[1/A^(2)]', None, None]
        self.details['sld_rimB'] = ['[1/A^(2)]', None, None]
        self.details['sld_rimC'] = ['[1/A^(2)]', None, None]
        self.details['sld_pcore'] = ['[1/A^(2)]', None, None]
        self.details['sld_solv'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]
        self.details['parallel_theta'] = ['[deg]', None, None]
        self.details['parallel_phi'] = ['[deg]', None, None]
        self.details['parallel_psi'] = ['[deg]', None, None]

        ## fittable parameters
        self.fixed=['shortA.width', 'midB.width', 'longC.width', 'parallel_phi.width', 'parallel_psi.width', 'parallel_theta.width']
        
        ## non-fittable parameters
        self.non_fittable = []
        
        ## parameters with orientation
        self.orientation_params = ['parallel_phi', 'parallel_psi', 'parallel_theta', 'parallel_phi.width', 'parallel_psi.width', 'parallel_theta.width']

    def __setstate__(self, state):
        """
        restore the state of a model from pickle
        """
        self.__dict__, self.params, self.dispersion = state
        
    def __reduce_ex__(self, proto):
        """
        Overwrite the __reduce_ex__ of PyTypeObject *type call in the init of 
        c model.
        """
        state = (self.__dict__, self.params, self.dispersion)
        return (create_CSParallelepipedModel,tuple(), state, None, None)
        
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(CSParallelepipedModel())   
       	
   
    def run(self, x=0.0):
        """ 
        Evaluate the model
        
        :param x: input q, or [q,phi]
        
        :return: scattering function P(q)
        
        """
        
        return CCSParallelepipedModel.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CCSParallelepipedModel.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CCSParallelepipedModel.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CCSParallelepipedModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CCSParallelepipedModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
