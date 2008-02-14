#!/usr/bin/env python
""" Provide functionality for a C extension model

	WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 	         DO NOT MODIFY THIS FILE, MODIFY simcylinder.h
 	         AND RE-RUN THE GENERATOR SCRIPT

    @author: Mathieu Doucet / UTK
    @contact: mathieu.doucet@nist.gov
"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.prototypes.c_models import CSimCylinder
import copy    
    
class SimCylinder(CSimCylinder, BaseComponent):
    """ Class that evaluates a SimCylinder model. 
    	This file was auto-generated from simcylinder.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 1.0 
         radius          = 20.0 
         length          = 400.0 
         theta           = 0.0 
         phi             = 0.0 
         qmax            = 0.1 

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CSimCylinder.__init__(self)
        
        ## Name of the model
        self.name = "SimCylinder"
   
    def clone(self):
        """ Return a identical copy of self """
        obj = SimCylinder()
        obj.params = copy.deepcopy(self.params)
        return obj   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CSimCylinder.run(self, x)
# main
if __name__ == '__main__':
    app = SimCylinder()
    print "%s: f(1) = %g" % (app.name, app.run(1))
    print "%s: f(1,1.3) = %g" % (app.name, app.run([1, 1.3]))
   
# End of file
