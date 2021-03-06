/*
	TODO: Add 2D model
*/

#if !defined(lamellarPS_h)
#define lamellarPS_h
/** Structure definition for concentrated lamellar form factor parameters
 * [PYTHONCLASS] = LamellarPSModel
 * [DISP_PARAMS] = delta, spacing
   [DESCRIPTION] = <text>[Concentrated Lamellar Form Factor] Calculates the scattered
	   intensity from a lyotropic lamellar phase.
	   The intensity (form factor and structure
	   factor)calculated is for lamellae of
	   uniform scattering length density that
	   are randomly distributed in solution
	   (a powder average). The lamellae thickness
		is polydisperse. The model can also
		be applied to large, multi-lamellar vesicles.
		No resolution smeared version is included
		in the structure factor of this model.
		*Parameters: spacing = repeat spacing,
		delta = bilayer thickness,
		sld_bi = SLD_bilayer
		sld_sol = SLD_solvent
		n_plate = # of Lamellar plates
		caille = Caille parameter (<0.8 or <1)
		background = incoherent bgd
		scale = scale factor
</text>
   [FIXED]= <text>delta.width; spacing.width</text>
   [ORIENTATION_PARAMS]=

 **/
typedef struct {
    /// Scale factor
    //  [DEFAULT]=scale=1.0
    double scale;
    /// repeat spacing of the lamellar [A]
    //  [DEFAULT]=spacing=400 [A]
    double spacing;
	/// bilayer thicknes [A]
    //  [DEFAULT]=delta=30 [A]
    double delta;
    /// SLD of bilayer [1/A^(2)]
    //  [DEFAULT]=sld_bi=6.3e-6 [1/A^(2)]
    double sld_bi;
    /// SLD of solvent [1/A^(2)]
    //  [DEFAULT]=sld_sol=1.0e-6 [1/A^(2)]
    double sld_sol;
	 /// Number of lamellar plates
    //  [DEFAULT]=n_plates=20
    double n_plates;
    /// caille parameters
    //  [DEFAULT]=caille=0.1
    double caille;
	/// Incoherent Background [1/cm]
	//  [DEFAULT]=background=0.0 [1/cm]
	double background;

} LamellarPSParameters;

/// kernel
double LamellarPS_kernel(double dp[], double q);
/// 1D scattering function
double lamellarPS_analytical_1D(LamellarPSParameters *pars, double q);

/// 2D scattering function
double lamellarPS_analytical_2D(LamellarPSParameters *pars, double q, double phi);
double lamellarPS_analytical_2DXY(LamellarPSParameters *pars, double qx, double qy);

#endif
