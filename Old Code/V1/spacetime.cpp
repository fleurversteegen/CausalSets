# include <iostream>
# include <cmath>
# include <math.h>
# include "spacetime.h"

using namespace std;


//Construct a spacetime with a metric and length L in each dimension d
  
Spacetime :: Spacetime(int _L, float _rho, int *_metric, int _d) : rho(_rho), L_min (1), L(_L), d(_d)
{
    N = (L-L_min);                  //physically N = (L-L_min)/2L_min --> rescaled by 2L_min 
    metric = new int[d];
    
    for (int i =0; i < d; i++)
    {
        metric[i] = _metric[i];
        
    }
    
    Prob();
    //Sprinkle();
} 

//calculates the probability for 1 element to be in a planck volume

float Spacetime :: Prob()
{
    prob =  rho * pow(L_min , d) * exp(- rho *  pow(L_min , d) );
   
    return prob;
}




//Acquire the metric distance on the spacetime
//between two points located at _pos1 and _pos2
//metric defines g
double Spacetime :: MetDist(double * _pos1, double * _pos2)
{
  /*  int *_dist = new int[d];
    for(int j =0; j < d; j++)                           //calculate (dt, dx, dy, dz)
    {
    
        _dist[j] = *(_pos1 + j) - *(_pos2 + j);
    }
     
     
    double ds_sq = ( _dist[0] * _dist[0]) * metric[0] ;        //take the inner product gdxdx
    for (int i =1; i<d; i++)
        {
            ds_sq +=  ( _dist[i] *  _dist[i]) * metric[i];
        }
    */
    
    
    double ds_sq = 0;
    for (int i =0; i<d; i++)
        {
            ds_sq +=  ((*(_pos1 + i) - *(_pos2 + i)) * (*(_pos1 + i)- (*_pos2 + i))) * metric[i];     //take the product ds^2 = dx*dx*g
        }
    
    
    return ds_sq;
}



