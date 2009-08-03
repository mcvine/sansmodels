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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\flexible_cylinder.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CFlexibleCylinderModel
import copy    
    
class FlexibleCylinderModel(CFlexibleCylinderModel, BaseComponent):
    """ Class that evaluates a FlexibleCylinderModel model. 
    	This file was auto-generated from ..\c_extensions\flexible_cylinder.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 1.0 
         length          = 1000.0 [A]
         kuhn_length     = 100.0 [A]
         radius          = 20.0 [A]
         contrast        = 5.3e-006 [1/A�]
         background      = 0.0001 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CFlexibleCylinderModel.__init__(self)
        
        ## Name of the model
        self.name = "FlexibleCylinderModel"
        ## Model description
        self.description =""" Note : 'scale' and 'contrast' are both multiplicative factors in the
		model and are perfectly correlated. One or
		both of these parameters must be held fixed
		during model fitting."""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['length'] = ['[A]', None, None]
        self.details['kuhn_length'] = ['[A]', None, None]
        self.details['radius'] = ['[A]', None, None]
        self.details['contrast'] = ['[1/A�]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

		## fittable parameters
        self.fixed=['length.width', 'kuhn_length.width', 'radius.width']
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(FlexibleCylinderModel())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CFlexibleCylinderModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CFlexibleCylinderModel.runXY(self, x)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CFlexibleCylinderModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
