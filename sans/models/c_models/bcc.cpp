/**
	This software was developed by the University of Tennessee as part of the
	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
	project funded by the US National Science Foundation.

	If you use DANSE applications to do scientific research that leads to
	publication, we ask that you acknowledge the use of the software with the
	following sentence:

	"This work benefited from DANSE software developed under NSF award DMR-0520547."

	copyright 2008, University of Tennessee
 */

/**
 * Scattering model classes
 * The classes use the IGOR library found in
 *   sansmodels/src/libigor
 *
 */

#include <math.h>
#include "models.hh"
#include "parameters.hh"
#include <stdio.h>
using namespace std;

extern "C" {
	#include "libSphere.h"
	#include "bcc.h"
}

BCCrystalModel :: BCCrystalModel() {
	scale      = Parameter(1.0);
	dnn		= Parameter(220.0);
	d_factor = Parameter(0.06);
	radius     = Parameter(40.0, true);
	radius.set_min(0.0);
	sldSph   = Parameter(3.0e-6);
	sldSolv   = Parameter(6.3e-6);
	background = Parameter(0.0);
	theta  = Parameter(0.0, true);
	phi    = Parameter(0.0, true);
	psi    = Parameter(0.0, true);
}

/**
 * Function to evaluate 1D scattering function
 * The NIST IGOR library is used for the actual calculation.
 * @param q: q-value
 * @return: function value
 */
double BCCrystalModel :: operator()(double q) {
	double dp[7];

	// Fill parameter array for IGOR library
	// Add the background after averaging
	dp[0] = scale();
	dp[1] = dnn();
	dp[2] = d_factor();
	dp[3] = radius();
	dp[4] = sldSph();
	dp[5] = sldSolv();
	dp[6] = 0.0;

	// Get the dispersion points for the radius
	vector<WeightPoint> weights_rad;
	radius.get_weights(weights_rad);

	// Perform the computation, with all weight points
	double sum = 0.0;
	double norm = 0.0;
	double vol = 0.0;
	double result;

	// Loop over radius weight points
	for(int i=0; i<weights_rad.size(); i++) {
		dp[3] = weights_rad[i].value;

		//Un-normalize SphereForm by volume
		result = BCC_ParaCrystal(dp, q) * pow(weights_rad[i].value,3);
		// This FIXES a singualrity in the kernel in libigor.
		if ( result == INFINITY || result == NAN){
			result = 0.0;
		}
		sum += weights_rad[i].weight
			* result;
		//Find average volume
		vol += weights_rad[i].weight
			* pow(weights_rad[i].value,3);

		norm += weights_rad[i].weight;
	}

	if (vol != 0.0 && norm != 0.0) {
		//Re-normalize by avg volume
		sum = sum/(vol/norm);}
	return sum/norm + background();
}

/**
 * Function to evaluate 2D scattering function
 * @param q_x: value of Q along x
 * @param q_y: value of Q along y
 * @return: function value
 */
double BCCrystalModel :: operator()(double qx, double qy) {
	BCParameters dp;
	double q = sqrt(qx*qx + qy*qy);
	dp.scale      = scale();
	dp.dnn   = dnn();
	dp.d_factor   = d_factor();
	dp.radius  = radius();
	dp.sldSph   = sldSph();
	dp.sldSolv   = sldSolv();
	dp.background = 0.0;
	dp.theta  = theta();
	dp.phi    = phi();
	dp.psi    = psi();
	double pi = 4.0*atan(1.0);
	// Get the dispersion points for the radius
	vector<WeightPoint> weights_rad;
	radius.get_weights(weights_rad);

	// Get angular averaging for theta
	vector<WeightPoint> weights_theta;
	theta.get_weights(weights_theta);

	// Get angular averaging for phi
	vector<WeightPoint> weights_phi;
	phi.get_weights(weights_phi);

	// Get angular averaging for psi
	vector<WeightPoint> weights_psi;
	psi.get_weights(weights_psi);

	// Perform the computation, with all weight points
	double sum = 0.0;
	double norm = 0.0;
	double norm_vol = 0.0;
	double vol = 0.0;

	// Loop over radius weight points
	for(int i=0; i<weights_rad.size(); i++) {
		dp.radius = weights_rad[i].value;
		// Average over theta distribution
		for(int j=0; j< weights_theta.size(); j++) {
			dp.theta = weights_theta[j].value;
			// Average over phi distribution
			for(int k=0; k< weights_phi.size(); k++) {
				dp.phi = weights_phi[k].value;
				// Average over phi distribution
				for(int l=0; l< weights_psi.size(); l++) {
					dp.psi = weights_psi[l].value;
					//Un-normalize SphereForm by volume
					double _ptvalue = weights_rad[i].weight
										* weights_theta[j].weight
										* weights_phi[k].weight
										* weights_psi[l].weight
										* bc_analytical_2DXY(&dp, qx, qy);
										//* pow(weights_rad[i].value,3.0);
					// Consider when there is infinity or nan.
					// Actual value for this singular point are typically zero.
					if ( _ptvalue == INFINITY || _ptvalue == NAN){
						_ptvalue = 0.0;
					}
					if (weights_theta.size()>1) {
						_ptvalue *= fabs(sin(weights_theta[j].value*pi/180.0));
					}
					sum += _ptvalue;
					// This model dose not need the volume of spheres correction!!!
					norm += weights_rad[i].weight
							* weights_theta[j].weight
							* weights_phi[k].weight
							* weights_psi[l].weight;
				}
			}
		}
	}
	// Averaging in theta needs an extra normalization
	// factor to account for the sin(theta) term in the
	// integration (see documentation).
	if (weights_theta.size()>1) norm = norm / asin(1.0);

	if (vol != 0.0 && norm_vol != 0.0) {
		//Re-normalize by avg volume
		sum = sum/(vol/norm_vol);}

	return sum/norm + background();
}

/**
 * Function to evaluate 2D scattering function
 * @param pars: parameters of the BCCCrystal
 * @param q: q-value
 * @param phi: angle phi
 * @return: function value
 */
double BCCrystalModel :: evaluate_rphi(double q, double phi) {
	return (*this).operator()(q);
}

/**
 * Function to calculate effective radius
 * @return: effective radius value
 */
double BCCrystalModel :: calculate_ER() {
	//NOT implemented yet!!!
}
