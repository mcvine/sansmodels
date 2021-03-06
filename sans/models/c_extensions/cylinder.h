#if !defined(cylinder_h)
#define cylinder_h
/** Structure definition for cylinder parameters
 * [PYTHONCLASS] = CylinderModel
 * [DISP_PARAMS] = radius, length, cyl_theta, cyl_phi
   [DESCRIPTION] = <text> f(q)= 2*(sldCyl - sldSolv)*V*sin(qLcos(alpha/2))
				/[qLcos(alpha/2)]*J1(qRsin(alpha/2))/[qRsin(alpha)]

		P(q,alpha)= scale/V*f(q)^(2)+bkg
		V: Volume of the cylinder
		R: Radius of the cylinder
		L: Length of the cylinder
		J1: The bessel function
		alpha: angle betweenthe axis of the
		cylinder and the q-vector for 1D
		:the ouput is P(q)=scale/V*integral
		from pi/2 to zero of...
		f(q)^(2)*sin(alpha)*dalpha+ bkg
		</text>
	[FIXED]= <text>cyl_phi.width; cyl_theta.width; length.width;radius.width</text>
	[ORIENTATION_PARAMS]= <text>cyl_phi; cyl_theta; cyl_phi.width; cyl_theta.width</text>


 **/
typedef struct {
    /// Scale factor
    //  [DEFAULT]=scale=1.0
    double scale;
    /// Radius of the cylinder [A]
    //  [DEFAULT]=radius=20.0 [A]
    double radius;
    /// Length of the cylinder [A]
    //  [DEFAULT]=length=400.0 [A]
    double length;
    /// Contrast [1/A^(2)]
    //  [DEFAULT]=sldCyl=4.0e-6 [1/A^(2)]
    double sldCyl;
    /// sldCyl [1/A^(2)]
    //  [DEFAULT]=sldSolv=1.0e-6 [1/A^(2)]
    double sldSolv;
	/// Incoherent Background [1/cm] 0.00
	//  [DEFAULT]=background=0.0 [1/cm]
	double background;
    /// Orientation of the cylinder axis w/respect incoming beam [deg]
    //  [DEFAULT]=cyl_theta=60.0 [deg]
    double cyl_theta;
    /// Orientation of the cylinder in the plane of the detector [deg]
    //  [DEFAULT]=cyl_phi=60.0 [deg]
    double cyl_phi;

} CylinderParameters;



/// 1D scattering function
double cylinder_analytical_1D(CylinderParameters *pars, double q);

/// 2D scattering function
double cylinder_analytical_2D(CylinderParameters *pars, double q, double phi);
double cylinder_analytical_2DXY(CylinderParameters *pars, double qx, double qy);
double cylinder_analytical_2D_scaled(CylinderParameters *pars, double q, double q_x, double q_y);

#endif
