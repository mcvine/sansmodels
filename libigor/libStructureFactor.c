/*	SimpleFit.c

A simplified project designed to act as a template for your curve fitting function.
The fitting function is a simple polynomial. It works but is of no practical use.
*/

#include "StandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "libStructureFactor.h"
//Hard Sphere Structure Factor
//
double
HardSphereStruct(double dp[], double q)
{
	double denom,dnum,alpha,beta,gamm,a,asq,ath,afor,rca,rsa;
	double calp,cbeta,cgam,prefac,c,vstruc;
	double r,phi,struc;

	r = dp[0];
	phi = dp[1];
	//  compute constants
	denom = pow((1.0-phi),4);
	dnum = pow((1.0 + 2.0*phi),2);
	alpha = dnum/denom;
	beta = -6.0*phi*pow((1.0 + phi/2.0),2)/denom;
	gamm = 0.50*phi*dnum/denom;
	//
	//  calculate the structure factor
	//
	a = 2.0*q*r;
	asq = a*a;
	ath = asq*a;
	afor = ath*a;
	rca = cos(a);
	rsa = sin(a);
	calp = alpha*(rsa/asq - rca/a);
	cbeta = beta*(2.0*rsa/asq - (asq - 2.0)*rca/ath - 2.0/ath);
	cgam = gamm*(-rca/a + (4.0/a)*((3.0*asq - 6.0)*rca/afor + (asq - 6.0)*rsa/ath + 6.0/afor));
	prefac = -24.0*phi/a;
	c = prefac*(calp + cbeta + cgam);
	vstruc = 1.0/(1.0-c);
	struc = vstruc;

	return(struc);
}

//Sticky Hard Sphere Structure Factor
//
double
StickyHS_Struct(double dp[], double q)
{
	double qv;
	double rad,phi,eps,tau,eta;
	double sig,aa,etam1,qa,qb,qc,radic;
	double lam,lam2,test,mu,alpha,beta;
	double kk,k2,k3,ds,dc,aq1,aq2,aq3,aq,bq1,bq2,bq3,bq,sq;

	qv= q;
	rad = dp[0];
	phi = dp[1];
	eps = dp[2];
	tau = dp[3];

	eta = phi/(1.0-eps)/(1.0-eps)/(1.0-eps);

	sig = 2.0 * rad;
	aa = sig/(1.0 - eps);
	etam1 = 1.0 - eta;
	//C
	//C  SOLVE QUADRATIC FOR LAMBDA
	//C
	qa = eta/12.0;
	qb = -1.0*(tau + eta/(etam1));
	qc = (1.0 + eta/2.0)/(etam1*etam1);
	radic = qb*qb - 4.0*qa*qc;
	if(radic<0) {
		//if(x>0.01 && x<0.015)
	 	//	Print "Lambda unphysical - both roots imaginary"
	 	//endif
		return(-1.0);
	}
	//C   KEEP THE SMALLER ROOT, THE LARGER ONE IS UNPHYSICAL
	lam = (-1.0*qb-sqrt(radic))/(2.0*qa);
	lam2 = (-1.0*qb+sqrt(radic))/(2.0*qa);
	if(lam2<lam) {
		lam = lam2;
	}
	test = 1.0 + 2.0*eta;
	mu = lam*eta*etam1;
	if(mu>test) {
		//if(x>0.01 && x<0.015)
		// Print "Lambda unphysical mu>test"
		//endif
		return(-1.0);
	}
	alpha = (1.0 + 2.0*eta - mu)/(etam1*etam1);
	beta = (mu - 3.0*eta)/(2.0*etam1*etam1);
	//C
	//C   CALCULATE THE STRUCTURE FACTOR
	//C
	kk = qv*aa;
	k2 = kk*kk;
	k3 = kk*k2;
	ds = sin(kk);
	dc = cos(kk);
	aq1 = ((ds - kk*dc)*alpha)/k3;
	aq2 = (beta*(1.0-dc))/k2;
	aq3 = (lam*ds)/(12.0*kk);
	aq = 1.0 + 12.0*eta*(aq1+aq2-aq3);
	//
	bq1 = alpha*(0.5/kk - ds/k2 + (1.0 - dc)/k3);
	bq2 = beta*(1.0/kk - ds/k2);
	bq3 = (lam/12.0)*((1.0 - dc)/kk);
	bq = 12.0*eta*(bq1+bq2-bq3);
	//
	sq = 1.0/(aq*aq +bq*bq);

	return(sq);
}



