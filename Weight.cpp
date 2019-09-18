#include "head.h"
#include <functional>
#include <stdio.h>
#include <math.h>
#include <iostream>

double Weight(const double &p,const double &q,const double &w,const double &Temp){
	double WW=0;
	WW=exp(p)*p/q*log((w*w+(2*p+q)*(2*p+q)*q*q)/(w*w+(2*p-q)*(2*p-q)*q*q))/(exp((p*p-1)/Temp)+1)/4/M_PI/M_PI;
//	WW=Temp;
	return WW;
}
	
