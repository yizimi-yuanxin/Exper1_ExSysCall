#include <soft.h>

/*
	exp returns the exponential function of its
	floating-point argument.

	The coefficients are #1069 from Hart and Cheney. (22.35D)
*/

static double	exp_p0	= .2080384346694663001443843411e7;
static double	exp_p1	= .3028697169744036299076048876e5;
static double	exp_p2	= .6061485330061080841615584556e2;
static double	exp_q0	= .6002720360238832528230907598e7;
static double	exp_q1	= .3277251518082914423057964422e6;
static double	exp_q2	= .1749287689093076403844945335e4;
static double	log2e	= 1.4426950408889634073599247;
static double	sqrt2	= 1.4142135623730950488016887;
static double	maxf	= 10000;

double exp(double arg)
{
	double fract;
	double temexp_p1, temexp_p2, xsq;
	int ent;

	if(arg == 0.)
		return(1.);
	if(arg < -maxf)
		return(0.);
	if(arg > maxf) {
		return(HUGE_VAL);
	}
	arg *= log2e;
	ent = floor(arg);
	fract = (arg-ent) - 0.5;
	xsq = fract*fract;
	temexp_p1 = ((exp_p2*xsq+exp_p1)*xsq+exp_p0)*fract;
	temexp_p2 = ((1.0*xsq+exp_q2)*xsq+exp_q1)*xsq + exp_q0;
	return(ldexp(sqrt2*(temexp_p2+temexp_p1)/(temexp_p2-temexp_p1), ent));
}
