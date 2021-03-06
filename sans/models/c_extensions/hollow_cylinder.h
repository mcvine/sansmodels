#if !defined(hollow_cylinder_h)
#define hollow_cylinder_h

/**
 * Structure definition for hollow cylinder parameters
 */
 //[PYTHONCLASS] = HollowCylinderModel
 //[DISP_PARAMS] = core_radius, radius, length, axis_theta, axis_phi
 //[DESCRIPTION] = <text> P(q) = scale*<f*f>/Vol + bkg, where f is the scattering amplitude.
 //					core_radius = the radius of core
 //				radius = the radius of shell
 // 			length = the total length of the cylinder
 //				sldCyl = SLD of the shell
 //				sldSolv = SLD of the solvent
 //				background = incoherent background
 //	</text>
 //[FIXED]= <text> axis_phi.width; axis_theta.width; length.width;core_radius.width; radius</text>
 //[ORIENTATION_PARAMS]= axis_phi; axis_theta;axis_phi.width; axis_theta.width


typedef struct {
    /// Scale factor
    //  [DEFAULT]=scale=1.0
    double scale;

    /// Core radius [A]
    //  [DEFAULT]=core_radius=20.0 [A]
    double core_radius;

    /// Shell radius [A]
    //  [DEFAULT]=radius=30.0 [A]
    double radius;

    /// Hollow cylinder length [A]
    //  [DEFAULT]=length=400.0 [A]
    double length;

    /// SLD_cylinder  [1/A^(2)]
    //  [DEFAULT]=sldCyl=6.3e-6 [1/A^(2)]
    double sldCyl;

    /// SLD_solvent  [1/A^(2)]
    //  [DEFAULT]=sldSolv=1.0e-6 [1/A^(2)]
    double sldSolv;

	/// Incoherent Background [1/cm]
	//  [DEFAULT]=background=0.01 [1/cm]
	double background;

    /// Orientation of the long axis of the hollow cylinder w/respect incoming beam [deg]
    //  [DEFAULT]=axis_theta=90.0 [deg]
    double axis_theta;

    /// Orientation of the long axis of the hollow cylinder in the plane of the detector [deg]
    //  [DEFAULT]=axis_phi=0.0 [deg]
    double axis_phi;

} HollowCylinderParameters;



/// 1D scattering function
double hollow_cylinder_analytical_1D(HollowCylinderParameters *pars, double q);

/// 2D scattering function
double hollow_cylinder_analytical_2D(HollowCylinderParameters *pars, double q, double phi);
double hollow_cylinder_analytical_2DXY(HollowCylinderParameters *pars, double qx, double qy);
double hollow_cylinder_analytical_2D_scaled(HollowCylinderParameters *pars, double q, double q_x, double q_y);

#endif