//     SUBROUTINE SQWELL: CALCULATES THE STRUCTURE FACTOR FOR A
//                        DISPERSION OF MONODISPERSE HARD SPHERES
//     IN THE Mean Spherical APPROXIMATION ASSUMING THE SPHERES
//     INTERACT THROUGH A SQUARE WELL POTENTIAL.
//** not the best choice of closure ** see note below
//     REFS:  SHARMA,SHARMA, PHYSICA 89A,(1977),212
double
SquareWellStruct(double dp[], double q)
{
	double req,phis,edibkb,lambda,struc;
	double sigma,eta,eta2,eta3,eta4,etam1,etam14,alpha,beta,gamm;
	double x,sk,sk2,sk3,sk4,t1,t2,t3,t4,ck;

	x= q;

	req = dp[0];
	phis = dp[1];
	edibkb = dp[2];
	lambda = dp[3];

	sigma = req*2.;
	eta = phis;
	eta2 = eta*eta;
	eta3 = eta*eta2;
	eta4 = eta*eta3;
	etam1 = 1. - eta;
	etam14 = etam1*etam1*etam1*etam1;
	alpha = (  pow((1. + 2.*eta),2) + eta3*( eta-4.0 )  )/etam14;
	beta = -(eta/3.0) * ( 18. + 20.*eta - 12.*eta2 + eta4 )/etam14;
	gamm = 0.5*eta*( pow((1. + 2.*eta),2) + eta3*(eta-4.) )/etam14;
	//
	//  calculate the structure factor

	sk = x*sigma;
	sk2 = sk*sk;
	sk3 = sk*sk2;
	sk4 = sk3*sk;
	t1 = alpha * sk3 * ( sin(sk) - sk * cos(sk) );
	t2 = beta * sk2 * ( 2.*sk*sin(sk) - (sk2-2.)*cos(sk) - 2.0 );
	t3 =   ( 4.0*sk3 - 24.*sk ) * sin(sk);
	t3 = t3 - ( sk4 - 12.0*sk2 + 24.0 )*cos(sk) + 24.0;
	t3 = gamm*t3;
	t4 = -edibkb*sk3*(sin(lambda*sk) - lambda*sk*cos(lambda*sk)+ sk*cos(sk) - sin(sk) );
	ck =  -24.0*eta*( t1 + t2 + t3 + t4 )/sk3/sk3;
	struc  = 1./(1.-ck);

	return(struc);
}

