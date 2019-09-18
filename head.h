#ifndef CIRCLE_H
#define CIRCLE_H
#include <vector>
#define M_PI 3.1415926535897932384

class DressedVortex{
	public:
	        double Temp;	
		std::vector<double> Grid_q;     // momentum vriable
		std::vector<double> Grid_f;	//frequency vriable
		std::vector<double> vort;
		DressedVortex(const double& t,std::vector<double> Grid_q,std::vector<double> Grid_f);
};

class MC{
	private:
		double p;     // momentum integral
		double coscta; 
		double q;
		double f;
		double Temp;
	//	int block_size;
	//	std::vector<double> block;
		
	public:
		int diagram_n;
		double vort;
		int Z0;
		MC(const double& t);
		void Update01();
		void Update10();
		void asign_q_f(const double& a,const double& b){q=a;f=b;Z0=0;vort=0;}
};


double Weight(const double&,const double&,const double&,const double&);

double RNG();
#endif
