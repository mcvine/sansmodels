#!/usr/bin/env python
""" WrapperGenerator class to generate model code automatically.
"""

import os, sys
import re

class WrapperGenerator:
    """ Python wrapper generator for C models
    
        The developer must provide a header file describing 
        the new model.
        
        To provide the name of the Python class to be
        generated, the .h file must contain the following 
        string in the comments:
        
        // [PYTHONCLASS] = my_model
        
        where my_model must be replaced by the name of the
        class that you want to import from sans.models.
        (example: [PYTHONCLASS] = MyModel
          will create a class MyModel in sans.models.MyModel.
          It will also create a class CMyModel in 
          sans_extension.c_models.)
          
        Also in comments, each parameter of the params 
        dictionary must be declared with a default value
        in the following way:
        
        // [DEFAULT]=param_name=default_value
        
        (example:
            //  [DEFAULT]=radius=20.0
        )
          
        See cylinder.h for an example.
        
        
        A .c file corresponding to the .h file should also
        be provided (example: my_model.h, my_model.c).
    
        The .h file should define two function definitions. For example,
        cylinder.h defines the following:
        
            /// 1D scattering function
            double cylinder_analytical_1D(CylinderParameters *pars, double q);
            
            /// 2D scattering function
            double cylinder_analytical_2D(CylinderParameters *pars, double q, double phi);
            
        The .c file implements those functions.
        
        @author: Mathieu Doucet / UTK
        @contact: mathieu.doucet@nist.gov
    """
    
    def __init__(self, filename):
        """ Initialization """
        
        ## Name of .h file to generate wrapper from
        self.file = filename
        
        # Info read from file
        
        ## Name of python class to write
        self.pythonClass = None
        ## Parser in struct section
        self.inStruct = False
        ## Name of struct for the c object
        self.structName = None
        ## Dictionary of parameters
        self.params = {}
        ## ModelCalculation module flag
        self.modelCalcFlag = False
        ## List of default parameters (text)
        self.default_list = ""
        ##description
        self.description=''
        ## Dictionary of units
        self.details = ""
        
    def __repr__(self):
        """ Simple output for printing """
        
        rep  = "Python class: %s\n" % self.pythonClass
        rep += "  struc name: %s\n" % self.structName
        rep += "  params:     %s\n" % self.params
        rep += "  description: %s\n"% self.description
        return rep
        
    def read(self):
        """ Reads in the .h file to catch parameters of the wrapper """
        
        # Check if the file is there
        if not os.path.isfile(self.file):
            raise ValueError, "File %s is not a regular file" % self.file
        
        # Read file
        f = open(self.file,'r')
        buf = f.read()
       
        self.default_list = "List of default parameters:\n"
        #lines = string.split(buf,'\n')
        lines = buf.split('\n')
        self.details  = "## Parameter details [units, min, max]\n"
        self.details += "        self.details = {}\n"
        # Catch Description
        key = "[DESCRIPTION]"
        find_description= 0
        temp=""
        for line in lines:
            if line.count(key)>0 :
                
                try:
                    find_description= 1
                    index = line.index(key)
                    toks = line[index:].split("=",1 )
                    temp=toks[1].lstrip().rstrip()
                    text='text'
                    key2="<%s>"%text.lower()
                    if re.match(key2,temp)!=None:
                        #index2 = line.index(key2)
                        #temp = temp[index2:]
                        toks2=temp.split(key2,1)
                        self.description=toks2[1]
                        text='text'
                        key2="</%s>"%text.lower()
                        if re.search(key2,toks2[1])!=None:
                            temp=toks2[1].split(key2,1)
                            self.description=temp[0]
                            break
                        #print self.description
                    else:
                        self.description=temp
                        break
                except:
                     raise ValueError, "Could not parse file %s" % self.file
            elif find_description==1:
                text='text'
                key2="</%s>"%text.lower()
                #print "second line",line,key2,re.search(key2,line)
                if re.search(key2,line)!=None:
                    tok=line.split(key2,1)
                    temp=tok[0].split("//",1)
                    self.description+=tok[1].lstrip().rstrip()
                    break
                else:
                    #if re.search("*",line)!=None:
                    #    temp=line.split("*",1)
                    #    self.description+='\n'+temp[1].lstrip().rstrip()
                    if re.search("//",line)!=None:
                        temp=line.split("//",1)
                        self.description+='\n\t\t'+temp[1].lstrip().rstrip()
                        
                    else:
                        self.description+='\n\t\t'+line.lstrip().rstrip()
                    
                
        for line in lines:
            
            # Catch class name
            key = "[PYTHONCLASS]"
            if line.count(key)>0:
                try:
                    index = line.index(key)
                    #toks = string.split( line[index:], "=" )
                    toks = line[index:].split("=" )
                    self.pythonClass = toks[1].lstrip().rstrip()
                except:
                    raise ValueError, "Could not parse file %s" % self.file
                
            # Catch struct name
            if line.count("typedef struct")>0:
                # We are entering a struct block
                self.inStruct = True
            
            if self.inStruct and line.count("}")>0:
                # We are exiting a struct block
                self.inStruct = False
    
                # Catch the name of the struct
                index = line.index("}")
                #toks = string.split(line[index+1:],";")
                toks = line[index+1:].split(";")
                # Catch pointer definition
                #toks2 = string.split(toks[0],',')
                toks2 = toks[0].split(',')
                self.structName = toks2[0].lstrip().rstrip()
          
            # Catch struct content
            key = "[DEFAULT]"
            if self.inStruct and line.count(key)>0:
                # Found a new parameter
                try:
                    index = line.index(key)
                    toks = line[index:].split("=")
                    toks2 = toks[2].split()
                    val = float(toks2[0])
                    self.params[toks[1]] = val
                    #self.pythonClass = toks[1].lstrip().rstrip()
                    units = ""
                    if len(toks2) >= 2:
                        units = toks2[1]
                    self.default_list += "         %-15s = %s %s\n" % \
                        (toks[1], val, units)
                    
                    # Check for min and max
                    min = "None"
                    max = "None"
                    if len(toks2) == 4:
                        min = toks2[2]
                        max = toks2[3]
                    
                    self.details += "        self.details['%s'] = ['%s', %s, %s]\n" % \
                        (toks[1].lstrip().rstrip(), units.lstrip().rstrip(), min, max)
                except:
                    raise ValueError, "Could not parse input file %s \n  %s" % \
                        (self.file, sys.exc_value)
                
                
            # Catch need for numerical calculations
            key = "CalcParameters calcPars"
            if line.count(key)>0:
                self.modelCalcFlag = True
            
                
                
    def write_c_wrapper(self):
        """ Writes the C file to create the python extension class 
            The file is written in C[PYTHONCLASS].c
        """
        
        file = open("C"+self.pythonClass+'.c', 'w')
        template = open("classTemplate.txt", 'r')
        
        tmp_buf = template.read()
        #tmp_lines = string.split(tmp_buf,'\n')
        tmp_lines = tmp_buf.split('\n')
        
        for tmp_line in tmp_lines:
            
            # Catch class name
            newline = self.replaceToken(tmp_line, 
                                        "[PYTHONCLASS]", 'C'+self.pythonClass)
            ##catch description
            #newline = self.replaceToken(tmp_line, 
            #                            "[DESCRIPTION]", self.description)
            # Catch class name
            newline = self.replaceToken(newline, 
                                        "[MODELSTRUCT]", self.structName)
            
            # Dictionary initialization
            param_str = "// Initialize parameter dictionary\n"
            for par in self.params:
                param_str += "        PyDict_SetItemString(self->params,\"%s\",Py_BuildValue(\"d\",%f));\n" % \
                    (par, self.params[par])
                
            newline = self.replaceToken(newline,
                                        "[INITDICTIONARY]", param_str)
            
            # Read dictionary
            param_str = "// Reader parameter dictionary\n"
            for par in self.params:
                param_str += "    self->model_pars.%s = PyFloat_AsDouble( PyDict_GetItemString(self->params, \"%s\") );\n" % \
                    (par, par)
                
            newline = self.replaceToken(newline, "[READDICTIONARY]", param_str)
                
            # Name of .c file
            #toks = string.split(self.file,'.')
            toks = self.file.split('.')
            newline = self.replaceToken(newline, "[C_FILENAME]", toks[0])
            
            # Include file
            newline = self.replaceToken(newline, 
                                        "[INCLUDE_FILE]", self.file)           
                
            # Numerical calcs dealloc
            dealloc_str = "\n"
            if self.modelCalcFlag:
                dealloc_str = "    modelcalculations_dealloc(&(self->model_pars.calcPars));\n"
            newline = self.replaceToken(newline, 
                                        "[NUMERICAL_DEALLOC]", dealloc_str)     
                
            # Numerical calcs init
            init_str = "\n"
            if self.modelCalcFlag:
                init_str = "        modelcalculations_init(&(self->model_pars.calcPars));\n"
            newline = self.replaceToken(newline, 
                                        "[NUMERICAL_INIT]", init_str)     
                
            # Numerical calcs reset
            reset_str = "\n"
            if self.modelCalcFlag:
                reset_str = "modelcalculations_reset(&(self->model_pars.calcPars));\n"
            newline = self.replaceToken(newline, 
                                        "[NUMERICAL_RESET]", reset_str)     
                
            # Write new line to the wrapper .c file
            file.write(newline+'\n')
            
            
        file.close()
        
    def write_python_wrapper(self):
        """ Writes the python file to create the python extension class 
            The file is written in ../[PYTHONCLASS].py
        """
        
        file = open("../"+self.pythonClass+'.py', 'w')
        template = open("modelTemplate.txt", 'r')
        
        tmp_buf = template.read()
        tmp_lines = tmp_buf.split('\n')
        
        for tmp_line in tmp_lines:
            
            # Catch class name
            newline = self.replaceToken(tmp_line, 
                                        "[CPYTHONCLASS]", 'C'+self.pythonClass)
            
            # Catch class name
            newline = self.replaceToken(newline, 
                                        "[PYTHONCLASS]", self.pythonClass)
            
            # Include file
            newline = self.replaceToken(newline, 
                                        "[INCLUDE_FILE]", self.file)    
                   
            # Include file
            newline = self.replaceToken(newline, 
                                        "[DEFAULT_LIST]", self.default_list)
            # Model Description
            newline = self.replaceToken(newline, 
                                        "[DESCRIPTION]", self.description)
            # Parameter details
            newline = self.replaceToken(newline, 
                                        "[PAR_DETAILS]", self.details)
            #print"write",tmp_line 
            # Write new line to the wrapper .c file
            file.write(newline+'\n')
           
        file.close()
        
        
    def replaceToken(self, line, key, value): #pylint: disable-msg=R0201
        """ Replace a token in the template file 
            @param line: line of text to inspect
            @param key: token to look for
            @param value: string value to replace the token with
            @return: new string value
        """
        lenkey = len(key)
        newline = line
        while newline.count(key)>0:
            index = newline.index(key)
            newline = newline[:index]+value+newline[index+lenkey:]
        return newline
        
        
# main
if __name__ == '__main__':
    if len(sys.argv)>1:
        print "Will look for file %s" % sys.argv[1]
        app = WrapperGenerator(sys.argv[1])
    else:
        app = WrapperGenerator("test.h")
    app.read()
    app.write_c_wrapper()
    app.write_python_wrapper()
    print app
   
# End of file        