// Hayter-Penfold (rescaled) MSA structure factor for screened Coulomb interactions
//
double
HayterPenfoldMSA(double dp[], double q)
{
	double Elcharge=1.602189e-19;		// electron charge in Coulombs (C)
	double kB=1.380662e-23;				// Boltzman constant in J/K
	double FrSpPerm=8.85418782E-12;	//Permittivity of free space in C^2/(N m^2)
	double SofQ, QQ, Qdiam, Vp, csalt, ss;
	double VolFrac, SIdiam, diam, Kappa, cs, IonSt;
	double dialec, Perm, Beta, Temp, zz, charge;
	double pi;
	int ierr;

	pi = 4.0*atan(1.);
	QQ= q;

	diam=dp[0];		//in dp[0] coming from python is radius : cahnged on Mar. 30, 2009
	zz = dp[1];		//# of charges
	VolFrac=dp[2];
	Temp=dp[3];		//in degrees Kelvin
	csalt=dp[4];		//in molarity
	dialec=dp[5];		// unitless
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//////////////////////////// convert to USEFUL inputs in SI units                                                //
						////////////////////////////    NOTE: easiest to do EVERYTHING in SI units                               //
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Beta=1.0/(kB*Temp);		// in Joules^-1
	Perm=dialec*FrSpPerm;	//in C^2/(N  m^2)
	charge=zz*Elcharge;		//in Coulomb (C)
	SIdiam = diam*1E-10;		//in m
	Vp=4.0*pi/3.0*(SIdiam/2.0)*(SIdiam/2.0)*(SIdiam/2.0);	//in m^3
	cs=csalt*6.022E23*1E3;	//# salt molecules/m^3

	//         Compute the derived values of :
	//			 Ionic strength IonSt (in C^2/m^3)
	// 			Kappa (Debye-Huckel screening length in m)
	//	and		gamma Exp(-k)
	IonSt=0.5 * Elcharge*Elcharge*(zz*VolFrac/Vp+2.0*cs);
	Kappa=sqrt(2*Beta*IonSt/Perm);     //Kappa calc from Ionic strength
									   //	Kappa=2/SIdiam					// Use to compare with HP paper
	gMSAWave[5]=Beta*charge*charge/(pi*Perm*SIdiam*pow((2.0+Kappa*SIdiam),2));

	//         Finally set up dimensionless parameters
	Qdiam=QQ*diam;
	gMSAWave[6] = Kappa*SIdiam;
	gMSAWave[4] = VolFrac;

	//Function sqhpa(qq)  {this is where Hayter-Penfold program began}

	//       FIRST CALCULATE COUPLING

	ss=pow(gMSAWave[4],(1.0/3.0));
	gMSAWave[9] = 2.0*ss*gMSAWave[5]*exp(gMSAWave[6]-gMSAWave[6]/ss);

	//        CALCULATE COEFFICIENTS, CHECK ALL IS WELL
	//        AND IF SO CALCULATE S(Q*SIG)

	ierr=0;
	ierr=sqcoef(ierr);
	if (ierr>=0) {
		SofQ=sqhcal(Qdiam);
	}else{
       	//SofQ=NaN;
		SofQ=-1.0;
		//	print "Error Level = ",ierr
		//      print "Please report HPMSA problem with above error code"
	}

	return(SofQ);
}



