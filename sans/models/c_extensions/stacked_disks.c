/**
 * Scattering model for a stacked disk
 * TODO: Add 2D analysis
 */

#include "stacked_disks.h"
#include <math.h>
#include "libCylinder.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Function to evaluate 1D scattering function
 * @param pars: parameters of the staked disks
 * @param q: q-value
 * @return: function value
 */
double stacked_disks_analytical_1D(StackedDisksParameters *pars, double q) {
	double dp[10];

	// Fill paramater array
	dp[0] = pars->scale;
	dp[1] = pars->radius;
	dp[2] = pars->core_thick;
	dp[3] = pars->layer_thick;
	dp[4] = pars->core_sld;
	dp[5] = pars->layer_sld;
	dp[6] = pars->solvent_sld;
	dp[7] = pars->n_stacking;
	dp[8] = pars->sigma_d;
	dp[9] = pars->background;

	// Call library function to evaluate model
	return StackedDiscs(dp, q);
}
/**
 * Function to evaluate 2D scattering function
 * @param pars: parameters of the staked disks
 * @param q: q-value
 * @return: function value
 */
double stacked_disks_analytical_2DXY(StackedDisksParameters *pars, double qx, double qy) {
	double q;
	q = sqrt(qx*qx+qy*qy);
    return stacked_disks_analytical_2D_scaled(pars, q, qx/q, qy/q);
}


/**
 * Function to evaluate 2D scattering function
 * @param pars: parameters of the staked disks
 * @param q: q-value
 * @param phi: angle phi
 * @return: function value
 */
double stacked_disks_analytical_2D(StackedDisksParameters *pars, double q, double phi) {
    return stacked_disks_analytical_2D_scaled(pars, q, cos(phi), sin(phi));
}

/**
 * Function to evaluate 2D scattering function
 * @param pars: parameters of the staked disks
 * @param q: q-value
 * @param q_x: q_x / q
 * @param q_y: q_y / q
 * @return: function value
 */
double stacked_disks_analytical_2D_scaled(StackedDisksParameters *pars, double q, double q_x, double q_y) {
	double cyl_x, cyl_y, cyl_z;
	double q_z;
	double alpha, vol, cos_val;
	double d, dum, halfheight;
	double answer;



    // parallelepiped orientation
    cyl_x = sin(pars->axis_theta) * cos(pars->axis_phi);
    cyl_y = sin(pars->axis_theta) * sin(pars->axis_phi);
    cyl_z = cos(pars->axis_theta);

    // q vector
    q_z = 0;

    // Compute the angle btw vector q and the
    // axis of the parallelepiped
    cos_val = cyl_x*q_x + cyl_y*q_y + cyl_z*q_z;

    // The following test should always pass
    if (fabs(cos_val)>1.0) {
    	printf("parallel_ana_2D: Unexpected error: cos(alpha)>1\n");
     	return 0;
    }

    // Note: cos(alpha) = 0 and 1 will get an
    // undefined value from Stackdisc_kern
	alpha = acos( cos_val );

	// Call the IGOR library function to get the kernel
	d = 2 * pars->layer_thick + pars->core_thick;
	halfheight = pars->core_thick/2.0;
	dum =alpha ;
	answer = Stackdisc_kern(q, pars->radius, pars->core_sld,pars->layer_sld,
		pars->solvent_sld, halfheight, pars->layer_thick, dum, pars->sigma_d, d, pars->n_stacking)/sin(alpha);

	// Multiply by contrast^2
	//answer *= pars->contrast*pars->contrast;

	//normalize by staked disks volume
    vol = acos(-1.0) * pars->radius * pars->radius * d * pars->n_stacking;
	answer /= vol;

	//convert to [cm-1]
	answer *= 1.0e8;

	//Scale
	answer *= pars->scale;

	// add in the background
	answer += pars->background;

	return answer;
}


