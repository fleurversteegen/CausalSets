# include <iostream>
# include <cmath>
# include <math.h>
# include "spacetime.h"

using namespace std;


//Construct a spacetime with a metric and length L in each dimension d, and a sprinkling density rho
  
Spacetime :: Spacetime(int _L, float _rho, int *_metric, int _d) : rho(_rho), L_min (1), L(_L), d(_d)
{
    N = (L-L_min);                              //N = (L-L_min)/2L_min --> rescaled by 2L_min to loop over integers
    metric = new int[d];
    
    for (int i =0; i < d; i++)
    {
        metric[i] = _metric[i];                 //
        
    }
    
    Prob();
  
} 

//calculates the probability for 1 element to be in a unit volume

float Spacetime :: Prob()
{
    prob =  rho * pow(L_min , d) * exp(- rho *  pow(L_min , d) );
   
    return prob;
}




//Acquire the metric distance on the spacetime
//between two points located at _pos1 and _pos2
//g is the metric
double Spacetime :: MetDist(double * _pos1, double * _pos2)
{
    double ds_sq = 0;
    for (int i =0; i<d; i++)
        {
            ds_sq +=  ((*(_pos1 + i) - *(_pos2 + i)) * (*(_pos1 + i)- *(_pos2 + i))) * metric[i];     //take the product ds^2 = dx*dx*g
        }
    return ds_sq;
}



