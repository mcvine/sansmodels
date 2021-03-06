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
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\polygausscoil.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans.models.sans_extension.c_models import CPoly_GaussCoil
import copy    

def create_Poly_GaussCoil():
    obj = Poly_GaussCoil()
    #CPoly_GaussCoil.__init__(obj) is called by Poly_GaussCoil constructor
    return obj

class Poly_GaussCoil(CPoly_GaussCoil, BaseComponent):
    """ 
    Class that evaluates a Poly_GaussCoil model. 
    This file was auto-generated from ..\c_extensions\polygausscoil.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         scale           = 1.0 
         rg              = 60.0 [A]
         poly_m          = 2.0 [Mw/Mn]
         background      = 0.001 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        #apply(CPoly_GaussCoil.__init__, (self,)) 
        CPoly_GaussCoil.__init__(self)
        
        ## Name of the model
        self.name = "Poly_GaussCoil"
        ## Model description
        self.description ="""I(q)=(scale)*2*[(1+U*x)^(-1/U)+x-1]/[(1+U)*x^2] + background
		where x = [rg^2*q^2]
		and the polydispersity is
		U = [M_w/M_n]-1.
		scale = scale factor * volume fraction
		rg = radius of gyration
		poly_m = polydispersity of molecular weight
		background = incoherent background"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['rg'] = ['[A]', None, None]
        self.details['poly_m'] = ['[Mw/Mn]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

        ## fittable parameters
        self.fixed=[]
        
        ## non-fittable parameters
        self.non_fittable = []
        
        ## parameters with orientation
        self.orientation_params = []

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
        return (create_Poly_GaussCoil,tuple(), state, None, None)
        
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(Poly_GaussCoil())   
       	
   
    def run(self, x=0.0):
        """ 
        Evaluate the model
        
        :param x: input q, or [q,phi]
        
        :return: scattering function P(q)
        
        """
        
        return CPoly_GaussCoil.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CPoly_GaussCoil.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CPoly_GaussCoil.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CPoly_GaussCoil.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CPoly_GaussCoil.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
