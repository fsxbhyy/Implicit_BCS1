#include "head.h"
#include <functional>
#include <stdio.h>
#include <math.h>
#include <iostream>
/*double Weight(double p, double coscta,double q,double Temp){
	double WW=0;
	WW=exp(p*p/Temp)/(exp((p*p+q*q/4+p*q*coscta-1)/Temp)+1);
	return WW;
}*/
	
void MC::Update01(){
	double dum_p;
//	double r,phi;
	double R=0;	
//	r=sqrt(-2.0*log(1-RNG()));
//	phi=M_PI*(RNG()-0.5);
//	dum_p=fabs(r*cos(phi));
	dum_p=-log(1-RNG());
	R=Weight(dum_p,q,f,Temp);
	//	printf("%f\n",R);
	if(R>1||RNG()<R){
		p=dum_p;
//		gamma.Z1++;
		vort+=1.0;
		diagram_n=1;
	}
	else {
		Z0++;
	}	
}