/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//
//
//      CALCULATES RESCALED VOLUME FRACTION AND CORRESPONDING
//      COEFFICIENTS FOR "SQHPA"
//
//      JOHN B. HAYTER   (I.L.L.)    14-SEP-81
//
//      ON EXIT:
//
//      SETA IS THE RESCALED VOLUME FRACTION
//      SGEK IS THE RESCALED CONTACT POTENTIAL
//      SAK IS THE RESCALED SCREENING CONSTANT
//      A,B,C,F,U,V ARE THE MSA COEFFICIENTS
//      G1= G(1+) IS THE CONTACT VALUE OF G(R/SIG):
//      FOR THE GILLAN CONDITION, THE DIFFERENCE FROM
//      ZERO INDICATES THE COMPUTATIONAL ACCURACY.
//
//      IR > 0:    NORMAL EXIT,  IR IS THE NUMBER OF ITERATIONS.
//         < 0:    FAILED TO CONVERGE
//
int
sqcoef(int ir)
{
	int itm=40,ix,ig,ii;
	double acc=5.0E-6,del,e1,e2,f1,f2;

	//      WAVE gMSAWave = $"root:HayPenMSA:gMSAWave"
	f1=0;		//these were never properly initialized...
	f2=0;

	ig=1;
	if (gMSAWave[6]>=(1.0+8.0*gMSAWave[4])) {
		ig=0;
		gMSAWave[15]=gMSAWave[14];
		gMSAWave[16]=gMSAWave[4];
		ix=1;
		ir = sqfun(ix,ir);
		gMSAWave[14]=gMSAWave[15];
		gMSAWave[4]=gMSAWave[16];
		if((ir<0.0) || (gMSAWave[14]>=0.0)) {
			return ir;
		}
	}
	gMSAWave[10]=fmin(gMSAWave[4],0.20);
	if ((ig!=1) || ( gMSAWave[9]>=0.15)) {
		ii=0;
		do {
			ii=ii+1;
			if(ii>itm) {
				ir=-1;
				return ir;
			}
			if (gMSAWave[10]<=0.0) {
			    gMSAWave[10]=gMSAWave[4]/ii;
			}
			if(gMSAWave[10]>0.6) {
			    gMSAWave[10] = 0.35/ii;
			}
			e1=gMSAWave[10];
			gMSAWave[15]=f1;
			gMSAWave[16]=e1;
			ix=2;
			ir = sqfun(ix,ir);
			f1=gMSAWave[15];
			e1=gMSAWave[16];
			e2=gMSAWave[10]*1.01;
			gMSAWave[15]=f2;
			gMSAWave[16]=e2;
			ix=2;
			ir = sqfun(ix,ir);
			f2=gMSAWave[15];
			e2=gMSAWave[16];
			e2=e1-(e2-e1)*f1/(f2-f1);
			gMSAWave[10] = e2;
			del = fabs((e2-e1)/e1);
		} while (del>acc);
		gMSAWave[15]=gMSAWave[14];
		gMSAWave[16]=e2;
		ix=4;
		ir = sqfun(ix,ir);
		gMSAWave[14]=gMSAWave[15];
		e2=gMSAWave[16];
		ir=ii;
		if ((ig!=1) || (gMSAWave[10]>=gMSAWave[4])) {
		    return ir;
		}
	}
	gMSAWave[15]=gMSAWave[14];
	gMSAWave[16]=gMSAWave[4];
	ix=3;
	ir = sqfun(ix,ir);
	gMSAWave[14]=gMSAWave[15];
	gMSAWave[4]=gMSAWave[16];
	if ((ir>=0) && (gMSAWave[14]<0.0)) {
		ir=-3;
	}
	return ir;
}


