// The original code, of which work was not DANSE funded,
// was provided by J. Cho.
#if !defined(o_h)
#define refl_adv_h

/**
 * Structure definition for sphere parameters
 */
 //[PYTHONCLASS] = ReflAdvModel
 //[DISP_PARAMS] = thick_inter0
 //[DESCRIPTION] =<text>Calculate neutron reflectivity using the Parratt iterative formula
 //				Parameters:
 //				background:background
 //				scale: scale factor
 //				sld_bottom0: the SLD of the substrate
 //				sld_medium: the SLD of the incident medium
 //					or superstrate
 //				sld_flatN: the SLD of the flat region of
 //					the N'th layer
 //				thick_flatN: the thickness of the flat
 //					region of the N'th layer
 //				func_interN: the function used to describe
 //					the interface of the N'th layer
 //				nu_interN: the coefficient for the func_interN
 //				thick_interN: the thickness of the interface
 //					of the N'th layer
 //				Note: the layer number starts to increase
 //					from the bottom (substrate) to the top.
 //		</text>
 //[FIXED]=  <text></text>
 //[NON_FITTABLE_PARAMS]= <text>n_layers;func_inter0;func_inter1;func_inter2;func_inter3;func_inter4;func_inter5;func_inter5;func_inter7;func_inter8;func_inter9;func_inter10 </text>
 //[ORIENTATION_PARAMS]= <text> </text>

