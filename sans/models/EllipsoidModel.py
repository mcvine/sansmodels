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
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\ellipsoid.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CEllipsoidModel
import copy    
    
class EllipsoidModel(CEllipsoidModel, BaseComponent):
    """ 
    Class that evaluates a EllipsoidModel model. 
    This file was auto-generated from ..\c_extensions\ellipsoid.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         scale           = 1.0 
         radius_a        = 20.0 [A]
         radius_b        = 400.0 [A]
         sldEll          = 4e-006 [1/A^(2)]
         sldSolv         = 1e-006 [1/A^(2)]
         background      = 0.0 [1/cm]
         axis_theta      = 1.57 [rad]
         axis_phi        = 0.0 [rad]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CEllipsoidModel.__init__(self)
        
        ## Name of the model
        self.name = "EllipsoidModel"
        ## Model description
        self.description =""""P(q.alpha)= scale*f(q)^(2)+ bkg, where f(q)= 3*(sld_ell
		- sld_solvent)*V*[sin(q*r(Ra,Rb,alpha))
		-q*r*cos(qr(Ra,Rb,alpha))]
		/[qr(Ra,Rb,alpha)]^(3)"
		
		r(Ra,Rb,alpha)= [Rb^(2)*(sin(alpha))^(2)
		+ Ra^(2)*(cos(alpha))^(2)]^(1/2)
		
		scatter_sld: SLD of the scatter
		solvent_sld: SLD of the solvent
		sldEll: SLD of ellipsoid
		sldSolv: SLD of solvent
		V: volune of the Eliipsoid
		Ra: radius along the rotation axis
		of the Ellipsoid
		Rb: radius perpendicular to the
		rotation axis of the ellipsoid"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['radius_a'] = ['[A]', None, None]
        self.details['radius_b'] = ['[A]', None, None]
        self.details['sldEll'] = ['[1/A^(2)]', None, None]
        self.details['sldSolv'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]
        self.details['axis_theta'] = ['[rad]', None, None]
        self.details['axis_phi'] = ['[rad]', None, None]

        ## fittable parameters
        self.fixed=['axis_phi.width', 'axis_theta.width', 'radius_a.width', 'radius_b.width', 'length.width', 'r_minor.width']
        
        ## parameters with orientation
        self.orientation_params =['axis_phi.width', 'axis_theta.width', 'axis_phi', 'axis_theta']
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(EllipsoidModel())   
        
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
        
        return CEllipsoidModel.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CEllipsoidModel.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CEllipsoidModel.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CEllipsoidModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CEllipsoidModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
