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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\binaryHS_PSF11.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CBinaryHSPSF11Model
import copy    
    
class BinaryHSPSF11Model(CBinaryHSPSF11Model, BaseComponent):
    """ Class that evaluates a BinaryHSPSF11Model model. 
    	This file was auto-generated from ..\c_extensions\binaryHS_PSF11.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         l_radius        = 160.0 [A]
         s_radius        = 25.0 [A]
         vol_frac_ls     = 0.2 
         vol_frac_ss     = 0.2 
         ls_sld          = 3.5e-006 [1/A^(2)]
         ss_sld          = 5e-007 [1/A^(2)]
         solvent_sld     = 6.36e-006 [1/A^(2)]
         background      = 0.001 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CBinaryHSPSF11Model.__init__(self)
        
        ## Name of the model
        self.name = "BinaryHSPSF11Model"
        ## Model description
        self.description ="""
		Model parameters:
		
		l_radius : large radius of the binary hard sphere
		s_radius : small radius of the binary hard sphere
		vol_frac_ls : volume fraction of large spheres
		vol_frac_ss : volume fraction of small spheres
		ls_sld: large sphere  scattering length density
		ss_sld: small sphere scattering length density
		solvent_sld: solvent scattering length density
		background: incoherent background"""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['l_radius'] = ['[A]', None, None]
        self.details['s_radius'] = ['[A]', None, None]
        self.details['vol_frac_ls'] = ['', None, None]
        self.details['vol_frac_ss'] = ['', None, None]
        self.details['ls_sld'] = ['[1/A^(2)]', None, None]
        self.details['ss_sld'] = ['[1/A^(2)]', None, None]
        self.details['solvent_sld'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

		## fittable parameters
        self.fixed=['l_radius.width', 's_radius.width']
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(BinaryHSPSF11Model())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CBinaryHSPSF11Model.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CBinaryHSPSF11Model.runXY(self, x)
        
    def evalDistribition(self, x = []):
        """ Evaluate the model in cartesian coordinates
            @param x: input q[], or [qx[], qy[]]
            @return: scattering function P(q[])
        """
        return CBinaryHSPSF11Model.evalDistribition(self, x)
        
    def calculate_ER(self):
        """ Calculate the effective radius for P(q)*S(q)
            @return: the value of the effective radius
        """       
        return CBinaryHSPSF11Model.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CBinaryHSPSF11Model.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