typedef struct {
	/// number of layers
	//  [DEFAULT]=n_layers=1
	int n_layers;
    /// Scale factor
    //  [DEFAULT]=scale= 1.0
	double scale;
    ///	thick_inter0 [A]
    //  [DEFAULT]=thick_inter0=50.0 [A]
	double thick_inter0;
	///	func_inter0
	//  [DEFAULT]=func_inter0= 0
	double func_inter0;
	///	sld_bottom0 [1/A^(2)]
	//  [DEFAULT]=sld_bottom0= 2.07e-6 [1/A^(2)]
	double sld_bottom0;
	///	sld_medium [1/A^(2)]
	//  [DEFAULT]=sld_medium= 1.0e-6 [1/A^(2)]
	double sld_medium;
	/// Background
	//  [DEFAULT]=background=0
	double background;

    //  [DEFAULT]=sld_flat1=4.0e-06 [1/A^(2)]
    double sld_flat1;
    //  [DEFAULT]=sld_flat2=3.5e-06 [1/A^(2)]
    double sld_flat2;
    //  [DEFAULT]=sld_flat3=4.0e-06 [1/A^(2)]
    double sld_flat3;
    //  [DEFAULT]=sld_flat4=3.5e-06 [1/A^(2)]
    double sld_flat4;
    //  [DEFAULT]=sld_flat5=4.0e-06 [1/A^(2)]
    double sld_flat5;
    //  [DEFAULT]=sld_flat6=3.5e-06 [1/A^(2)]
    double sld_flat6;
    //  [DEFAULT]=sld_flat7=4.0e-06 [1/A^(2)]
    double sld_flat7;
    //  [DEFAULT]=sld_flat8=3.5e-06 [1/A^(2)]
    double sld_flat8;
    //  [DEFAULT]=sld_flat9=4.0e-06 [1/A^(2)]
    double sld_flat9;
    //  [DEFAULT]=sld_flat10=3.5e-06 [1/A^(2)]
    double sld_flat10;

    //  [DEFAULT]=thick_inter1=50 [A]
    double thick_inter1;
    //  [DEFAULT]=thick_inter2=50 [A]
    double thick_inter2;
    //  [DEFAULT]=thick_inter3=50 [A]
    double thick_inter3;
    //  [DEFAULT]=thick_inter4=50 [A]
    double thick_inter4;
    //  [DEFAULT]=thick_inter5=50 [A]
    double thick_inter5;
    //  [DEFAULT]=thick_inter6=50 [A]
    double thick_inter6;
    //  [DEFAULT]=thick_inter7=50 [A]
    double thick_inter7;
    //  [DEFAULT]=thick_inter8=50 [A]
    double thick_inter8;
    //  [DEFAULT]=thick_inter9=50 [A]
    double thick_inter9;
    //  [DEFAULT]=thick_inter10=50 [A]
    double thick_inter10;

    //  [DEFAULT]=thick_flat1=100 [A]
    double thick_flat1;
    //  [DEFAULT]=thick_flat2=100 [A]
    double thick_flat2;
    //  [DEFAULT]=thick_flat3=100 [A]
    double thick_flat3;
    //  [DEFAULT]=thick_flat4=100 [A]
    double thick_flat4;
    //  [DEFAULT]=thick_flat5=100 [A]
    double thick_flat5;
    //  [DEFAULT]=thick_flat6=100 [A]
    double thick_flat6;
    //  [DEFAULT]=thick_flat7=100 [A]
    double thick_flat7;
    //  [DEFAULT]=thick_flat8=100 [A]
    double thick_flat8;
    //  [DEFAULT]=thick_flat9=100 [A]
    double thick_flat9;
    //  [DEFAULT]=thick_flat10=100 [A]
    double thick_flat10;

    //  [DEFAULT]=func_inter1=0
    double func_inter1;
    //  [DEFAULT]=func_inter2=0
    double func_inter2;
    //  [DEFAULT]=func_inter3=0
    double func_inter3;
    //  [DEFAULT]=func_inter4=0
    double func_inter4;
    //  [DEFAULT]=func_inter5=0
    double func_inter5;
    //  [DEFAULT]=func_inter6=0
    double func_inter6;
    //  [DEFAULT]=func_inter7=0
    double func_inter7;
    //  [DEFAULT]=func_inter8=0
    double func_inter8;
    //  [DEFAULT]=func_inter9=0
    double func_inter9;
    //  [DEFAULT]=func_inter10=0
    double func_inter10;

    //  [DEFAULT]=sldIM_flat1=0 [1/A^(2)]
    double sldIM_flat1;
    //  [DEFAULT]=sldIM_flat2=0 [1/A^(2)]
    double sldIM_flat2;
    //  [DEFAULT]=sldIM_flat3=0 [1/A^(2)]
    double sldIM_flat3;
    //  [DEFAULT]=sldIM_flat4=0 [1/A^(2)]
    double sldIM_flat4;
    //  [DEFAULT]=sldIM_flat5=0 [1/A^(2)]
    double sldIM_flat5;
    //  [DEFAULT]=sldIM_flat6=0 [1/A^(2)]
    double sldIM_flat6;
    //  [DEFAULT]=sldIM_flat7=0 [1/A^(2)]
    double sldIM_flat7;
    //  [DEFAULT]=sldIM_flat8=0 [1/A^(2)]
    double sldIM_flat8;
    //  [DEFAULT]=sldIM_flat9=0 [1/A^(2)]
    double sldIM_flat9;
    //  [DEFAULT]=sldIM_flat10=0 [1/A^(2)]
    double sldIM_flat10;

    //  [DEFAULT]=nu_inter1=2.5
    double nu_inter1;
    //  [DEFAULT]=nu_inter2=2.5
    double nu_inter2;
    //  [DEFAULT]=nu_inter3=2.5
    double nu_inter3;
    //  [DEFAULT]=nu_inter4=2.5
    double nu_inter4;
    //  [DEFAULT]=nu_inter5=2.5
    double nu_inter5;
    //  [DEFAULT]=nu_inter6=2.5
    double nu_inter6;
    //  [DEFAULT]=nu_inter7=2.5
    double nu_inter7;
    //  [DEFAULT]=nu_inter8=2.5
    double nu_inter8;
    //  [DEFAULT]=nu_inter9=2.5
    double nu_inter9;
    //  [DEFAULT]=nu_inter10=2.5
    double nu_inter10;


    //  [DEFAULT]=sldIM_sub0=0
    double sldIM_sub0;
    //  [DEFAULT]=sldIM_medium=0
    double sldIM_medium;
    //  [DEFAULT]=npts_inter=21.0
    double npts_inter;
    //  [DEFAULT]=nu_inter0=2.5
    double nu_inter0;
} ReflAdvParameters;

double re_adv_kernel(double dq[], double q);

/// 1D scattering function
double refl_adv_analytical_1D(ReflAdvParameters *pars, double q);

/// 2D scattering function
double refl_adv_analytical_2D(ReflAdvParameters *pars, double q, double phi);
double refl_adv_analytical_2DXY(ReflAdvParameters *pars, double qx, double qy);

#endif
