#include <iostream>
#include "head.h"
#include <functional>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include "H5Cpp.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}


int main(int argc,char** argv) {
	
	std::ofstream file;
	std::ofstream file_config;
        std::string slabel;
        std::string name1="All_";
	double Temp;
	if(argc==3){
		slabel=argv[1];
		name1=name1+slabel+".txt";
		file.open(name1.c_str());
		Temp=atof(argv[2]);
	}
	else{
		printf("please enter label");
		std::cin>>slabel>>Temp;
		name1=name1+slabel+".txt";
		file.open(name1.c_str());
	}

	file_config.open("configure.txt");

	H5::H5File file1;
	H5::H5File file_data;
	H5::DataSet dataset;


	int i,j,k,l;
/*	int block_counter=0;
	int block_n;
	int block_L;
	int block_s=20;*/
	int NN=1e5; //MC total steps
	double sum=0;
	double q=0;
	double delta_q;
	double delta_f;
	int grid_size1=4;
	int grid_size2=12;
        double w;
	double val;
	double g=2.1;


	double fc=15.0;
	double qf=1.0;
	double qc=10.0;
	file_config<<fc<<"\n"<<qf<<"\n"<<qc<<"\n"<<g<<"\n"<<Temp<<"\n";
//create grid_f_dif and grid_q_dif
	std::vector<double> grid_f;
	std::vector<double> grid_dq;

if(is_file_exist("pi.h5")){
	printf("read old data");
	//read frequency-difference gridf
        file_data.openFile("pi.h5",H5F_ACC_RDWR);
        hsize_t dims_out[1];
        dataset=file_data.openDataSet("/pi/w");
        dataset.getSpace().getSimpleExtentDims(dims_out,NULL);
        for(i=0;i<dims_out[0];i++){
		grid_f.push_back(0);
//		if(i!=0) printf("%f\n",round((grid_f[i]-grid_f[i-1]/2/M_PI/Temp)));
	}
        dataset.read(&(grid_f[0]),H5::PredType::IEEE_F64LE);


//read momentum_dif grid_dq     
        dataset=file_data.openDataSet("/pi/q");
        dataset.getSpace().getSimpleExtentDims(dims_out,NULL);
        for(i=0;i<dims_out[0];i++){
		grid_dq.push_back(0);
	}
        dataset.read(&(grid_dq[0]),H5::PredType::IEEE_F64LE);
	file_data.close();
}
else{
	i=0;
	w=0;
	
	int N_highf1=50;
	int N_highf2=30;
	double f_init=2.0;
	double f_middle=5.0;
	double step_f=1;

	while(w<2*fc){ //0->wf
		grid_f.push_back(w);
		w=w+2*M_PI*Temp*step_f;
		if(w<f_init) {
			i++;
			step_f=pow(2,i/grid_size2);
			
		}
		else if(w<f_middle) step_f=floor((f_middle-100*2*M_PI*Temp)/2/M_PI/Temp/N_highf1);
		else if(w<2*fc) step_f=floor((2*fc-f_middle)/2/M_PI/Temp/N_highf2);	
	}
	grid_f.push_back(w);

	int grid_size_dq=5;
	i=0;
	w=1e-14;
	double step_dq=w;
	while(w<2*qc){ 
		grid_dq.push_back(w);
	//	w=w+1e-6;
		w=w+step_dq;
		if(i%grid_size_dq==0) step_dq=step_dq*2;
		if(step_dq>1.0) step_dq=1.0;
		i++;
	}
	printf("lastq=%f\n",w);
	grid_dq.push_back(w);
}

for(i=0;i<grid_f.size();i++){
              if(i!=0) printf("%f\n",round((grid_f[i]-grid_f[i-1])/2/M_PI/Temp));
}

for(i=0;i<grid_dq.size();i++){
              if(i!=0) printf("%f\n",(grid_dq[i]-grid_dq[i-1]));
}




	printf("size_dq=%d size_f=%d\n",int(grid_dq.size()),int(grid_f.size()));

//	std::vector<double> Z0;
	DressedVortex gamma(Temp,grid_dq,grid_f);
	MC markov(Temp);	
//	block_L=NN/block_s;
//	for(i=0;i<gamma.block_size*gamma.size_f;i++){
//		Z0.push_back(0);
//	}
	for(l=0;l<gamma.Grid_f.size();l++){
		for(j=0;j<gamma.Grid_q.size();j++){
			markov.asign_q_f(gamma.Grid_q[j],gamma.Grid_f[l]);		
			for(i=0;i<NN;i++){
				if(markov.diagram_n==1){
					markov.Update10();
				}
				else if(markov.diagram_n==0){
					markov.Update01();
				}
		/*		if((i+1)%block_L==0){ //block method->MC error
					block_n=(i+1)/block_L-1;
					
					for(j=0;j<gamma.size_q;j++){
						gamma.block[block_n*gamma.size_q*gamma.size_f+j*gamma.size_f+l]=gamma.vort[j*gamma.size_f+l]*gamma.qc/delta_q/2.0/M_PI/M_PI;
					}
					Z0[block_n*gamma.size_f+l]=gamma.Z0[l];
				}*/
			}
			q=gamma.Grid_q[j];
			val=markov.vort/markov.Z0;
		//	val=4*M_PI*g*gamma.Grid_q[j]/(gamma.Grid_q[j]*gamma.Grid_q[j]+4*M_PI*g*val);
			file<<markov.vort<<"\t"<<markov.Z0<<"\t"<<gamma.Grid_q[j]<<"\t"<<gamma.Grid_f[l]<<"\t"<<val<<"\n";//<<"\t"<<markov.vort/markov.Z0/(q*q*q*q+q*q*markov.vort/markov.Z0)<<"\n";
			gamma.vort.push_back(val);//markov.vort/markov.Z0);
		}	
	}


if(is_file_exist("pi.h5")){
	if( remove( "pi.h5" ) != 0 )
   	 perror( "Error deleting file" );
 	 else
    	puts( "File successfully deleted" ); 	  
}

	file1=H5::H5File("pi.h5",H5F_ACC_TRUNC);
	H5::Group g2(file1.createGroup("/pi"));
 	hsize_t dims[1];
    //store freq grid


    dims[0]=gamma.Grid_f.size();
    H5::DataSpace dataspace=H5::DataSpace(1,dims);
    dataset=H5::DataSet(file1.createDataSet("/pi/w",
					   H5::PredType::IEEE_F64LE,dataspace));
    dataset.write(&(gamma.Grid_f[0]),H5::PredType::IEEE_F64LE);
    dataspace.close();
    dataset.close();
    //store momentum grid
    dims[0]=gamma.Grid_q.size();
    dataspace=H5::DataSpace(1,dims);
    dataset=H5::DataSet(file1.createDataSet("/pi/q",
					   H5::PredType::IEEE_F64LE,dataspace));
    dataset.write(&(gamma.Grid_q[0]),H5::PredType::IEEE_F64LE);
    dataspace.close();
    dataset.close();

    //store val grid
    dims[0]=gamma.vort.size();
    dataspace=H5::DataSpace(1,dims);
    dataset=H5::DataSet(file1.createDataSet("/pi/pi",
					   H5::PredType::IEEE_F64LE,dataspace));
    dataset.write(&(gamma.vort[0]),H5::PredType::IEEE_F64LE);
    dataspace.close();
    dataset.close();



    file.close();	
    file_config.close();
}
