#ifndef SPACETIME_H
#define SPACETIME_H


using namespace std;

class Spacetime
{

private:
    
    int *metric;           //holds the metric g 

public:

    int L_min, L, N, d; //min length, size of spacetime, points along one dimension, dimension
    float rho;         //sprinkling density
    float prob;        //sprinkling prob
    
    
    
    
    Spacetime(int, float, int *, int);   //Contruct spacetime by passing the size L, the sprinkling density rho, the metric g and the dimension d
 
    double MetDist(double *, double *);    //Metric distance given spacetime coord
    
    float Prob();                    //probability used for sprinkling
    
  
    
  
};    
#endif
