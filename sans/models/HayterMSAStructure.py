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
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\HayterMSA.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CHayterMSAStructure
import copy    
    
class HayterMSAStructure(CHayterMSAStructure, BaseComponent):
    """ 
    Class that evaluates a HayterMSAStructure model. 
    This file was auto-generated from ..\c_extensions\HayterMSA.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         effect_radius   = 20.75 [A]
         charge          = 19.0 
         volfraction     = 0.0192 
         temperature     = 318.16 [K]
         saltconc        = 0.0 [M]
         dielectconst    = 71.08 

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CHayterMSAStructure.__init__(self)
        
        ## Name of the model
        self.name = "HayterMSAStructure"
        ## Model description
        self.description ="""To calculate the structure factor (the Fourier transform of the
		pair correlation function g(r)) for a system of
		charged, spheroidal objects in a dielectric
		medium.
		When combined with an appropriate form
		factor, this allows for inclusion of
		the interparticle interference effects
		due to screened coulomb repulsion between
		charged particles.
		(Note: charge > 0 required.)
		
		Ref: JP Hansen and JB Hayter, Molecular
		Physics 46, 651-656 (1982).
		"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['effect_radius'] = ['[A]', None, None]
        self.details['charge'] = ['', None, None]
        self.details['volfraction'] = ['', None, None]
        self.details['temperature'] = ['[K]', None, None]
        self.details['saltconc'] = ['[M]', None, None]
        self.details['dielectconst'] = ['', None, None]

        ## fittable parameters
        self.fixed=['effect_radius.width']
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(HayterMSAStructure())   
        
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
        
        return CHayterMSAStructure.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CHayterMSAStructure.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CHayterMSAStructure.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CHayterMSAStructure.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CHayterMSAStructure.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
