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
	
void MC::Update10(){
//	double delta_q=gamma.qc/gamma.size_q;
//        double delta_f=2*gamma.fc/gamma.size_f;
	double R=0;	
	R=1.0/Weight(p,q,f,Temp);
//		printf("%f\n",R);
	if(R>1||RNG()<R){
                Z0++;
                diagram_n=0;
        }
	else {
                vort+=1.0;
        }	
}
