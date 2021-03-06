#if !defined(triaxial_ellipsoid_h)
#define triaxial_ellipsoid_h
/** Structure definition for cylinder parameters
 * [PYTHONCLASS] = TriaxialEllipsoidModel
 * [DISP_PARAMS] = semi_axisA, semi_axisB, semi_axisC,axis_theta, axis_phi, axis_psi
	[DESCRIPTION] = <text>Note: During fitting ensure that the inequality A<B<C is not
	violated. Otherwise the calculation will
	not be correct.
	</text>
	[FIXED]= <text>axis_psi.width; axis_phi.width; axis_theta.width; semi_axisA.width; semi_axisB.width; semi_axisC.width </text>
	[ORIENTATION_PARAMS]= <text>axis_psi; axis_phi; axis_theta; axis_psi.width; axis_phi.width; axis_theta.width</text>
 **/
typedef struct {
    /// Scale factor
    //  [DEFAULT]=scale=1.0
    double scale;
    /// semi -axis A of the triaxial_ellipsoid [A]
    //  [DEFAULT]=semi_axisA= 35.0 [A]
    double semi_axisA;
    /// semi -axis B of the triaxial_ellipsoid [A]
    //  [DEFAULT]=semi_axisB=100.0 [A]
    double semi_axisB;
	/// semi -axis C of the triaxial_ellipsoid [A]
    //  [DEFAULT]=semi_axisC=400.0 [A]
    double semi_axisC;
    /// sldEll [1/A^(2)]
    //  [DEFAULT]=sldEll=1.0e-6 [1/A^(2)]
    double sldEll;
    /// sldSolv [1/A^(2)]
    //  [DEFAULT]=sldSolv=6.3e-6 [1/A^(2)]
    double sldSolv;
	/// Incoherent Background [1/cm] 0.00
	//  [DEFAULT]=background=0.0 [1/cm]
	double background;
    /// Orientation of the triaxial_ellipsoid axis w/respect incoming beam [deg]
    //  [DEFAULT]=axis_theta=57.325 [deg]
    double axis_theta;
    /// Orientation of the triaxial_ellipsoid in the plane of the detector [deg]
    //  [DEFAULT]=axis_phi=57.325 [deg]
    double axis_phi;
    /// Orientation of the cross section of the triaxial_ellipsoid in the plane of the detector [deg]
    //  [DEFAULT]=axis_psi=0.0 [deg]
    double axis_psi;

} TriaxialEllipsoidParameters;



/// 1D scattering function
double triaxial_ellipsoid_analytical_1D(TriaxialEllipsoidParameters *pars, double q);

/// 2D scattering function
double triaxial_ellipsoid_analytical_2D(TriaxialEllipsoidParameters *pars, double q, double phi);
double triaxial_ellipsoid_analytical_2DXY(TriaxialEllipsoidParameters *pars, double qx, double qy);
double triaxial_ellipsoid_analytical_2D_scaled(TriaxialEllipsoidParameters *pars, double q, double q_x, double q_y);

#endif
