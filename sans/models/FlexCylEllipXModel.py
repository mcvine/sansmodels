#!/usr/bin/env python
"""
	This software was developed by the University of Tennessee as part of the
	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
	project funded by the US National Science Foundation.

	If you use DANSE applications to do scientific research that leads to
	publication, we ask that you acknowledge the use of the software with the
	following sentence:

	"This work benefited from DANSE software developed under NSF award DMR-0520547."

	copyright 2008, University of Tennessee
"""

""" Provide functionality for a C extension model

	WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\flexcyl_ellipX.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CFlexCylEllipXModel
import copy    
    
class FlexCylEllipXModel(CFlexCylEllipXModel, BaseComponent):
    """ Class that evaluates a FlexCylEllipXModel model. 
        This file was auto-generated from ..\c_extensions\flexcyl_ellipX.h.
        Refer to that file and the structure it contains
        for details of the model.
        List of default parameters:
         scale           = 1.0 
         length          = 1000.0 [A]
         kuhn_length     = 100.0 [A]
         radius          = 20.0 [A]
         axis_ratio      = 1.5 
         sldCyl          = 1e-006 [1/A^(2)]
         sldSolv         = 6.3e-006 [1/A^(2)]
         background      = 0.0001 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CFlexCylEllipXModel.__init__(self)
        
        ## Name of the model
        self.name = "FlexCylEllipXModel"
        ## Model description
        self.description =""" Note : scale and contrast=sldCyl-sldSolv are both multiplicative factors in the
		model and are perfectly correlated. One or
		both of these parameters must be held fixed
		during model fitting."""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['length'] = ['[A]', None, None]
        self.details['kuhn_length'] = ['[A]', None, None]
        self.details['radius'] = ['[A]', None, None]
        self.details['axis_ratio'] = ['', None, None]
        self.details['sldCyl'] = ['[1/A^(2)]', None, None]
        self.details['sldSolv'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

        ## fittable parameters
        self.fixed=['length.width', 'kuhn_length.width', 'radius.width', 'axis_ratio.width']
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(FlexCylEllipXModel())   
        
    def __getstate__(self):
        """ return object state for pickling and copying """
        model_state = {'params': self.params, 'dispersion': self.dispersion, 'log': self.log}
        
        return self.__dict__, model_state
        
    def __setstate__(self, state):
        """ create object from pickled state """
        
        self.__dict__, model_state = state
        self.params = model_state['params']
        self.dispersion = model_state['dispersion']
        self.log = model_state['log']
       	
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CFlexCylEllipXModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CFlexCylEllipXModel.runXY(self, x)
        
    def evalDistribution(self, x = []):
        """ Evaluate the model in cartesian coordinates
            @param x: input q[], or [qx[], qy[]]
            @return: scattering function P(q[])
        """
        return CFlexCylEllipXModel.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ Calculate the effective radius for P(q)*S(q)
            @return: the value of the effective radius
        """       
        return CFlexCylEllipXModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CFlexCylEllipXModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file