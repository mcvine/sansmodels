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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\lamellar.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CLamellarModel
import copy    
    
class LamellarModel(CLamellarModel, BaseComponent):
    """ Class that evaluates a LamellarModel model. 
        This file was auto-generated from ..\c_extensions\lamellar.h.
        Refer to that file and the structure it contains
        for details of the model.
        List of default parameters:
         scale           = 1.0 
         bi_thick        = 50.0 [A]
         sld_bi          = 1e-006 [1/A^(2)]
         sld_sol         = 6.3e-006 [1/A^(2)]
         background      = 0.0 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CLamellarModel.__init__(self)
        
        ## Name of the model
        self.name = "LamellarModel"
        ## Model description
        self.description ="""[Dilute Lamellar Form Factor](from a lyotropic lamellar phase)
		I(q)= 2*pi*P(q)/(delta *q^(2)), where
		P(q)=2*(contrast/q)^(2)*(1-cos(q*delta))^(2))
		bi_thick = bilayer thickness
		sld_bi = SLD of bilayer
		sld_sol = SLD of solvent
		background = Incoherent background
		scale = scale factor
		"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['bi_thick'] = ['[A]', None, None]
        self.details['sld_bi'] = ['[1/A^(2)]', None, None]
        self.details['sld_sol'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

        ## fittable parameters
        self.fixed=[]
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(LamellarModel())   
        
    def __getstate__(self):
        """ return object state for pickling and copying """
        print "__dict__",self.__dict__
        #self.__dict__['params'] = self.params
        #self.__dict__['dispersion'] = self.dispersion
        #self.__dict__['log'] = self.log
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
        
        return CLamellarModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CLamellarModel.runXY(self, x)
        
    def evalDistribition(self, x = []):
        """ Evaluate the model in cartesian coordinates
            @param x: input q[], or [qx[], qy[]]
            @return: scattering function P(q[])
        """
        return CLamellarModel.evalDistribition(self, x)
        
    def calculate_ER(self):
        """ Calculate the effective radius for P(q)*S(q)
            @return: the value of the effective radius
        """       
        return CLamellarModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CLamellarModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
