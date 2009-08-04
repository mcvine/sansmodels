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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\hollow_cylinder.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CHollowCylinderModel
import copy    
    
class HollowCylinderModel(CHollowCylinderModel, BaseComponent):
    """ Class that evaluates a HollowCylinderModel model. 
    	This file was auto-generated from ..\c_extensions\hollow_cylinder.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 1.0 
         core_radius     = 20.0 [A]
         shell_radius    = 30.0 [A]
         length          = 400.0 [A]
         contrast        = 5.3e-006 [1/A�]
         background      = 0.01 [1/cm]
         axis_theta      = 1.57 [rad]
         axis_phi        = 0.0 [rad]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CHollowCylinderModel.__init__(self)
        
        ## Name of the model
        self.name = "HollowCylinderModel"
        ## Model description
        self.description =""""""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['core_radius'] = ['[A]', None, None]
        self.details['shell_radius'] = ['[A]', None, None]
        self.details['length'] = ['[A]', None, None]
        self.details['contrast'] = ['[1/A�]', None, None]
        self.details['background'] = ['[1/cm]', None, None]
        self.details['axis_theta'] = ['[rad]', None, None]
        self.details['axis_phi'] = ['[rad]', None, None]

		## fittable parameters
        self.fixed=['axis_phi.width', 'axis_theta.width', 'length.width', 'core_radius.width', 'shell_radius']
        
        ## parameters with orientation
        self.orientation_params =['axis_phi', 'axis_theta', 'axis_phi.width', 'axis_theta.width']
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(HollowCylinderModel())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CHollowCylinderModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CHollowCylinderModel.runXY(self, x)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CHollowCylinderModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file