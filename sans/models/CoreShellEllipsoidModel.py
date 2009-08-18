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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\spheroid.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CCoreShellEllipsoidModel
import copy    
    
class CoreShellEllipsoidModel(CCoreShellEllipsoidModel, BaseComponent):
    """ Class that evaluates a CoreShellEllipsoidModel model. 
    	This file was auto-generated from ..\c_extensions\spheroid.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 1.0 
         equat_core      = 200.0 [A]
         polar_core      = 20.0 [A]
         equat_shell     = 250.0 [A]
         polar_shell     = 30.0 [A]
         contrast        = 1e-006 [1/A�]
         sld_solvent     = 6.3e-006 [1/A�]
         background      = 0.001 [1/cm]
         axis_theta      = 0.0 [rad]
         axis_phi        = 0.0 [rad]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CCoreShellEllipsoidModel.__init__(self)
        
        ## Name of the model
        self.name = "CoreShellEllipsoidModel"
        ## Model description
        self.description ="""[SpheroidCoreShellModel] Calculates the form factor for an spheroid
		ellipsoid particle with a core_shell structure.
		The form factor is averaged over all possible
		orientations of the ellipsoid such that P(q)
		= scale*<f^2>/Vol + bkg, where f is the
		single particle scattering amplitude.
		[Parameters]:
		equat_core = equatorial radius of core,
		polar_core = polar radius of core,
		equat_shell = equatorial radius of shell,
		polar_shell = polar radius of shell,
		contrast = SLD_core - SLD_shell
		sld_solvent = SLD_solvent
		background = Incoherent bkg
		scale =scale
		Note:It is the users' responsibility to ensure
		that shell radii are larger than core radii.
		oblate shell: equatorial radius > polar radius
		prolate shell: equatorial radius < polar radius"""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['equat_core'] = ['[A]', None, None]
        self.details['polar_core'] = ['[A]', None, None]
        self.details['equat_shell'] = ['[A]', None, None]
        self.details['polar_shell'] = ['[A]', None, None]
        self.details['contrast'] = ['[1/A�]', None, None]
        self.details['sld_solvent'] = ['[1/A�]', None, None]
        self.details['background'] = ['[1/cm]', None, None]
        self.details['axis_theta'] = ['[rad]', None, None]
        self.details['axis_phi'] = ['[rad]', None, None]

		## fittable parameters
        self.fixed=['equat_core.width', 'polar_core.width', 'equat_shell.width', 'polar_shell.width', 'axis_phi.width', 'axis_theta.width']
        
        ## parameters with orientation
        self.orientation_params =['axis_phi', 'axis_theta', 'axis_phi.width', 'axis_theta.width']
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(CoreShellEllipsoidModel())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CCoreShellEllipsoidModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CCoreShellEllipsoidModel.runXY(self, x)
        
    def evalDistribition(self, x = []):
        """ Evaluate the model in cartesian coordinates
            @param x: input q[], or [qx[], qy[]]
            @return: scattering function P(q[])
        """
        return CCoreShellEllipsoidModel.evalDistribition(self, x)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CCoreShellEllipsoidModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
