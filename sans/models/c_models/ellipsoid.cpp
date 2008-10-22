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
 *	TODO: refactor so that we pull in the old sansmodels.c_extensions
 */

#include <math.h>
#include "models.hh"
#include "parameters.hh"
#include <stdio.h>
using namespace std;

extern "C" {
	#include "libCylinder.h"
	#include "ellipsoid.h"
}

EllipsoidModel :: EllipsoidModel() {
	scale      = Parameter(1.0);
	radius_a   = Parameter(20.0, true);
	radius_a.set_min(0.0);
	radius_b   = Parameter(400.0, true);
	radius_b.set_min(0.0);
	contrast   = Parameter(3.e-6);
	background = Parameter(0.0);
	axis_theta  = Parameter(1.57, true);
	axis_phi    = Parameter(0.0, true);
}

/**
 * Function to evaluate 1D scattering function
 * The NIST IGOR library is used for the actual calculation.
 * @param q: q-value
 * @return: function value
 */
double EllipsoidModel :: operator()(double q) {
	double dp[5];

	// Fill parameter array for IGOR library
	// Add the background after averaging
	dp[0] = scale();
	dp[1] = radius_a();
	dp[2] = radius_b();
	dp[3] = contrast();
	dp[4] = 0.0;

	// Get the dispersion points for the radius_a
	vector<WeightPoint> weights_rad_a;
	radius_a.get_weights(weights_rad_a);

	// Get the dispersion points for the radius_b
	vector<WeightPoint> weights_rad_b;
	radius_b.get_weights(weights_rad_b);

	// Perform the computation, with all weight points
	double sum = 0.0;
	double norm = 0.0;

	// Loop over radius_a weight points
	for(int i=0; i<weights_rad_a.size(); i++) {
		dp[1] = weights_rad_a[i].value;

		// Loop over radius_b weight points
		for(int j=0; j<weights_rad_b.size(); j++) {
			dp[2] = weights_rad_b[j].value;

			sum += weights_rad_a[i].weight
				* weights_rad_b[j].weight * EllipsoidForm(dp, q);
			norm += weights_rad_a[i].weight
				* weights_rad_b[j].weight;
		}
	}
	return sum/norm + background();
}

/**
 * Function to evaluate 2D scattering function
 * @param q_x: value of Q along x
 * @param q_y: value of Q along y
 * @return: function value
 */
double EllipsoidModel :: operator()(double qx, double qy) {
	EllipsoidParameters dp;
	// Fill parameter array
	dp.scale      = scale();
	dp.radius_a   = radius_a();
	dp.radius_b   = radius_b();
	dp.contrast   = contrast();
	dp.background = 0.0;
	dp.axis_theta = axis_theta();
	dp.axis_phi   = axis_phi();

	// Get the dispersion points for the radius_a
	vector<WeightPoint> weights_rad_a;
	radius_a.get_weights(weights_rad_a);

	// Get the dispersion points for the radius_b
	vector<WeightPoint> weights_rad_b;
	radius_b.get_weights(weights_rad_b);

	// Get angular averaging for theta
	vector<WeightPoint> weights_theta;
	axis_theta.get_weights(weights_theta);

	// Get angular averaging for phi
	vector<WeightPoint> weights_phi;
	axis_phi.get_weights(weights_phi);

	// Perform the computation, with all weight points
	double sum = 0.0;
	double norm = 0.0;

	// Loop over radius weight points
	for(int i=0; i<weights_rad_a.size(); i++) {
		dp.radius_a = weights_rad_a[i].value;


		// Loop over length weight points
		for(int j=0; j<weights_rad_b.size(); j++) {
			dp.radius_b = weights_rad_b[j].value;

			// Average over theta distribution
			for(int k=0; k<weights_theta.size(); k++) {
				dp.axis_theta = weights_theta[k].value;

				// Average over phi distribution
				for(int l=0; l<weights_phi.size(); l++) {
					dp.axis_phi = weights_phi[l].value;

					double _ptvalue = weights_rad_a[i].weight
						* weights_rad_b[j].weight
						* weights_theta[k].weight
						* weights_phi[l].weight
						* ellipsoid_analytical_2DXY(&dp, qx, qy);
					if (weights_theta.size()>1) {
						_ptvalue *= sin(weights_theta[k].value);
					}
					sum += _ptvalue;

					norm += weights_rad_a[i].weight
						* weights_rad_b[j].weight
						* weights_theta[k].weight
						* weights_phi[l].weight;

				}
			}
		}
	}
	// Averaging in theta needs an extra normalization
	// factor to account for the sin(theta) term in the
	// integration (see documentation).
	if (weights_theta.size()>1) norm = norm / asin(1.0);
	return sum/norm + background();
}

/**
 * Function to evaluate 2D scattering function
 * @param pars: parameters of the cylinder
 * @param q: q-value
 * @param phi: angle phi
 * @return: function value
 */
double EllipsoidModel :: evaluate_rphi(double q, double phi) {
	double qx = q*cos(phi);
	double qy = q*sin(phi);
	return (*this).operator()(qx, qy);
}