int
sqfun(int ix, int ir)
{
	double acc=1.0e-6;
	double reta,eta2,eta21,eta22,eta3,eta32,eta2d,eta2d2,eta3d,eta6d,e12,e24,rgek;
	double rak,ak1,ak2,dak,dak2,dak4,d,d2,dd2,dd4,dd45,ex1,ex2,sk,ck,ckma,skma;
	double al1,al2,al3,al4,al5,al6,be1,be2,be3,vu1,vu2,vu3,vu4,vu5,ph1,ph2,ta1,ta2,ta3,ta4,ta5;
	double a1,a2,a3,b1,b2,b3,v1,v2,v3,p1,p2,p3,pp,pp1,pp2,p1p2,t1,t2,t3,um1,um2,um3,um4,um5,um6;
	double w0,w1,w2,w3,w4,w12,w13,w14,w15,w16,w24,w25,w26,w32,w34,w3425,w35,w3526,w36,w46,w56;
	double fa,fap,ca,e24g,pwk,qpw,pg,del,fun,fund,g24;
	int ii,ibig,itm=40;
	//      WAVE gMSAWave = $"root:HayPenMSA:gMSAWave"
	a2=0;
	a3=0;
	b2=0;
	b3=0;
	v2=0;
	v3=0;
	p2=0;
	p3=0;

	//     CALCULATE CONSTANTS; NOTATION IS HAYTER PENFOLD (1981)

	reta = gMSAWave[16];
	eta2 = reta*reta;
	eta3 = eta2*reta;
	e12 = 12.0*reta;
	e24 = e12+e12;
	gMSAWave[13] = pow( (gMSAWave[4]/gMSAWave[16]),(1.0/3.0));
	gMSAWave[12]=gMSAWave[6]/gMSAWave[13];
	ibig=0;
	if (( gMSAWave[12]>15.0) && (ix==1)) {
		ibig=1;
	}

	gMSAWave[11] = gMSAWave[5]*gMSAWave[13]*exp(gMSAWave[6]- gMSAWave[12]);
	rgek =  gMSAWave[11];
	rak =  gMSAWave[12];
	ak2 = rak*rak;
	ak1 = 1.0+rak;
	dak2 = 1.0/ak2;
	dak4 = dak2*dak2;
	d = 1.0-reta;
	d2 = d*d;
	dak = d/rak;
	dd2 = 1.0/d2;
	dd4 = dd2*dd2;
	dd45 = dd4*2.0e-1;
	eta3d=3.0*reta;
	eta6d = eta3d+eta3d;
	eta32 = eta3+ eta3;
	eta2d = reta+2.0;
	eta2d2 = eta2d*eta2d;
	eta21 = 2.0*reta+1.0;
	eta22 = eta21*eta21;

	//     ALPHA(I)

	al1 = -eta21*dak;
	al2 = (14.0*eta2-4.0*reta-1.0)*dak2;
	al3 = 36.0*eta2*dak4;

	//      BETA(I)

	be1 = -(eta2+7.0*reta+1.0)*dak;
	be2 = 9.0*reta*(eta2+4.0*reta-2.0)*dak2;
	be3 = 12.0*reta*(2.0*eta2+8.0*reta-1.0)*dak4;

	//      NU(I)

	vu1 = -(eta3+3.0*eta2+45.0*reta+5.0)*dak;
	vu2 = (eta32+3.0*eta2+42.0*reta-2.0e1)*dak2;
	vu3 = (eta32+3.0e1*reta-5.0)*dak4;
	vu4 = vu1+e24*rak*vu3;
	vu5 = eta6d*(vu2+4.0*vu3);

	//      PHI(I)

	ph1 = eta6d/rak;
	ph2 = d-e12*dak2;

	//      TAU(I)

	ta1 = (reta+5.0)/(5.0*rak);
	ta2 = eta2d*dak2;
	ta3 = -e12*rgek*(ta1+ta2);
	ta4 = eta3d*ak2*(ta1*ta1-ta2*ta2);
	ta5 = eta3d*(reta+8.0)*1.0e-1-2.0*eta22*dak2;

	//     double PRECISION SINH(K), COSH(K)

	ex1 = exp(rak);
	ex2 = 0.0;
	if ( gMSAWave[12]<20.0) {
		ex2=exp(-rak);
	}
	sk=0.5*(ex1-ex2);
	ck = 0.5*(ex1+ex2);
	ckma = ck-1.0-rak*sk;
	skma = sk-rak*ck;

	//      a(I)

	a1 = (e24*rgek*(al1+al2+ak1*al3)-eta22)*dd4;
	if (ibig==0) {
		a2 = e24*(al3*skma+al2*sk-al1*ck)*dd4;
		a3 = e24*(eta22*dak2-0.5*d2+al3*ckma-al1*sk+al2*ck)*dd4;
	}

	//      b(I)

	b1 = (1.5*reta*eta2d2-e12*rgek*(be1+be2+ak1*be3))*dd4;
	if (ibig==0) {
		b2 = e12*(-be3*skma-be2*sk+be1*ck)*dd4;
		b3 = e12*(0.5*d2*eta2d-eta3d*eta2d2*dak2-be3*ckma+be1*sk-be2*ck)*dd4;
	}

	//      V(I)

	v1 = (eta21*(eta2-2.0*reta+1.0e1)*2.5e-1-rgek*(vu4+vu5))*dd45;
	if (ibig==0) {
		v2 = (vu4*ck-vu5*sk)*dd45;
		v3 = ((eta3-6.0*eta2+5.0)*d-eta6d*(2.0*eta3-3.0*eta2+18.0*reta+1.0e1)*dak2+e24*vu3+vu4*sk-vu5*ck)*dd45;
	}


	//       P(I)

	pp1 = ph1*ph1;
	pp2 = ph2*ph2;
	pp = pp1+pp2;
	p1p2 = ph1*ph2*2.0;
	p1 = (rgek*(pp1+pp2-p1p2)-0.5*eta2d)*dd2;
	if (ibig==0) {
		p2 = (pp*sk+p1p2*ck)*dd2;
		p3 = (pp*ck+p1p2*sk+pp1-pp2)*dd2;
	}

	//       T(I)

	t1 = ta3+ta4*a1+ta5*b1;
	if (ibig!=0) {

		//		VERY LARGE SCREENING:  ASYMPTOTIC SOLUTION

  		v3 = ((eta3-6.0*eta2+5.0)*d-eta6d*(2.0*eta3-3.0*eta2+18.0*reta+1.0e1)*dak2+e24*vu3)*dd45;
		t3 = ta4*a3+ta5*b3+e12*ta2 - 4.0e-1*reta*(reta+1.0e1)-1.0;
		p3 = (pp1-pp2)*dd2;
		b3 = e12*(0.5*d2*eta2d-eta3d*eta2d2*dak2+be3)*dd4;
		a3 = e24*(eta22*dak2-0.5*d2-al3)*dd4;
		um6 = t3*a3-e12*v3*v3;
		um5 = t1*a3+a1*t3-e24*v1*v3;
		um4 = t1*a1-e12*v1*v1;
		al6 = e12*p3*p3;
		al5 = e24*p1*p3-b3-b3-ak2;
		al4 = e12*p1*p1-b1-b1;
		w56 = um5*al6-al5*um6;
		w46 = um4*al6-al4*um6;
		fa = -w46/w56;
		ca = -fa;
		gMSAWave[3] = fa;
		gMSAWave[2] = ca;
		gMSAWave[1] = b1+b3*fa;
		gMSAWave[0] = a1+a3*fa;
		gMSAWave[8] = v1+v3*fa;
		gMSAWave[14] = -(p1+p3*fa);
		gMSAWave[15] = gMSAWave[14];
		if (fabs(gMSAWave[15])<1.0e-3) {
			gMSAWave[15] = 0.0;
		}
		gMSAWave[10] = gMSAWave[16];

	} else {

		t2 = ta4*a2+ta5*b2+e12*(ta1*ck-ta2*sk);
		t3 = ta4*a3+ta5*b3+e12*(ta1*sk-ta2*(ck-1.0))-4.0e-1*reta*(reta+1.0e1)-1.0;

		//		MU(i)

		um1 = t2*a2-e12*v2*v2;
		um2 = t1*a2+t2*a1-e24*v1*v2;
		um3 = t2*a3+t3*a2-e24*v2*v3;
		um4 = t1*a1-e12*v1*v1;
		um5 = t1*a3+t3*a1-e24*v1*v3;
		um6 = t3*a3-e12*v3*v3;

		//			GILLAN CONDITION ?
		//
		//			YES - G(X=1+) = 0
		//
		//			COEFFICIENTS AND FUNCTION VALUE
		//
		if ((ix==1) || (ix==3)) {

			//			NO - CALCULATE REMAINING COEFFICIENTS.

			//			LAMBDA(I)

			al1 = e12*p2*p2;
			al2 = e24*p1*p2-b2-b2;
			al3 = e24*p2*p3;
			al4 = e12*p1*p1-b1-b1;
			al5 = e24*p1*p3-b3-b3-ak2;
			al6 = e12*p3*p3;

			//			OMEGA(I)

			w16 = um1*al6-al1*um6;
			w15 = um1*al5-al1*um5;
			w14 = um1*al4-al1*um4;
			w13 = um1*al3-al1*um3;
			w12 = um1*al2-al1*um2;

			w26 = um2*al6-al2*um6;
			w25 = um2*al5-al2*um5;
			w24 = um2*al4-al2*um4;

			w36 = um3*al6-al3*um6;
			w35 = um3*al5-al3*um5;
			w34 = um3*al4-al3*um4;
			w32 = um3*al2-al3*um2;
			//
			w46 = um4*al6-al4*um6;
			w56 = um5*al6-al5*um6;
			w3526 = w35+w26;
			w3425 = w34+w25;

			//			QUARTIC COEFFICIENTS

			w4 = w16*w16-w13*w36;
			w3 = 2.0*w16*w15-w13*w3526-w12*w36;
			w2 = w15*w15+2.0*w16*w14-w13*w3425-w12*w3526;
			w1 = 2.0*w15*w14-w13*w24-w12*w3425;
			w0 = w14*w14-w12*w24;

			//			ESTIMATE THE STARTING VALUE OF f

			if (ix==1) {
				//				LARGE K
				fap = (w14-w34-w46)/(w12-w15+w35-w26+w56-w32);
			} else {
				//				ASSUME NOT TOO FAR FROM GILLAN CONDITION.
				//				IF BOTH RGEK AND RAK ARE SMALL, USE P-W ESTIMATE.
				gMSAWave[14]=0.5*eta2d*dd2*exp(-rgek);
				if (( gMSAWave[11]<=2.0) && ( gMSAWave[11]>=0.0) && ( gMSAWave[12]<=1.0)) {
					e24g = e24*rgek*exp(rak);
					pwk = sqrt(e24g);
					qpw = (1.0-sqrt(1.0+2.0*d2*d*pwk/eta22))*eta21/d;
					gMSAWave[14] = -qpw*qpw/e24+0.5*eta2d*dd2;
				}
  				pg = p1+gMSAWave[14];
				ca = ak2*pg+2.0*(b3*pg-b1*p3)+e12*gMSAWave[14]*gMSAWave[14]*p3;
				ca = -ca/(ak2*p2+2.0*(b3*p2-b2*p3));
				fap = -(pg+p2*ca)/p3;
			}

			//			AND REFINE IT ACCORDING TO NEWTON
			ii=0;
			do {
				ii = ii+1;
				if (ii>itm) {
					//					FAILED TO CONVERGE IN ITM ITERATIONS
					ir=-2;
					return (ir);
				}
				fa = fap;
				fun = w0+(w1+(w2+(w3+w4*fa)*fa)*fa)*fa;
				fund = w1+(2.0*w2+(3.0*w3+4.0*w4*fa)*fa)*fa;
				fap = fa-fun/fund;
				del=fabs((fap-fa)/fa);
			} while (del>acc);

			ir = ir+ii;
			fa = fap;
			ca = -(w16*fa*fa+w15*fa+w14)/(w13*fa+w12);
			gMSAWave[14] = -(p1+p2*ca+p3*fa);
			gMSAWave[15] = gMSAWave[14];
			if (fabs(gMSAWave[15])<1.0e-3) {
				gMSAWave[15] = 0.0;
			}
			gMSAWave[10] = gMSAWave[16];
		} else {
			ca = ak2*p1+2.0*(b3*p1-b1*p3);
			ca = -ca/(ak2*p2+2.0*(b3*p2-b2*p3));
			fa = -(p1+p2*ca)/p3;
			if (ix==2) {
				gMSAWave[15] = um1*ca*ca+(um2+um3*fa)*ca+um4+um5*fa+um6*fa*fa;
			}
			if (ix==4) {
				gMSAWave[15] = -(p1+p2*ca+p3*fa);
			}
		}
   		gMSAWave[3] = fa;
		gMSAWave[2] = ca;
		gMSAWave[1] = b1+b2*ca+b3*fa;
		gMSAWave[0] = a1+a2*ca+a3*fa;
		gMSAWave[8] = (v1+v2*ca+v3*fa)/gMSAWave[0];
	}
   	g24 = e24*rgek*ex1;
	gMSAWave[7] = (rak*ak2*ca-g24)/(ak2*g24);
	return (ir);
}

