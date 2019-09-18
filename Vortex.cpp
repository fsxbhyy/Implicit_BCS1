#include "head.h"
#include <functional>
#include <stdio.h>
#include <math.h>
#include <iostream>

DressedVortex::DressedVortex(const double& T,std::vector<double> qq,std::vector<double> ff):Temp(T){	
	this->Grid_q.swap(qq);
	this->Grid_f.swap(ff);
	
//	this->size_f=size2;
/*	for(l=0;l<size1;l++){
		w=l*q_c/size1;
		this->qq.push_back(w);
	}*/
	
	
/*	w=0.000000001;
	for(i=0;i<grid_num;i++){ //0->kf
		for(j=0;j<grid_size/pow(2.0,i);j++){
			this->Grid_q.push_back(w);
			w=w+delta_q*pow(2.0,i);
			size1++;
		}
	}
	for(i=i-1;i>-1;i--){ //kf->2kf
                for(j=0;j<grid_size/pow(2.0,i);j++){
                        this->Grid_q.push_back(w);
                        w=w+delta_q*pow(2.0,i);
                	size1++;
		}
        }
	for(i=0;i<grid_num;i++){ //2kf->3kf
                for(j=0;j<grid_size/pow(2.0,i);j++){
                        this->Grid_q.push_back(w);
                        w=w+delta_q*pow(2.0,i);
                	size1++;
		}
        }
	delta_q=delta_q*pow(2.0,i);
	w=w+delta_q;
	while(w<qc){//3kf->kc
		this->Grid_q.push_back(w);
		w=w+delta_q;
		size1++;
	}
	this->size_q=size1;*/
/*	double step_q=2*qf/2.0/grid_size1/3.0;
        i=0;
        w=1e-6;
        while(w<2*qf){ //0->qf
                Grid_q.push_back(w);
                w=w+step_q*pow(2.0,i/grid_size1);
                if(w>qf) i--;
                else i++;
        }
        while(w<2*qc){ //qf->qc
                Grid_q.push_back(w);
                w=w+step_q*pow(2.0,i/grid_size1);
                i++;
        }



	i=0;
        w=0;
        while(w<3*fc){ //0->wf
                Grid_f.push_back(w);
                w=w+2*M_PI*Temp*pow(2.0,i/grid_size2);
                i++;
        }*/

	/*	for(i=i-1;i>-1;i--){ //kf->2kf
                for(j=0;j<grid_size/pow(2.0,i);j++){
                        this->qq.push_back(w);
                        w=w+delta_q*pow(2.0,i);
                	size1++;
		}
        }*/

/*	for(l=0;l<size2;l++){
		w=2*Temp*M_PI*(l-size2/2.0+0.5);
		this->ff.push_back(w);
	}*/

}

