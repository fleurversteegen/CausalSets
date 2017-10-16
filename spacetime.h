#ifndef SPACETIME_H
#define SPACETIME_H


using namespace std;

class Spacetime
{

private:
    
    int *metric;           //holds the metric g 

public:

    int rho_pl, L_pl, L, N,d; //planck density, planck length, size of spacetime, points along one dimension, dimension, sprinklink prob
    float prob;
    
    
    
    
    Spacetime(int, int *, int);   //Contruct spacetime by passing the size L and the metric g
 
    double MetDist(double *, double *);    //Metric distance given spacetime coord
    
    float Prob();                    //probability used for sprinkling
    
  
    
  
};    
#endif