// called as DiamCyl(hcyl,rcyl)
//modified from Igor NIST package XOP
double
DiamCyl(double hcyl, double rcyl)
{
	double diam,a,b,t1,t2,ddd;
	double pi;

	pi = 4.0*atan(1.0);
	if (rcyl == 0 || hcyl == 0) {
		return 0.0;
	}
	a = rcyl;
	b = hcyl/2.0;
	t1 = a*a*2.0*b/2.0;
	t2 = 1.0 + (b/a)*(1.0+a/b/2)*(1.0+pi*a/b/2.0);
	ddd = 3.0*t1*t2;
	diam = pow(ddd,(1.0/3.0));

	return(diam);
}

//prolate OR oblate ellipsoids
//aa is the axis of rotation
//if aa>bb, then PROLATE
//if aa<bb, then OBLATE
// A. Isihara, J. Chem. Phys. 18, 1446 (1950)
//returns DIAMETER
// called as DiamEllip(aa,bb)

//modified from Igor NIST package XOP
double
DiamEllip(double aa, double bb)
{
	double ee,e1,bd,b1,bL,b2,del,ddd,diam;

	if (aa == 0 || bb == 0) {
		return 0.0;
	}
	if (aa == bb) {
		return 2*aa;
	}
	if(aa>bb) {
		ee = (aa*aa - bb*bb)/(aa*aa);
	}else{
		ee = (bb*bb - aa*aa)/(bb*bb);
	}

	bd = 1.0-ee;
	e1 = sqrt(ee);
	b1 = 1.0 + asin(e1)/(e1*sqrt(bd));
	bL = (1.0+e1)/(1.0-e1);
	b2 = 1.0 + bd/2/e1*log(bL);
	del = 0.75*b1*b2;

	ddd = 2.0*(del+1.0)*aa*bb*bb;		//volume is always calculated correctly
	diam = pow(ddd,(1.0/3.0));

	return(diam);
}

