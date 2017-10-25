# include <iostream>
# include <cstdlib>
# include <fstream>
# include "spacetime.h" //Contains declarations of the spacetime
# include "elements.h" //Contains declaration of an element
# include "set.h"       //Constains declarations of a set
# include <ctime>
# include <math.h>
#include <stdio.h> 
#include <sys/sysinfo.h> 
using namespace std;

//TODO:
//=====================================================================
//***in the if statement, -0.5 * L_min ???
//***rewrite the NN() fct in set to effectively detect neighbours
//   by using transitivity of causal relations
//***implement (maximal) anti-chain ---> identifier layer neighbour
//=====================================================================




//recursively loop over the spatial coordinates and select elements according to the Poisson distr.
void SprinkleRec(int * p, int d, int dim, int max, float prob, Set& set, ofstream& Output )
{  
    
    double r;
    if(dim == d)
    { 
        r = ((double) rand() / (RAND_MAX));              //create random nr
        
        if(r < prob)                                     //if smaller than prob of finding an element, then add an element
           {                 
               double *pos = new double[d];
               for (int j = 0; j < d; j++)
                    {
                        *(pos + j) = (*(p + j) - 0.5)+((double) rand() / (RAND_MAX));      //randomly place the element in the region assigned to point p
                    }   
                Element e(*set.GetNrElem()+1, pos, d); 
          
               set.AddElem(e);
                  
           
               Output <<pos[0]<<" "<<pos[1]<<endl;       //print position of the element to the Output file
               
               delete [] pos;
                      
                  
                }  
             
    }
   else
   { 
       for(p[dim] = -max; p[dim]<=abs(max); p[dim]+=2)       //loop over values x,y,z,... that are allowed by the diamont shape patch        
       {
           SprinkleRec(p, d, dim+1, max, prob, set, Output); 
           
       }
   }
 }




//Builds a Set 'set' by sprinkling a diamont type patch of the Spacetime 'mink'
void Sprinkle(Spacetime mink, Set &set, ofstream& Output)
{ 
    
    
    int d = mink.d;
    int N = mink.N;
    int t;
    int * point = new int [d];
    float prob = mink.Prob();                         //the probability of finding one element in a fixed volume element (poisson distr.)
    
   for (t = -N ; t <= N; t++)                        //N is scaled up by a factor 2L_min such that the loop runs over integers
    {        
        *point = t;                                 //1st coord of a spacetime point
    
         SprinkleRec(point, d,1, -abs(t)+ N, prob, set, Output);   //recursively loop over the spatial dimensions, given the maximum value of -abs(t)+N 
                                                                   //for the spatial dimensions. (due to the diamont shape)
    }
    delete [] point;
}

int ram_usage(){
  struct sysinfo info; 

  if (sysinfo(&info) != 0)
  {
      cout << "Could not retrieve info from sysinfo" << endl;
      return false;
  }

  unsigned long result = info.freeram * info.mem_unit;
  result += info.freeswap * info.mem_unit;
  result += info.bufferram * info.mem_unit;

  cout << result << endl;
}







int main()
{
    
     
    int metric[] = {1,-1,-1,-1};            //choose a metric
    int L = 4;                              //each dimension runs from -(L-L_min) to (L-L_min)
    int d = 2;                              //spacetime dimension
    float rho = 1;                          //Sprinkling density
  
    Spacetime st(L, rho, metric, d);        //Create a spacetime
    Set S(st);                              //Define a set based on Spacetime 
    
    
    ofstream Output;                        //Output file holding the position of each element
//    Output.open("data.dat");
    ofstream Output2;                     
//    Output2.open("neighbours.dat");       //Output file holding the neighbours of each file
    clock_t begin = clock();                //keep track of execution time
  
    Sprinkle(st, S, Output);                //Sprinkle the spacetime to obtain a Set
    
    cout<<*S.GetNrElem()<<endl;             //print the nr of Elements in the Set
    
    Element *walker = S.GetRoot();          //Get the root element
    Element *walker2 = S.GetTail();         //Get the tail element
    Element *walker3 = S.GetNode(4);        //Get the element with id 4
     
    while(walker != NULL)
    {           
        S.NN(*walker, Output);              //Determine the neighbours of each element in the set
        walker = walker->next;
    }
  
//    vector <int> C = S.M_Causal(Output2);   //Calculate the Causal matrix (WARNING: DON'T ATTEMPT FOR )
  
//    vector <int> Link = S.M_Link();         //Calculate the Link matrix
 
//    cout<<endl;
//    S.display(C);                           //Display the Causal matrix
//    cout<<endl;
//    S.display(Link);                        //Display the Link matrix
//    cout<<endl; 
//    Output.close();
//    Output2.close();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"elapsed time: "<<elapsed_secs;

}
