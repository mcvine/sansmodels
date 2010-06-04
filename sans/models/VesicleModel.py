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
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\vesicle.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CVesicleModel
import copy    
    
class VesicleModel(CVesicleModel, BaseComponent):
    """ 
    Class that evaluates a VesicleModel model. 
    This file was auto-generated from ..\c_extensions\vesicle.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         scale           = 1.0 
         radius          = 100.0 [A]
         thickness       = 30.0 [A]
         core_sld        = 6.36e-006 [1/A^(2)]
         shell_sld       = 5e-007 [1/A^(2)]
         background      = 0.0 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CVesicleModel.__init__(self)
        
        ## Name of the model
        self.name = "VesicleModel"
        ## Model description
        self.description ="""Model parameters:    radius : the core radius of the vesicle
		thickness: the shell thickness
		core_sld: the core SLD
		shell_sld: the shell SLD
		background: incoherent background
		scale : scale factor"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['radius'] = ['[A]', None, None]
        self.details['thickness'] = ['[A]', None, None]
        self.details['core_sld'] = ['[1/A^(2)]', None, None]
        self.details['shell_sld'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

        ## fittable parameters
        self.fixed=['radius.width', 'thickness.width']
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(VesicleModel())   
        
    def __getstate__(self):
        """
        return object state for pickling and copying
        """
        model_state = {'params': self.params, 'dispersion': self.dispersion, 'log': self.log}
        
        return self.__dict__, model_state
        
    def __setstate__(self, state):
        """
        create object from pickled state
        
        :param state: the state of the current model
        
        """
        
        self.__dict__, model_state = state
        self.params = model_state['params']
        self.dispersion = model_state['dispersion']
        self.log = model_state['log']
       	
   
    def run(self, x=0.0):
        """ 
        Evaluate the model
        
        :param x: input q, or [q,phi]
        
        :return: scattering function P(q)
        
        """
        
        return CVesicleModel.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CVesicleModel.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CVesicleModel.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CVesicleModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CVesicleModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