double
sqhcal(double qq)
{
    double SofQ,etaz,akz,gekz,e24,x1,x2,ck,sk,ak2,qk,q2k,qk2,qk3,qqk,sink,cosk,asink,qcosk,aqk,inter;
	//	WAVE gMSAWave = $"root:HayPenMSA:gMSAWave"

	etaz = gMSAWave[10];
	akz =  gMSAWave[12];
	gekz =  gMSAWave[11];
	e24 = 24.0*etaz;
	x1 = exp(akz);
	x2 = 0.0;
	if ( gMSAWave[12]<20.0) {
		x2 = exp(-akz);
	}
	ck = 0.5*(x1+x2);
	sk = 0.5*(x1-x2);
	ak2 = akz*akz;

	if (qq<=0.0) {
		SofQ = -1.0/gMSAWave[0];
	} else {
		qk = qq/gMSAWave[13];
		q2k = qk*qk;
		qk2 = 1.0/q2k;
		qk3 = qk2/qk;
		qqk = 1.0/(qk*(q2k+ak2));
		sink = sin(qk);
		cosk = cos(qk);
		asink = akz*sink;
		qcosk = qk*cosk;
		aqk = gMSAWave[0]*(sink-qcosk);
		aqk=aqk+gMSAWave[1]*((2.0*qk2-1.0)*qcosk+2.0*sink-2.0/qk);
		inter=24.0*qk3+4.0*(1.0-6.0*qk2)*sink;
		aqk=(aqk+0.5*etaz*gMSAWave[0]*(inter-(1.0-12.0*qk2+24.0*qk2*qk2)*qcosk))*qk3;
		aqk=aqk +gMSAWave[2]*(ck*asink-sk*qcosk)*qqk;
		aqk=aqk +gMSAWave[3]*(sk*asink-qk*(ck*cosk-1.0))*qqk;
		aqk=aqk +gMSAWave[3]*(cosk-1.0)*qk2;
		aqk=aqk -gekz*(asink+qcosk)*qqk;
		SofQ = 1.0/(1.0-e24*aqk);
	}
	return (SofQ);
}

///////////end of XOP


